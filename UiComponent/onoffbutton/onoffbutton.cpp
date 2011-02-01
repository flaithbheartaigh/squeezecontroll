#include "onoffbutton.h"
#define size_width 110.0
#define size_height 35.0
#define handle_width 50
#define onOffset 10
#define offOffset 5
#define startOffset 4
#define textYOffset 25
#define rectRadius 7.0
#define offAreaStart handle_width-10
#define offAreaEnd size_width-handle_width+14
#define animation_width handle_width+7




OnOffButton::OnOffButton(QWidget *parent) :
        QWidget(parent)
{
    mButtonState=false;
    setMinimumSize(size_width+5.0,size_height+2);
    setMaximumSize(size_width+5.0,size_height+2);
    mPosX=startOffset;
    mMouseMoved=false;
    mMousePressed=false;
    mOldXPos=0;
    mDirection=OnOffButton::NONE;

    QLinearGradient fade2(0, 0, 0,size_height);
    fade2.setColorAt(0, QColor(0, 0, 80, 255));
    fade2.setColorAt(0.2,QColor(0, 39, 255, 255));
    fade2.setColorAt(1, QColor(153, 155, 255, 255));
    setOnBackGroundGradien(fade2);

}


void OnOffButton::setOnBackGroundGradien(QLinearGradient aGradient)
{

    mOnBackGroundGradien=aGradient;
    mOnBackGroundGradien.setStart(0,0);
    mOnBackGroundGradien.setFinalStop(0,size_height);
}

void OnOffButton::setOffBackGroundGradien(QLinearGradient aGradient)
{
    mOffBackgroundGradient=aGradient;
}

void OnOffButton::setHandleBackGroundGradien(QLinearGradient aGradient)
{
    mHandleBackGroundGradient=aGradient;
}

void OnOffButton::mousePressEvent(QMouseEvent *e)
{
    mStartXpos=e->pos().x();
    mMousePressed=true;
    qDebug()<<"Mouse press "<<mStartXpos;
}



void OnOffButton::mouseReleaseEvent(QMouseEvent *e)
{
    qDebug()<<abs(mStartXpos-mPosX);


    //First step button state check
    //We need to check the traveled distance, it has to be
    //greather the 1/3 of the total component width and
    //The mouse has to be in move state;
    //If we do not have a mouseMove detected.
    if (((abs(mStartXpos-e->pos().x())>(size_width/3))&&(mMouseMoved))||((!mMouseMoved)&&(mMousePressed)))
    {

    //Calculate if we should change the buttom state;
    if((mDirection==OnOffButton::NONE)||((mDirection==OnOffButton::RIGHT)&&(mButtonState==false))||((mDirection==OnOffButton::LEFT)&&(mButtonState==true)))
        mButtonState=!mButtonState;

    }


    if (mButtonState)
    {
        animate(mPosX,size_width-animation_width);
    }
    else
    {
        animate(mPosX,startOffset);
    }


    mMouseMoved=false;
    mMousePressed=false;
    mDirection=OnOffButton::NONE;
}




void OnOffButton::mouseMoveEvent(QMouseEvent *e)
{


    //Check that this is a real mouse event, this is needed for real HW.
    if ((abs(mStartXpos-e->pos().x())>8)||(mMouseMoved==true))
    {
        mMouseMoved=true;
        int currentXPox=e->pos().x();
        int vectorL=currentXPox-mOldXPos;

        //Store the direction, for use on mouse release;
        if (vectorL<0) mDirection=OnOffButton::LEFT;
        else mDirection=OnOffButton::RIGHT;

        mPosX=mPosX+vectorL;

        //Min and Max value for the handle
        if(mPosX<startOffset) mPosX=startOffset;
        else if(mPosX>(size_width-handle_width+offOffset)) mPosX=size_width-handle_width+offOffset;

        update();               //Update the graphics
        mOldXPos=currentXPox;   //Store the x vextor;

    }
    else
        if (!mMouseMoved)
            mOldXPos=e->pos().x(); // STore the current position for use when a mousemove has been detected
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


    //Draw blue rect with on text inside
//******************************************************************
    QRectF rectangle3(0.1, 0.0, mPosX+5, size_height-0.1);

    p.setBrush(mOnBackGroundGradien);
    p.drawRoundedRect(rectangle3,rectRadius,rectRadius);

    p.setPen(QColor(255,255,255));
    p.drawText((-size_width/2)+mPosX+onOffset,textYOffset,"ON");
//******************************************************************

    //Draw Gray Rect rect with off text inside
//******************************************************************
    QRectF rectangle4(offAreaStart+mPosX, 0.0, offAreaEnd-mPosX,size_height-0.1);
    QLinearGradient fade1(0, 0, 0, height());
    fade1.setColorAt(0, QColor(160, 160, 160, 255));
    fade1.setColorAt(0.1,QColor(241,241,241));
    fade1.setColorAt(1, QColor(255, 255, 255, 255));
    p.setBrush(fade1);
    p.drawRoundedRect(rectangle4,rectRadius,rectRadius);

    p.setPen(QColor(136,136,136));
    p.drawText((size_width/2)+mPosX+offOffset,textYOffset,"OFF");



//******************************************************************

//Draw the handle
//******************************************************************
    p.setPen(QColor(176,176,176));
    QRectF rectangle(mPosX-3, 0.0, handle_width, size_height);
    QLinearGradient fade(0, 0, 0, height()/2);
    fade.setColorAt(0, QColor(255, 255, 255, 255));
    fade.setColorAt(0.2, QColor(201, 201, 201, 255));
    fade.setColorAt(1, QColor(252, 252, 252, 255));
    p.setBrush(fade);
    p.drawRoundedRect(rectangle,rectRadius,rectRadius);

//******************************************************************



//Draw the outher box
//******************************************************************
    p.setBrush(Qt::NoBrush);
    p.setPen(QColor(136,136,136));
    QRectF rectangle1(0.0, 0.1, size_width+startOffset, size_height);
    p.drawRoundedRect(rectangle1, rectRadius, rectRadius);
//******************************************************************



    p.end();
}

