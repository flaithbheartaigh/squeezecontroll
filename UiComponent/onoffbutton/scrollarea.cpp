#include "scrollarea.h"
#include "ui_scrollarea.h"
#include <QPushButton>

ScrollArea::ScrollArea(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ScrollArea)
{
    ui->setupUi(this);
    init();


}

ScrollArea::~ScrollArea()
{
    delete ui;
}


void ScrollArea::init()
{

    vBoxScroll = new QVBoxLayout(ui->internal);
    ui->internal->setLayout(vBoxScroll);

//    for (int a=0;a<10;a++)
//    {
//    QPushButton *mBtn = new QPushButton(ui->internal);
//    mBtn->setGeometry(0,0,40,20);
//    mBtn->show();
//    mBtn->raise();
//    vBoxScroll->addWidget(mBtn);



//}


    mScroll = new QsKineticScroller(this);
    mScroll->enableKineticScrollFor(ui->scrollArea_2);
}

void ScrollArea::addNewWidget(QWidget *mWidget)
{

vBoxScroll->addWidget(mWidget);

}
