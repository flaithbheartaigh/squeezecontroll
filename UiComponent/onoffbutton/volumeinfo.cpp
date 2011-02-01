#include "volumeinfo.h"
#include "ui_volumeinfo.h"
#include <QTimeLine>

VolumeInfo::VolumeInfo(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::VolumeInfo)
{
    ui->setupUi(this);
    mFadeOut=false;

}

VolumeInfo::~VolumeInfo()
{
    delete ui;
}


void VolumeInfo::SetInfo(QString aInf)
{

    if(mFadeOut==true)
    {

        timeLine->stop();
        ui->MasterFrame->setStyleSheet("border-radius: 10px;background-color: rgba(38, 73, 129,180);");
        mFadeOut=false;
    }

    ui->label->setText(aInf);

}


void VolumeInfo::fadeIn()
{
    QTimeLine *timeLine = new QTimeLine(500, this);
    timeLine->setFrameRange(0, 180);
    connect(timeLine, SIGNAL(frameChanged(int)), this,SLOT(setSettingsFrameTrans(int)));
    timeLine->start();

    ui->MasterFrame->setStyleSheet("border-radius: 10px;background-color: rgba(38, 73, 129,0);");
    show();
}

void VolumeInfo::fadeOut()
{


    timeLine = new QTimeLine(500, this);
    timeLine->setFrameRange(180, 0);
    connect(timeLine, SIGNAL(frameChanged(int)), this,SLOT(setSettingsFrameTrans(int)));
    connect(timeLine,SIGNAL(finished()),this,SLOT(fadeOutFinish()));
    timeLine->start();

    ui->MasterFrame->setStyleSheet("border-radius: 10px;background-color: rgba(38, 73, 129,180);");
    mFadeOut=true;
}


void VolumeInfo::setSettingsFrameTrans(int aValue)
{

    ui->MasterFrame->setStyleSheet("border-radius: 10px;background-color: rgba(38, 73, 129,"+QString::number(aValue)+");");

}

void VolumeInfo::fadeOutFinish()
{
    hide();
    mFadeOut=false;
}
