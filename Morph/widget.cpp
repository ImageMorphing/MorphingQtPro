#include <QEvent>
#include <QLabel>
#include <QMouseEvent>
#include "widget.h"

Widget::Widget(QWidget *parent):QWidget(parent)
{
    setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);
}

bool Widget::eventFilter(QObject *, QEvent *evt)
{
    static QPoint lastPnt;
    static bool isHover = false;
    if(evt->type() == QEvent::MouseButtonPress)
    {
        QMouseEvent* e = static_cast<QMouseEvent*>(evt);
        if(QRect(choosenLabel->mapToGlobal(QPoint(0, 0)), QSize(choosenLabel->width(), choosenLabel->height())).contains(e->globalPos()))
            if(choosenLabel->rect().contains(e->pos())){
                lastPnt = e->pos();
                isHover = true;
            }
    }
    else if(evt->type() == QEvent::MouseMove && isHover)
    {
        QMouseEvent* e = static_cast<QMouseEvent*>(evt);
        int dx = e->pos().x() - lastPnt.x();
        int dy = e->pos().y() - lastPnt.y();
        choosenLabel->move(choosenLabel->x() + dx, choosenLabel->y() + dy);
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
    choosenLabel = label;
    listOfLabel[labelNum] = label;
}

void Widget::chooseLabel(int num){
    choosenLabel = listOfLabel[num];
}
