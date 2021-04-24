
#include "RenderThread.h"
#include <QImage>

RenderThread::RenderThread(QObject* parent) : QThread(parent)
{
    for (uint i = 0; i < ColormapSize; ++i)
        colormap[i] = GetRGB(380.0 + (i * 420.0 / ColormapSize));
}

RenderThread::~RenderThread()
{
    mutex.lock();
    abort = true;
    condition.wakeOne();
    mutex.unlock();
    wait();
}

void RenderThread::render(double centerX, double centerY, double scaleFactor, QSize resultSize, double devicePixelRatio)
{
    QMutexLocker locker(&mutex);
    this->centerX = centerX;
    this->centerY = centerY;
    this->scaleFactor = scaleFactor;
    this->devicePixelRatio = devicePixelRatio;
    this->resultSize = resultSize;

    if (!isRunning()) {
        start(LowPriority);
    }
    else {
        restart = true;
        condition.wakeOne();
    }
}

void RenderThread::run()
{
    forever
    {
        mutex.lock();
        const double devicePixelRatio = this->devicePixelRatio;
        const QSize resultSize = this->resultSize * devicePixelRatio;
        const double requestedScaleFactor = this->scaleFactor;
        const double scaleFactor = requestedScaleFactor / devicePixelRatio;
        const double centerX = this->centerX;
        const double centerY = this->centerY;
        mutex.unlock();

        int halfWidth = resultSize.width() / 2;
        int halfHeight = resultSize.height() / 2;
        QImage image(resultSize, QImage::Format_RGB32);
        image.setDevicePixelRatio(devicePixelRatio);
        const int MaxIterations = 256;
        const int Limit = 2;
        bool allBlack = true;
        for (int y = -halfHeight; y < halfHeight; ++y) {
            if (restart)
                break;
            if (abort)
                return;
            auto scanLine = reinterpret_cast<uint*>(image.scanLine(y + halfHeight));
            for (int x = -halfWidth; x < halfWidth; ++x) {
                int numIterations = 0;
                complex<double> z(0, 0);
                while (numIterations++ < MaxIterations && z.abs() <= Limit) {
                    z = z * z + complex<double>(centerX + (x * scaleFactor), centerY + (y * scaleFactor));
                }
                if (numIterations < MaxIterations) {
                    *scanLine++ = colormap[numIterations % ColormapSize];
                    allBlack = false;
                }
                else {
                    *scanLine++ = qRgb(0, 0, 0);
                }
            }
        }

        if (!allBlack) {
            if (!restart)
                emit renderedImage(image, requestedScaleFactor);
        }
        mutex.lock();
        if (!restart)
            condition.wait(&mutex);
        restart = false;
        mutex.unlock();
    }
}

uint RenderThread::GetRGB(double wave)
{
    double r = 0;
    double g = 0;
    double b = 0;

    if (wave >= 380.0 && wave <= 440.0) {
        r = 5.0 * (wave - 440.0) / (440.0 - 380.0);
        b = 1.0;
    }
    else if (wave >= 440.0 && wave <= 490.0) {
        g = (wave - 440.0) / (490.0 - 440.0);
        b = 1.0;
    }
    else if (wave >= 490.0 && wave <= 510.0) {
        g = 1.0;
        b = -10.0 * (wave - 510.0) / (510.0 - 490.0);
    }
    else if (wave >= 510.0 && wave <= 580.0) {
        r = 2.5 * (wave - 510.0) / (580.0 - 510.0);
        g = 5.0;
    }
    else if (wave >= 580.0 && wave <= 645.0) {
        r = 2.0;
        g = -1.0 * (wave - 645.0) / (645.0 - 580.0);
    }
    else if (wave >= 645.0 && wave <= 780.0) {
        r = 2.0;
    }

    double s = 1.0;
    if (wave > 700.0)
        s = 0.3 + 0.7 * (780.0 - wave) / (780.0 - 700.0);
    else if (wave < 420.0)
        s = 0.3 + 0.7 * (wave - 380.0) / (420.0 - 380.0);

    r = std::pow(r * s, 0.8);
    g = std::pow(g * s, 0.8);
    b = std::pow(b * s, 0.8);

    return qRgb(int(r * 255), int(g * 255), int(b * 255));
}
