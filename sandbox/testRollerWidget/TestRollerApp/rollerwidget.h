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
    explicit RollerWidget(int aBufferSize, QWidget *parent = 0, int aNumOfTextToDisplay = 1,QColor aTextSelected=Qt::lightGray, QColor aText=Qt::blue, QColor aBackGround=Qt::white);
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
    void setBufferSize(int);                            //Sets the amount of widgets to be used locally.

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
    int m_offset,old_offset;    //
    int m_buffersize;
    int m_height;               //height of a widget in the list
    int m_count;                //The amount of items in the list
    int m_highlight;
    int m_selected;
    int m_nomoftexttodisplay;
    QColor m_background,m_text,m_textSelected,m_lineColor,m_highLightedColor,m_oldColor;
//    QStringList m_colorNames;
//    QList<QColor> m_firstColor;
//    QList<QColor> m_secondColor;
//    QPixmap *myPic;
    QList<QWidget> albumList;
//    QList<allAlbum> albumList;
    QFont *m_font1, *m_font2;
    bool m_longPress;
    QPoint m_mousePos;
    bool m_button;
    bool m_timeOut;

signals:
    void doubleClick(int);
    void endOfScroll(int);
    void longPress(int);

private slots:
    void timeOut();

private:
    Ui::RollerWidget *ui;
};

#endif // ROLLERWIDGET_H
