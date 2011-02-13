#include "rollerwidget.h"
#include "ui_rollerwidget.h"

RollerWidget::RollerWidget(int aBufferSize, int aWidgetHeight, QWidget *parent,int aNumOfTextToDisplay, QColor aTextSelected, QColor aText, QColor aBackGround)
    :QWidget(parent) ,
    ui(new Ui::RollerWidget)
{    
    ui->setupUi(this);
    m_buffersize = aBufferSize;
    m_ScrollDirectionDown = true; //Makes sure that the populating the list happend to end of list
    m_pending_fetch = aBufferSize; //owner will have to addWidgets aBufferTimes before the update is called.
    m_offset = 0;
    old_offset = 0;
    m_button=false;
    m_longPress=false;
    m_timeOut=false;

    //QApplication::setFont(*m_font1);

    m_height = aWidgetHeight;//QFontMetrics(font()).height() + 25;
    qDebug()<<"Font H="<<m_height;

    m_highlight = -1;
    m_selected = -1;





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

void RollerWidget::setCount(int aNumOfItemsInList)
{
    m_count = aNumOfItemsInList;
}

//public function
void RollerWidget::addWidget(QWidget* aWidget)
{
    aWidget->setParent(ui->frame);
    if(m_ScrollDirectionDown)
    {
        aWidget->move(0,albumList.count()*m_height-m_offset%m_height);
        aWidget->show();
        albumList.append(aWidget);
    }
    else
    {
        aWidget->move(0,m_pending_fetch*m_height+m_offset%m_height);
        aWidget->show();
        albumList.prepend(aWidget);
    }
    m_pending_fetch--;
    if(m_pending_fetch == 0)
    {
        moveWidgets();
    }
}

int RollerWidget::count()
{
    return m_count;//(albumList.count());
}
void RollerWidget::setNumOfTextToDisplay(int aNumOfTextToDisplay)
{
    m_nomoftexttodisplay=aNumOfTextToDisplay;
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
    //calculate what elements are to be fetched old Index = m_offset / m_height
    old_offset = m_offset;
    int oldIndex = m_offset/m_height;
    int newIndex;
    int yy = aOffset.y();    
    if (yy != m_offset) {
        m_offset = qBound(0, yy, m_height * count() - height());
        if(m_offset>old_offset)
            m_ScrollDirectionDown = true;
        else
            m_ScrollDirectionDown = false;

        newIndex = m_offset/m_height;
        qDebug() << "Offset = " << aOffset << " m_offset " << m_offset << " oldIndex = " << oldIndex << " newIndex = " << newIndex << "offset % m_height = " << m_offset%m_height;
        //fetch the widgets by emiting signals and delete obsolete widgets
        //If newIndex > OldIndex -> We are moving down the list
        //The items to be fetched are newIndex to newIndex+m_buffersize
        if(newIndex>oldIndex)
        {           
            m_pending_fetch = newIndex-oldIndex;
            //if delta index is larger than buffer, we have a problem
            for(int i = 0; i< m_pending_fetch; i++)
            {
                QWidget* temp =  albumList.takeFirst(); //hack to show something right now
                albumList.append(temp);//hack
                qDebug() << "remove first";
                //albumList.removeFirst();
            }
            emit fetch(oldIndex+m_buffersize-(newIndex-oldIndex), newIndex-oldIndex );
            qDebug() << "fetch " << oldIndex+m_buffersize-(newIndex-oldIndex) + 1 << ", " << newIndex-oldIndex;
        }
        else if (oldIndex>newIndex)
        {
            m_pending_fetch = oldIndex-newIndex;
            m_ScrollDirectionDown = false;
            for(int i=0; i< oldIndex-newIndex; i++)
            {                
                qDebug() << "remove last";
                QWidget* temp =  albumList.takeLast(); //hack to show something right now
                albumList.prepend(temp);
                //albumList.removeLast();
            }
            emit fetch(newIndex , oldIndex-newIndex);
            qDebug() << "fetch " << newIndex << ", " << oldIndex-newIndex;
        }
        else //no index change. Force move
        {
            moveWidgets();
        }
        //update();
    }
}

//Protected function
void RollerWidget::mousePressEvent(QMouseEvent *aEvent) {

    if (m_timeOut==false)
    {
        qDebug()<<"Got a mouse press event in List Setting long press flag";
        m_longPress=true;

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
//Private function
void RollerWidget::moveWidgets()
{
    int direction =1;
    if (m_ScrollDirectionDown == true)
        direction = -1;

    for(int i=0;i<albumList.count();i++)
    {
        albumList.at(i)->move(0, m_offset%m_height *direction + i*m_height);
    }
    update();
}

//Private slot function
void RollerWidget::timeOut()
{

   update();
    if (m_longPress==true)
    {

     m_longPress=false;
     m_timeOut=true;
     qDebug()<<"Got a timeOut "<<m_longPress;
    }
}
