#include "widget.h"
#include "ui_widget.h"


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    mVolume = new volumeControl(this);

    mVolume->move(QPoint(40,450));

    for(int a=0;a<10;a++)
    {
    mButton1 = new OnOffButton(this);
    mButton1->move(QPoint(200,10+(a*40)));
    mButton1->update();
    mTimer = new QTimer(this);
    connect(mTimer,SIGNAL(timeout()),this,SLOT(removeVolumeInfo()));
    ui->widget_2->hide();




}
mButtonPanel = new buttonPanel(this);
mButtonPanel->move(QPoint(0,640-80));
mButtonPanel->update();
connect(mButtonPanel,SIGNAL(buttonReleased(buttonPanel::buttonpressed)),this,SLOT(buttonPressed(buttonPanel::buttonpressed)));
connect(mVolume,SIGNAL(sendVolume(int)),this,SLOT(volumenControl(int)));
ui->widget_2->raise();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::buttonPressed(buttonPanel::buttonpressed aButton)
{
    qDebug()<<"You Pressed "<<aButton;
}

void Widget::volumenControl(int aInfo)
{
    ui->widget_2->SetInfo(QString::number(aInfo));
    if (!mTimer->isActive())
    {
        mTimer->setInterval(1000);
        ui->widget_2->fadeIn();
        mTimer->start();

    }
    else
    {
        mTimer->start(1000);
    }

}

void Widget::removeVolumeInfo()
{
    ui->widget_2->hide();
    mTimer->stop();
}

