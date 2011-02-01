#ifndef SCROLLAREA_H
#define SCROLLAREA_H

#include <QWidget>
#include <QVBoxLayout>
#include "QsKineticScroller.h"

namespace Ui {
    class ScrollArea;
}

class ScrollArea : public QWidget
{
    Q_OBJECT

public:
    explicit ScrollArea(QWidget *parent = 0);
    ~ScrollArea();
    void addNewWidget(QWidget *mWidget);

private:
    Ui::ScrollArea *ui;
    QVBoxLayout *vBoxScroll;
    QsKineticScroller *mScroll;

    void init();


};

#endif // SCROLLAREA_H
