#ifndef VOLUMECONTROL_H
#define VOLUMECONTROL_H

#include <QWidget>
#include <QtGui>

class volumeControl : public QWidget
{
    Q_OBJECT
public:
    explicit volumeControl(QWidget *parent = 0);
    void paintEvent(QPaintEvent *);
    void setWidth(int aWidth);
    void mouseMoveEvent(QMouseEvent *);


private:
   int mVolumeControlWidth;
   int mPosX;
   float mFactor;
   int value;
   QPixmap mHandle;

signals:
   void sendVolume(int);

public slots:


};

#endif // VOLUMECONTROL_H
