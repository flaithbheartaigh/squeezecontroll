#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <onoffbutton.h>
#include <buttonpanel.h>
#include "volumecontrol.h"
#include "volumeinfo.h"
#include "scrollarea.h"
#include "overlay.h"
#include <QTimer>

namespace Ui {
    class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private:
    Ui::Widget *ui;
    OnOffButton* mButton1;
    buttonPanel* mButtonPanel;
    volumeControl* mVolume;
    ScrollArea* mPanelScroll;
    overlay *mOverLay;
    QTimer *mTimer;


private slots:
    void buttonPressed(buttonPanel::buttonpressed);
    void volumenControl(int);
    void removeVolumeInfo();


};


#endif // WIDGET_H
