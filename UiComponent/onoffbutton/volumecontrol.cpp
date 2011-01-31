#include "volumecontrol.h"
#define width 250
#define height 50


volumeControl::volumeControl(QWidget *parent) :
    QWidget(parent)
{
mPosX=0;
setWidth(width);
mFactor=100.0/width;
value=0;

}


void volumeControl::setWidth(int aWidth)
{
    mVolumeControlWidth=aWidth;
    setMinimumSize(mVolumeControlWidth,height);
    setMaximumSize(mVolumeControlWidth,height);
}


void volumeControl::paintEvent(QPaintEvent *e)
{
    QPainter p(this);






    QRectF rectangle3(10.0, 7.5,230.0, 15.0);
    QLinearGradient fade2(0.0, 7.5,0.0, 22.5);

    fade2.setColorAt(0, QColor(250, 250, 255, 255));
    fade2.setColorAt(.5, QColor(0, 39, 255, 255));
    fade2.setColorAt(1, QColor(200, 255, 255, 255));

    p.setBrush(fade2);
    p.drawRoundedRect(rectangle3,7.0,7.0);



    QRectF rectangle2(mPosX-15, 0.0, 30, 30);
    QLinearGradient fade1(0, 0, 0,30.0);

    fade1.setColorAt(0, QColor(250, 250, 255, 255));
    fade1.setColorAt(.5, QColor(160, 160, 160, 255));
    fade1.setColorAt(1, QColor(250, 250, 250, 255));

    p.setBrush(fade1);
    p.drawRoundedRect(rectangle2,15.0,15.0);





    p.end();
}



void volumeControl::mouseMoveEvent(QMouseEvent *e)
{


    if((e->pos().x()>15)&&(e->pos().x()<width-15))
    {

        mPosX=e->pos().x();
    }

    update();

    value=e->pos().x()*mFactor;
    if(e->pos().x()<0)
    {
    value=0;
    }
    else if(e->pos().x()>width)
    {
        value=width*mFactor;
    }

    emit sendVolume(value);

}
