#include "scrollitem.h"
#include "ui_scrollitem.h"

ScrollItem::ScrollItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ScrollItem)
{
    ui->setupUi(this);
}

ScrollItem::~ScrollItem()
{
    delete ui;
}

void ScrollItem::setHeader(const QString aHeader)
{
    ui->Header->setText(aHeader);
}
