#include <QtGui/QApplication>
#include "rollerwidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    RollerWidget w(20);
    w.show();

    return a.exec();
}
