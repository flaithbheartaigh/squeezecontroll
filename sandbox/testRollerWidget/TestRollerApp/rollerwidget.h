#ifndef ROLLERWIDGET_H
#define ROLLERWIDGET_H

#include <QWidget>
#include "flickable.h"
#include <QtCore>
#include <QtGui>
#include <QFont>

namespace Ui {
    class RollerWidget;
}

class RollerWidget : public QWidget, public Flickable
{
    Q_OBJECT

public:
    explicit RollerWidget(int aBufferSize, int aWidgetHeight, QWidget *parent = 0, int aNumOfTextToDisplay = 1,QColor aTextSelected=Qt::lightGray, QColor aText=Qt::blue, QColor aBackGround=Qt::white);
    ~RollerWidget();

    void scrolllist(int offset);
    int getScrollListOffset();
    int getSelected();
    void setBackgroundColor(QColor color);
    void setTextColor(QColor color);
    void setSelectedColor(QColor color);
    void setLineColor(QColor color);
    int count();
    void setNumOfTextToDisplay(int aNumOfTextToDisplay);
    void setHighLightedColor(QColor color);             //Color to be used in widget that is selected
    void setCount(int aNumOfItemsInList);               //Sets the total amount of widgets in list
    void addWidget(QWidget* aWidget);
protected:
    //reimplement from flickable
    virtual QPoint scrollOffset() const;
    virtual void setEndScroll();
    virtual void setScrollOffset1(const QPoint &offset);

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);

private:
    void moveWidgets();         //Moves the widgets m_offset-old_offset
    bool m_ScrollDirectionDown; //used to determing whether new widgets go to top or bottom
    int m_pending_fetch;        //When 0 all widgets are fetched and update is initiated.
    int m_offset,old_offset;    //
    int m_buffersize;           //The amount of widgets in the buffer
    int m_height;               //height of a widget in the list
    int m_count;                //The amount of widgets in the list
    int m_highlight;
    int m_selected;
    int m_nomoftexttodisplay;

    QList<QWidget*> albumList;
    bool m_longPress;
    QPoint m_mousePos;
    bool m_button;
    bool m_timeOut;

signals:
    void doubleClick(int);
    void endOfScroll(int);
    void longPress(int);
    void fetch(int index, int number);

private slots:
    void timeOut();

private:
    Ui::RollerWidget *ui;
};

#endif // ROLLERWIDGET_H
