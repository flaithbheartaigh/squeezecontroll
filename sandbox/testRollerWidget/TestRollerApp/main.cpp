#include <QtGui/QApplication>
#include "rollerwidget.h"
#include "scrollitem.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    RollerWidget w(20, 31);
    w.setCount(50);
    w.show();
    for(int i=0;i<20;i++)
    {
        ScrollItem* myItem = new ScrollItem(&w);
        myItem->setHeader(QString("MyString %0").arg(i));
        myItem->setGeometry(0,0,200,31);
        w.addWidget(myItem);
    }
    return a.exec();
}
