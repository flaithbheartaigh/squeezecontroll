#include "overlay.h"
#include "ui_overlay.h"

overlay::overlay(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::overlay)
{
    ui->setupUi(this);
    oldPosx=0;
}

overlay::~overlay()
{
    delete ui;
}


void overlay::mouseMoveEvent(QMouseEvent *e)
{

    move(QPoint(oldPosx--,0));

}

void overlay::mousePressEvent(QMouseEvent *e)
{

}
