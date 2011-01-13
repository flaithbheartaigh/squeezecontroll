#ifndef BUTTONPANEL_H
#define BUTTONPANEL_H

#include <QWidget>
#include <QtGui>
#include <QtCore>

class buttonPanel : public QWidget
{
    Q_OBJECT

public:
    enum buttonpressed {NOBUTTON,BUT1,BUT2,BUT3,BUT4};
    explicit buttonPanel(QWidget *parent = 0);
    void paintEvent(QPaintEvent *);
    void setText(QString aText,int aButtonNumber);

    void setButIconOn(QPixmap aIcon,int aIconNumber);
    void setButIconOff(QPixmap aIcon,int aIconNumber);

    void setTextOnColor(QColor aColor);
    void setTextOffColor(QColor aColor);
    virtual void mouseReleaseEvent(QMouseEvent *);

private:
    QString mButton1Text,mButton2Text,mButton3Text,mButton4Text;
    QPixmap mButIcon1On,mButIcon2On,mButIcon3On,mButIcon4On;
    QPixmap mButIcon1Off,mButIcon2Off,mButIcon3Off,mButIcon4Off;
    void init();
    QRect mHighLightRect;
    QColor mTextOnColor,mTextOffColor;

    buttonpressed mButtonPressed;

signals:
    void buttonReleased(buttonPanel::buttonpressed);

public slots:

};

#endif // BUTTONPANEL_H
