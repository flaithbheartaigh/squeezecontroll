#include <QtGui/QApplication>
#include "widget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
#if defined(Q_WS_S60)
    w.showMaximized();
#else
    w.showFullScreen();
#endif

    return a.exec();
}
