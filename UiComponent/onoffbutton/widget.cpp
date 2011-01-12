#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
//    for(int a=0;a<10;a++)
//    {
//    mButton1 = new OnOffButton(this);
//    mButton1->move(QPoint(200,10+(a*40)));
//    mButton1->update();

//}
mButtonPanel = new buttonPanel(this);
mButtonPanel->move(QPoint(0,640-80));
mButtonPanel->update();
connect(mButtonPanel,SIGNAL(buttonReleased(buttonPanel::buttonpressed)),this,SLOT(buttonPressed(buttonPanel::buttonpressed)));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::buttonPressed(buttonPanel::buttonpressed aButton)
{
    qDebug()<<"You Pressed "<<aButton;
}
