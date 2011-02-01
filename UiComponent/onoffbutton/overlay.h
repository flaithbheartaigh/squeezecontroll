#ifndef OVERLAY_H
#define OVERLAY_H

#include <QWidget>
#include <QMouseEvent>

namespace Ui {
    class overlay;
}

class overlay : public QWidget
{
    Q_OBJECT

public:
    explicit overlay(QWidget *parent = 0);
    ~overlay();
    void mouseMoveEvent(QMouseEvent *);
    void mousePressEvent(QMouseEvent *);

private:
    Ui::overlay *ui;
    int oldPosx;
};

#endif // OVERLAY_H
