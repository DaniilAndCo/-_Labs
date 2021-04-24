#pragma once
#include <QThread>
#include <QMutex>
#include <QWaitCondition>
#include <QSize>

template <class T>
class complex
{
public:
    T x, y;
    complex(T x, T y)
    {
        this->x = x;
        this->y = y;
    }
    uint abs()
    {
        return sqrt(x*x + y*y);
    }
    complex operator*(complex<T> other)
    {
        return complex(x*other.x  - y*other.y, x*other.y + y*other.x);
    }
    complex operator+(complex<T> other)
    {
        return complex(x + other.x, y + other.y);
    }
};

class RenderThread : public QThread
{
    Q_OBJECT

public:
    RenderThread(QObject *parent = nullptr);
    ~RenderThread();

    void render(double, double, double, QSize, double);

signals:
    void renderedImage(const QImage&, double);

protected:
    void run() override;

private:
    static uint GetRGB(double);

    QMutex mutex;
    QWaitCondition condition;
    const static uint ColormapSize = 512;
    uint colormap[ColormapSize];
    double centerX;
    double centerY;
    double scaleFactor;
    double devicePixelRatio;
    QSize resultSize;
    bool restart = false;
    bool abort = false;
};
