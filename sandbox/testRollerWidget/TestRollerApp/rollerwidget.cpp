#include "rollerwidget.h"
#include "ui_rollerwidget.h"

RollerWidget::RollerWidget(int aBufferSize, QWidget *parent,int aNumOfTextToDisplay, QColor aTextSelected, QColor aText, QColor aBackGround)
    :QWidget(parent) ,
    ui(new Ui::RollerWidget)
{    
    ui->setupUi(this);
    m_buffersize = aBufferSize;
    m_offset = 0;
    m_button=false;
    m_longPress=false;
    m_timeOut=false;
    m_font1 = new QFont("Helvetica",15,1,false);
    m_font1->setPixelSize(25);
    m_font2 =new QFont("Helvetica",10,1,false);
    m_font2->setPixelSize(15);

    QApplication::setFont(*m_font1);

    m_height = QFontMetrics(font()).height() + 25;
    qDebug()<<"Font H="<<m_height;

    m_highlight = -1;
    m_selected = -1;
    m_background=aBackGround;
    m_text=aText;
    m_textSelected=aTextSelected;
    m_highLightedColor=Qt::green;
    m_lineColor=Qt::darkBlue;
    //m_nomoftexttodisplay=aNumOfTextToDisplay;
    //myPic= new QPixmap(":/pic/cover1.jpg");

    setAttribute(Qt::WA_OpaquePaintEvent, true);
    setAttribute(Qt::WA_NoSystemBackground, true);

    setMouseTracking(true);

    Flickable::setAcceptMouseClick(this);
}

RollerWidget::~RollerWidget()
{
    delete ui;
}

//public function
void RollerWidget::scrolllist(int aOffset)
{
    m_offset = aOffset;
    Flickable::setOffset(m_offset);

    update();
}

int RollerWidget::getScrollListOffset()
{
    return(m_height*count()-height());
}

int RollerWidget::getSelected()
{
    return(m_selected);
}

void RollerWidget::setBackgroundColor(QColor aColor)
{
    m_background=aColor;
}
void RollerWidget::setTextColor(QColor aColor)
{
    m_text=aColor;
}
void RollerWidget::setCount(int aNumOfItemsInList)
{
    m_count = aNumOfItemsInList;
}

void RollerWidget::setSelectedColor(QColor aColor)
{
    m_textSelected=aColor;
    m_oldColor=aColor;
}
void RollerWidget::setLineColor(QColor aColor)
{
    m_lineColor=aColor;
}
int RollerWidget::count()
{
    return m_count;//(albumList.count());
}
void RollerWidget::setNumOfTextToDisplay(int aNumOfTextToDisplay)
{
    m_nomoftexttodisplay=aNumOfTextToDisplay;
}

void RollerWidget::setHighLightedColor(QColor aColor)
{
    m_highLightedColor=aColor;
}

//reimplement protected function from flickable
QPoint RollerWidget::RollerWidget::scrollOffset() const {
    return QPoint(0, m_offset);
}

//reimplement protected function from flickable
void RollerWidget::setEndScroll()
{
    qDebug()<<"End of scroll";
    emit endOfScroll(m_offset);
}

//reimplement protected function from flickable
void RollerWidget::setScrollOffset1(const QPoint &aOffset)
{
    int yy = aOffset.y();
    if (yy != m_offset) {
        m_offset = qBound(0, yy, m_height * count() - height());
        update();
    }
}

//Protected function
void RollerWidget::mousePressEvent(QMouseEvent *aEvent) {

    if (m_timeOut==false)
    {
        qDebug()<<"Got a mouse press event in List Setting long press flag";
        m_longPress=true;
        m_textSelected=Qt::blue;
        m_button=true;
        m_mousePos=aEvent->pos();
        QTimer::singleShot(170,this,SLOT(timeOut()));
    }
    else
        m_timeOut=false;

    Flickable::handleMousePress(aEvent);

    if (aEvent->button() == Qt::LeftButton) {
        int y = aEvent->pos().y() + m_offset;
        int i = y / m_height;

        m_selected = i;
        update();
        qDebug()<<"Mouse Press i="<<i;
        if (aEvent->isAccepted())
            return;


        if (i != m_highlight) {
            m_highlight = i;
            m_selected = i;
            update();
        }
        aEvent->accept();
    }
}

//Protected function
void RollerWidget::mouseMoveEvent(QMouseEvent *aEvent) {

    if (m_button)
    {
        if (abs(aEvent->pos().y()-m_mousePos.y())>50)
        {
            m_longPress=false;
            qDebug()<<"Mouse Move more than 50px";
        }
    }
    Flickable::handleMouseMove(aEvent);
}

//protected function
void RollerWidget::mouseReleaseEvent(QMouseEvent *aEvent) {
    m_button=false;
    if (m_longPress==true)
    {
        qDebug()<<"Sending a longpress event";
        emit longPress(m_selected);
        m_longPress=false;

    }

    Flickable::handleMouseRelease(aEvent);
    if (aEvent->isAccepted())
        return;

    if (aEvent->button() == Qt::LeftButton) {
        m_selected = m_highlight;
        aEvent->accept();
        update();
    }
}

//protected function
void RollerWidget::mouseDoubleClickEvent(QMouseEvent *aEvent)
{
    aEvent->accept();
    emit doubleClick(m_selected);
}

//Private slot function
void RollerWidget::timeOut()
{
   m_textSelected=m_oldColor;
   update();
    if (m_longPress==true)
    {

     m_longPress=false;
     m_timeOut=true;
     qDebug()<<"Got a timeOut "<<m_longPress;
    }
}
