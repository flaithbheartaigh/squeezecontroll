#ifndef KINETICLIST_H
#define KINETICLIST_H

#include <QWidget>
#include <QtCore>
#include <QtGui>
#include <QFont>
#include "flickable.h"
#include "database_struct.h"
#include "qDebug.h"

class kineticList : public QWidget, public Flickable
{
    Q_OBJECT

public:

    kineticList(QWidget *parent = 0, int mNumOfTextToDisplay = 1,QColor textSelected=Qt::lightGray, QColor text=Qt::blue, QColor backGround=Qt::white)
        :QWidget(parent) {
        m_offset = 0;

        font1 = new QFont("Helvetica",15,1,false);
        font1->setPixelSize(25);
        font2 =new QFont("Helvetica",10,1,false);
        font2->setPixelSize(15);

        QApplication::setFont(*font1);

        m_height = QFontMetrics(font()).height() + 25;
        qDebug()<<"Font H="<<m_height;

        m_highlight = -1;
        m_selected = -1;
        m_background=backGround;
        m_text=text;
        m_textSelected=textSelected;
        m_highLightedColor=Qt::green;
        m_lineColor=Qt::darkBlue;
        m_nomoftexttodisplay=mNumOfTextToDisplay;
        myPic= new QPixmap(":/pic/cover1.jpg");

        setAttribute(Qt::WA_OpaquePaintEvent, true);
        setAttribute(Qt::WA_NoSystemBackground, true);

        setMouseTracking(true);

        Flickable::setAcceptMouseClick(this);
    }


    void scrolllist(int offset)
    {
        m_offset = offset;
        Flickable::setOffset(m_offset);

        update();
    }

    int getScrollListOffset()
    {
        return(m_height*albumList.count()-height());
    }

    void setList(QList<allAlbum> *p)
    {
        albumList=*p;
        update();
    }
    int getSelected()
    {
        return(m_selected);
    }
    void setBackgroundColor(QColor color)
    {
        m_background=color;
    }
    void setTextColor(QColor color)
    {
        m_text=color;
    }
    void setSelectedColor(QColor color)
    {
        m_textSelected=color;
    }
    void setLineColor(QColor color)
    {
        m_lineColor=color;
    }
    int count()
    {
        return(albumList.count());
    }
    void setNumOfTextToDisplay(int mNumOfTextToDisplay)
    {
    m_nomoftexttodisplay=mNumOfTextToDisplay;
    }

    void setHighLightedColor(QColor color)
    {
        m_highLightedColor=color;
    }

protected:
    // reimplement from Flickable
    virtual QPoint scrollOffset() const {
        return QPoint(0, m_offset);
    }
    virtual void setEndScroll()
    {
        qDebug()<<"End of scroll";
        emit endOfScroll(m_offset);
    }
    // reimplement from Flickable
    virtual void setScrollOffset1(const QPoint &offset) {
        int yy = offset.y();
        if (yy != m_offset) {
            m_offset = qBound(0, yy, m_height * albumList.count() - height());

            update();
        }
    }


protected:
    void paintEvent(QPaintEvent *event) {
        QPainter p(this);
        p.fillRect(event->rect(), m_background);
        int start = m_offset / m_height;
        int y = start * m_height - m_offset;

        if (m_offset <= 0) {
            start = 0;
            y = -m_offset;
        }
        int end = start + height() / m_height + 1;
        if (end > albumList.count() - 1)
            end = albumList.count() - 1;
        for (int i = start; i <= end; ++i, y += m_height) {

            p.setBrush(Qt::NoBrush);
            p.setPen(m_text);

            //            p.setPen(m_text);
            //            if (i == m_highlight) {
            //                p.fillRect(0, y, width(), m_height, Qt::white);
            //                p.setPen(m_background);

            //            }
            if (i == m_selected) {
                p.fillRect(0, y, width(), m_height, m_textSelected);
                p.setPen(Qt::white);
            }
            //p.drawPixmap(0,y+2,55,55,albumList.at(i).AlbumArt);
            //p.drawPixmap(0,y+2,55,55,*myPic);
            if (m_nomoftexttodisplay==2)
            {
                p.setFont(*font1);
                p.drawText(0, y-10, width(), m_height, Qt::AlignVCenter, albumList.at(i).albumName);
                p.setFont(*font2);
                p.drawText(0, y+10, width(), m_height, Qt::AlignVCenter, albumList.at(i).albumArtist);
            }
            else
                p.drawText(0, y, width(), m_height, Qt::AlignVCenter, albumList.at(i).albumName);
            //p.drawText(m_height + 2, y  , width(), m_height, Qt::AlignVCenter, "Hej");
            //p.drawText(m_height + 2, y+20, width(), m_height, Qt::AlignVCenter, "Med dig");
            p.setPen(m_lineColor);
            p.drawLine(0,y,width(),y);
            p.setPen(m_text);
        }
        p.end();

    }
    void keyReleaseEvent(QKeyEvent *event) {
        if (event->key() == Qt::Key_Down) {
            m_offset += 20;
            event->accept();
            update();
            return;
        }
        if (event->key() == Qt::Key_Up) {
            m_offset -= 20;
            event->accept();
            update();
            return;
        }
    }



    void mousePressEvent(QMouseEvent *event) {

        Flickable::handleMousePress(event);

        if (event->button() == Qt::LeftButton) {
            int y = event->pos().y() + m_offset;
            int i = y / m_height;

            m_selected = i;
            update();
            qDebug()<<"Mouse Press i="<<i;
            if (event->isAccepted())
                return;


            if (i != m_highlight) {
                m_highlight = i;
                m_selected = i;
                update();
            }
            event->accept();
        }
    }

    void mouseMoveEvent(QMouseEvent *event) {
        Flickable::handleMouseMove(event);
    }

    void mouseReleaseEvent(QMouseEvent *event) {
        Flickable::handleMouseRelease(event);
        if (event->isAccepted())
            return;

        if (event->button() == Qt::LeftButton) {
            m_selected = m_highlight;
            event->accept();
            update();
        }
    }
    void mouseDoubleClickEvent(QMouseEvent *event){
        event->accept();
        emit doubleClick(m_selected);
    }

private:
    int m_offset;
    int m_height;
    int m_highlight;
    int m_selected;
    int m_nomoftexttodisplay;
    QColor m_background,m_text,m_textSelected,m_lineColor,m_highLightedColor;
    QStringList m_colorNames;
    QList<QColor> m_firstColor;
    QList<QColor> m_secondColor;
    QPixmap *myPic;
    QList<allAlbum> albumList;
    QFont *font1, *font2;

signals:
    void doubleClick(int);
    void endOfScroll(int);
};

#endif
