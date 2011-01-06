#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <onoffbutton.h>

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
};

#endif // WIDGET_H
