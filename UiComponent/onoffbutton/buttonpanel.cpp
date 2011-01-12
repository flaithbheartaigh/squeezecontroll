#include "buttonpanel.h"
#define size_width 360.0
#define size_height 80.0
#define heighLightWidth 80
#define heighLightHeight 70
#define heighLightRect QRect(5,5,heighLightWidth,heighLightHeight)
#define heighLightRadius 10.0
#define fontSize 5
#define textWidth 80.0
#define textRect QRectF(5.0,size_height-25,textWidth,20.0)
#define nextText 90.0


buttonPanel::buttonPanel(QWidget *parent) :
        QWidget(parent)
{
    setMinimumSize(size_width+5.0,size_height+2);
    setMaximumSize(size_width+5.0,size_height+2);
    init();
}

void buttonPanel::setText(QString aText, int aButtonNumber)

{
    switch (aButtonNumber)
    {
    case 1: mButton1Text=aText;break;
    case 2: mButton2Text=aText;break;
    case 3: mButton3Text=aText;break;
    case 4: mButton4Text=aText;break;


    default:
        qDebug("Wrong number");
    }

}

void buttonPanel::setButIconOn(QPixmap aIcon, int aIconNumber)
{
    switch (aIconNumber)
    {
    case 1: mButIcon1On=aIcon;break;
    case 2: mButIcon2On=aIcon;break;
    case 3: mButIcon3On=aIcon;break;
    case 4: mButIcon4On=aIcon;break;


    default:
        qDebug("Wrong number");
    }
}

void buttonPanel::setButIconOff(QPixmap aIcon, int aIconNumber)
{
    switch (aIconNumber)
    {
    case 1: mButIcon1Off=aIcon;break;
    case 2: mButIcon2Off=aIcon;break;
    case 3: mButIcon3Off=aIcon;break;
    case 4: mButIcon4Off=aIcon;break;


    default:
        qDebug("Wrong number");
    }
}


void buttonPanel::setTextOnColor(QColor aColor)
{
    mTextOnColor=aColor;
}

void buttonPanel::setTextOffColor(QColor aColor)
{
    mTextOffColor=aColor;
}

void buttonPanel::init()
{
    mButton1Text="Artist";
    mButton2Text="Albums";
    mButton3Text="Genres";
    mButton4Text="More";
    mButtonPressed=buttonPanel::BUT1;
    mHighLightRect=heighLightRect;
    mTextOffColor=QColor(160,160,160);
    mTextOnColor=QColor(255,255,255);
    mButIcon1On=QPixmap(":/Icon/artist_on.png");
    mButIcon1Off=QPixmap(":/Icon/artist_off.png");
    mButIcon2On=QPixmap(":/Icon/albums_on.png");
    mButIcon2Off=QPixmap(":/Icon/albums_off.png");
    mButIcon3On=QPixmap(":/Icon/genres_on.png");
    mButIcon3Off=QPixmap(":/Icon/genres_off.png");
    mButIcon4On=QPixmap(":/Icon/more_on.png");
    mButIcon4Off=QPixmap(":/Icon/more_off.png");
}

void buttonPanel::mouseReleaseEvent(QMouseEvent *e)
{
    QPoint mousePos = e->pos();
    int x=mousePos.x();

    if ((x>0)&&(x<90))
        mButtonPressed=buttonPanel::BUT1;
    else if ((x>90)&&(x<180))
        mButtonPressed=buttonPanel::BUT2;
    else if ((x>180)&&(x<270))
        mButtonPressed=buttonPanel::BUT3;
    else if ((x>270)&&(x<360))
        mButtonPressed=buttonPanel::BUT4;

    mHighLightRect=heighLightRect;
    mHighLightRect.setLeft(heighLightRect.left()+(90*(mButtonPressed-1)));
    mHighLightRect.setWidth(heighLightWidth);
    update();
    emit buttonReleased(mButtonPressed);
}

void buttonPanel::paintEvent(QPaintEvent *e)
{
    QPainter p(this);
    qDebug("Button Panel Painting");
    p.setBrush(QColor(35,35,35,230));

    p.setPen(Qt::NoPen);
    p.drawRect(0.0,0.0,size_width,size_height/2);

    p.setPen(QColor(0,0,0));
    p.drawLine(0.0,0.0,size_width,0.0);

    p.setPen(Qt::NoPen);

    p.setBrush(QColor(20,20,20,230));
    p.drawRect(0.0,(size_height/2),size_width,size_height/2);

    p.setPen(QColor(10,10,10));
    for (int a=1;a<5;a++)
    {
        p.drawLine(90*a,0,90*a,size_height);
    }



    p.setPen(Qt::NoPen);
    p.setBrush(QColor(100,100,100,100));
    p.drawRoundedRect(mHighLightRect,heighLightRadius,heighLightRadius);
    p.setPen(QColor(255,255,255));



    //Draw the 4 button Text
    //********************************************************************
    QFont mFont;
    mFont.setPointSize(fontSize);
    p.setFont(mFont);
    QTextOption mOption;
    mOption.setAlignment(Qt::AlignCenter);
    QRectF mRect=textRect;

    if(mButtonPressed==buttonPanel::BUT1)
    {
        p.setPen(mTextOnColor);
        p.drawPixmap(20,20,mButIcon1On);
        mFont.setBold(true);
        p.setFont(mFont);
    }
    else {
        p.setPen(mTextOffColor);
        p.drawPixmap(20,20,mButIcon1Off);
        mFont.setBold(false);
        p.setFont(mFont);
    }

    p.drawText(textRect,mButton1Text,mOption);
    mRect.setX(mRect.x()+nextText);
    mRect.setWidth(textWidth);
    if(mButtonPressed==buttonPanel::BUT2)
    {
        p.setPen(mTextOnColor);
        p.drawPixmap(118,20,mButIcon2On);
        mFont.setBold(true);
        p.setFont(mFont);
    }
    else {
        p.setPen(mTextOffColor);
        p.drawPixmap(118,20,mButIcon2Off);
        mFont.setBold(false);
        p.setFont(mFont);
    }

    p.drawText(mRect,mButton2Text,mOption);
    mRect.setX(mRect.x()+nextText);
    mRect.setWidth(textWidth);

    if(mButtonPressed==buttonPanel::BUT3)
    {
        p.setPen(mTextOnColor);
        p.drawPixmap(210,20,mButIcon3On);
        mFont.setBold(true);
        p.setFont(mFont);
    }
    else {
        p.setPen(mTextOffColor);
        p.drawPixmap(210,20,mButIcon3Off);
        mFont.setBold(false);
        p.setFont(mFont);
    }
    p.drawText(mRect,mButton3Text,mOption);
    mRect.setX(mRect.x()+nextText);
    mRect.setWidth(textWidth);
    if(mButtonPressed==buttonPanel::BUT4)
    {
        p.setPen(mTextOnColor);
        p.drawPixmap(298,20,mButIcon4On);
        mFont.setBold(true);
        p.setFont(mFont);
    }
    else {
        p.setPen(mTextOffColor);
        p.drawPixmap(298,20,mButIcon4Off);
        mFont.setBold(false);
        p.setFont(mFont);
    }
        p.drawText(mRect,mButton4Text,mOption);
    //********************************************************************

    p.end();
}


