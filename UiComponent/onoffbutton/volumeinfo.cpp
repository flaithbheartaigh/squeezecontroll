#include "volumeinfo.h"
#include "ui_volumeinfo.h"
#include <QTimeLine>

VolumeInfo::VolumeInfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VolumeInfo)
{
    ui->setupUi(this);

}

VolumeInfo::~VolumeInfo()
{
    delete ui;
}


void VolumeInfo::SetInfo(QString aInf)
{
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


void VolumeInfo::setSettingsFrameTrans(int aValue)
{

    ui->MasterFrame->setStyleSheet("border-radius: 10px;background-color: rgba(38, 73, 129,"+QString::number(aValue)+");");

}
