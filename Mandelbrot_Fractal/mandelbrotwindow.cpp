#include "mandelbrotwindow.h"
#include "ui_mandelbrotwidget.h"
#include <QPainter>
#include <QMouseEvent>
#include <QWheelEvent>

const double DefaultCenterX = -0.65;
const double DefaultCenterY = -0.004;
const double DefaultScale = 0.004;

const double ZoomInFactor = 0.8;
const double ZoomOutFactor = 1 / ZoomInFactor;
const int ScrollStep = 15;

MandelbrotWindow::MandelbrotWindow(QWidget* parent): QWidget(parent), centerX(DefaultCenterX), centerY(DefaultCenterY), pixmapScale(DefaultScale), curScale(DefaultScale)
{
    connect(&thread, &RenderThread::renderedImage, this, &MandelbrotWindow::updatePixmap);

    setWindowTitle(tr("Mandelbrot Fractal in C++ by Daniel Bondarkov"));
#if QT_CONFIG(cursor)
    setCursor(Qt::CrossCursor);
#endif
    resize(750, 550);
}

void MandelbrotWindow::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    painter.fillRect(rect(), Qt::black);

    if (pixmap.isNull()) {
        painter.setPen(Qt::white);
        painter.drawText(rect(), Qt::AlignCenter, tr("Rendering of the fractal, wait..."));
        return;
    }

    if (qFuzzyCompare(curScale, pixmapScale)) {
        painter.drawPixmap(pixmapOffset, pixmap);
    }
    else {
        auto previewPixmap = pixmap.devicePixelRatioF() == 1.0 ? pixmap : pixmap.scaled(pixmap.size() / pixmap.devicePixelRatioF(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        double scaleFactor = pixmapScale / curScale;
        int newWidth = int(previewPixmap.width() * scaleFactor);
        int newHeight = int(previewPixmap.height() * scaleFactor);
        int newX = pixmapOffset.x() + (previewPixmap.width() - newWidth) / 2;
        int newY = pixmapOffset.y() + (previewPixmap.height() - newHeight) / 2;

        painter.save();
        painter.translate(newX, newY);
        painter.scale(scaleFactor, scaleFactor);

        QRectF exposed = painter.transform().inverted().mapRect(rect()).adjusted(-1, -1, 1, 1);
        painter.drawPixmap(exposed, previewPixmap, exposed);
        painter.restore();
    }
}

void MandelbrotWindow::resizeEvent(QResizeEvent*)
{
    thread.render(centerX, centerY, curScale, size(), devicePixelRatioF());
}

void MandelbrotWindow::keyPressEvent(QKeyEvent* event)
{
    switch (event->key()) {
    case Qt::Key_Plus:
        zoom(ZoomInFactor);
        break;
    case Qt::Key_Minus:
        zoom(ZoomOutFactor);
        break;
    case Qt::Key_Left:
        scroll(-ScrollStep, 0);
        break;
    case Qt::Key_Right:
        scroll(+ScrollStep, 0);
        break;
    case Qt::Key_Down:
        scroll(0, -ScrollStep);
        break;
    case Qt::Key_Up:
        scroll(0, +ScrollStep);
        break;
    default:
        QWidget::keyPressEvent(event);
    }
}

void MandelbrotWindow::wheelEvent(QWheelEvent* event)
{
    const int numDegrees = event->angleDelta().y() / 8;
    const double numSteps = numDegrees / double(15);
    zoom(pow(ZoomInFactor, numSteps));
}

void MandelbrotWindow::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
        lastDragPos = event->pos();
}

void MandelbrotWindow::mouseMoveEvent(QMouseEvent* event)
{
    if (event->buttons() & Qt::LeftButton) {
        pixmapOffset += event->pos() - lastDragPos;
        lastDragPos = event->pos();
        update();
    }
}

void MandelbrotWindow::mouseReleaseEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton) {
        pixmapOffset += event->pos() - lastDragPos;
        lastDragPos = QPoint();

        const auto pixmapSize = pixmap.size() / pixmap.devicePixelRatioF();
        int deltaX = (width() - pixmapSize.width()) / 2 - pixmapOffset.x();
        int deltaY = (height() - pixmapSize.height()) / 2 - pixmapOffset.y();
        scroll(deltaX, deltaY);
    }
}

void MandelbrotWindow::updatePixmap(const QImage& image, double scaleFactor)
{
    if (!lastDragPos.isNull())
        return;

    pixmap = QPixmap::fromImage(image);
    pixmapOffset = QPoint();
    lastDragPos = QPoint();
    pixmapScale = scaleFactor;
    update();
}

void MandelbrotWindow::zoom(double zoomFactor)
{
    curScale *= zoomFactor;
    update();
    thread.render(centerX, centerY, curScale, size(), devicePixelRatioF());
}

void MandelbrotWindow::scroll(int deltaX, int deltaY)
{
    centerX += deltaX * curScale;
    centerY += deltaY * curScale;
    update();
    thread.render(centerX, centerY, curScale, size(), devicePixelRatioF());
}

MandelbrotWindow::~MandelbrotWindow() {}
