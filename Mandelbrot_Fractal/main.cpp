#include "mandelbrotwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MandelbrotWindow fractal;
    fractal.show();
    return app.exec();
}
