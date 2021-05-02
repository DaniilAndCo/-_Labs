#include "renderusamap.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    RenderUsaMap w;
    w.show();
    return a.exec();
}
