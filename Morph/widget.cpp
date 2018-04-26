#include <QEvent>
#include <QLabel>
#include <QMouseEvent>
#include "widget.h"

Widget::Widget(QWidget *parent):QWidget(parent)
{
    setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);
//     label = new QLabel("fuck", this);
//     label->hide();
}

bool Widget::eventFilter(QObject *, QEvent *evt)
{
    static QPoint lastPnt;
    static bool isHover = false;
    static int choosenLabel = 0;
    if(evt->type() == QEvent::MouseButtonPress)
    {
        QMouseEvent* e = static_cast<QMouseEvent*>(evt);
        if(listOfLabel[0]->rect().contains(e->pos()) && //is the mouse is clicking the key
            (e->button() == Qt::LeftButton)) //if the mouse click the right key
        {
            lastPnt = e->pos();
            isHover = true;
            choosenLabel = 0;
        } else if(listOfLabel[1]->rect().contains(e->pos()) && //is the mouse is clicking the key
                  (e->button() == Qt::LeftButton)) { //if the mouse click the right key)
            lastPnt = e->pos();
            isHover = true;
            choosenLabel = 1;
        }
    }
    else if(evt->type() == QEvent::MouseMove && isHover)
    {
        QMouseEvent* e = static_cast<QMouseEvent*>(evt);
        int dx = e->pos().x() - lastPnt.x();
        int dy = e->pos().y() - lastPnt.y();
        listOfLabel[choosenLabel]->move(listOfLabel[choosenLabel]->x()+dx,listOfLabel[choosenLabel]->y()+dy);
    }else if(evt->type() == QEvent::MouseButtonRelease && isHover)
    {
        isHover = false;
    }
    return false;
}

void Widget::CreateLabel(QPixmap *image, int labelNum)
{
    QLabel *label = new QLabel(this);
    label->setScaledContents(true);
    label->setPixmap(*image);
    label->resize(100, 100);
    label->installEventFilter(this);
    label->show();
    listOfLabel[labelNum] = label;
}
