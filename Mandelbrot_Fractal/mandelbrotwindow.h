#pragma once
#include "RenderThread.h"
#include <QWidget>

class MandelbrotWindow : public QWidget
{
    Q_OBJECT

public:
    MandelbrotWindow(QWidget *parent = nullptr);
    ~MandelbrotWindow();

protected:
    void resizeEvent(QResizeEvent*) override;
    void keyPressEvent(QKeyEvent*) override;
    void mousePressEvent(QMouseEvent*) override;
    void mouseMoveEvent(QMouseEvent*) override;
    void mouseReleaseEvent(QMouseEvent*) override;
    void paintEvent(QPaintEvent*) override;

#if QT_CONFIG(wheelevent)
    void wheelEvent(QWheelEvent*) override;
#endif

private slots:
    void zoom(double);
    void updatePixmap(const QImage&, double);

private:
    void scroll(int, int);

    RenderThread thread;
    QPixmap pixmap;
    QPoint pixmapOffset;
    QPoint lastDragPos;
    double centerX;
    double centerY;
    double pixmapScale;
    double curScale;
};
