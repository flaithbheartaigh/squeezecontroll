#ifndef SCROLLITEM_H
#define SCROLLITEM_H

#include <QWidget>

namespace Ui {
    class ScrollItem;
}

class ScrollItem : public QWidget
{
    Q_OBJECT

public:
    explicit ScrollItem(QWidget *parent = 0);
    ~ScrollItem();
    void setHeader(const QString aHeader);

private:
    Ui::ScrollItem *ui;
};

#endif // SCROLLITEM_H
