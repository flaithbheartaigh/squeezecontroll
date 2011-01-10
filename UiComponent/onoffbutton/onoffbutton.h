#ifndef ONOFFBUTTON_H
#define ONOFFBUTTON_H

#include <QWidget>
#include <QtCore>
#include <QtGui>

class OnOffButton : public QWidget
{
    Q_OBJECT
public:
    explicit OnOffButton(QWidget *parent = 0);
    void mouseReleaseEvent(QMouseEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void paintEvent(QPaintEvent *);

    enum {NONE,LEFT,RIGHT} direction;

private:
bool mButtonState;
bool mMouseMoved;
bool mMousePressed;
int mStartXpos;
int mOldXPos;
int mPosX;
int mDirection;
void animate(int xStart,int xEnd);
signals:
void buttonPressed(bool);

public slots:
void updateAnimation(int);

};

#endif // ONOFFBUTTON_H
