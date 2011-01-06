#include "onoffbutton.h"
#define size_width 140.0
#define size_height 35.0
#define handle_width 50
#define animation_width handle_width+5

OnOffButton::OnOffButton(QWidget *parent) :
        QWidget(parent)
{
    mButtonState=false;
    setMinimumSize(size_width+5.0,size_height+2);
    setMaximumSize(size_width+5.0,size_height+2);
    mPosX=4;
    mMouseMoved=false;

}

void OnOffButton::mousePressEvent(QMouseEvent *e)
{
    mStartXpos=e->pos().x();
}

void OnOffButton::mouseReleaseEvent(QMouseEvent *e)
{
    qDebug()<<abs(mStartXpos-mPosX);




    if ((abs(mStartXpos-e->pos().x())>(size_width/2.5))||(!mMouseMoved))
        mButtonState=!mButtonState;


    if (mButtonState)
    {
        animate(mPosX,size_width-animation_width);
    }
    else
    {
        animate(mPosX,4);
    }
    mMouseMoved=false;
}

void OnOffButton::mouseMoveEvent(QMouseEvent *e)
{

    int x;
    //qDebug()<<abs(mStartXpos-e->pos().x());
    if ((abs(mStartXpos-e->pos().x())>2)||(mMouseMoved==true))
    {
       // qDebug("Mouse Move Ok");
        mMouseMoved=true;

        if(e->pos().x()<mStartXpos)
        {
            x=((size_width-handle_width)-(abs(mStartXpos-e->pos().x())));
         //   qDebug()<<"x1="<<x;
        }
        else
        {
            x=((abs(mStartXpos-e->pos().x())));
           // qDebug()<<"x2="<<x;
        }



        if(x<4) x=4;
        else if(x>size_width-handle_width) x=5+size_width-handle_width;



        mPosX=x;

        update();
    }
}

void OnOffButton::animate(int xStart, int xEnd)
{
    QTimeLine *timeLine = new QTimeLine(300, this);
    timeLine->setFrameRange(xStart, xEnd);
    connect(timeLine, SIGNAL(frameChanged(int)), this, SLOT(updateAnimation(int)));
    timeLine->start();


}

void OnOffButton::updateAnimation(int x)
{
    mPosX=x;

    update();
}

void OnOffButton::paintEvent(QPaintEvent *e)
{
    QPainter p(this);






    QRectF rectangle3(3.0, 0.0, mPosX, size_height-0.1);
    QLinearGradient fade2(0, 0, 0,25.0);
    fade2.setColorAt(0, QColor(0, 39, 255, 255));
    fade2.setColorAt(1, QColor(113, 165, 255, 255));
    p.setBrush(fade2);
    p.drawRoundedRect(rectangle3,7.0,7.0);

    p.setPen(QColor(255,255,255));
    p.drawText((-size_width/2)+mPosX,25,"ON");


    QRectF rectangle4(27.0+mPosX, 0.0, size_width-mPosX,size_height-0.1);
    QLinearGradient fade1(0, 0, 0, height());
    fade1.setColorAt(0, QColor(231, 231, 231, 255));
    fade1.setColorAt(1, QColor(255, 255, 255, 255));
    p.setBrush(fade1);
    p.drawRoundedRect(rectangle4,7.0,7.0);

    p.setPen(QColor(136,136,136));
    p.drawText((size_width/2)+mPosX,25,"OFF");


    p.setPen(QColor(176,176,176));
    QRectF rectangle(mPosX-3, 0.0, handle_width, size_height);

    QLinearGradient fade(0, 0, 0, height()/3);
    fade.setColorAt(0, QColor(201, 201, 201, 255));
    fade.setColorAt(1, QColor(255, 255, 255, 255));
    p.setBrush(fade);
    p.drawRoundedRect(rectangle,7.0,7.0);




    p.setBrush(Qt::NoBrush);
    QRectF rectangle1(0.0, 0.1, size_width+4, size_height);
    p.drawRoundedRect(rectangle1, 7.0, 7.0);




    p.end();
}

