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
    if(evt->type() == QEvent::MouseButtonPress)
    {
        QMouseEvent* e = static_cast<QMouseEvent*>(evt);
        if(QRect(choosenLabel->mapToGlobal(QPoint(0, 0)), QSize(choosenLabel->width(), choosenLabel->height())).contains(e->globalPos()))
            if(choosenLabel->rect().contains(e->pos())){
                lastPnt = e->pos();
                isHover = true;
            }
        qDebug() << "Label size: " << choosenLabel->width() << " " << choosenLabel->height();
        qDebug() << "全局：" << e->globalPos();
        qDebug() << "局部：" << e->pos();
//        qDebug() << "Label：" << choosenLabel->pos();
        //        if(listOfLabel[0] != NULL && QRect(/*listOfLabel[0]->x()*/0, /*listOfLabel[0]->y()*/0, listOfLabel[0]->width(), listOfLabel[0]->height()).contains(e->pos()) && //is the mouse is clicking the key
        //                (e->button() == Qt::LeftButton)) //if the mouse click the right key
        //        {
        //            lastPnt = e->pos();
//            isHover = true;
//            choosenLabel = 0;
//            qDebug() << "label " << choosenLabel << " is choosen";
//            qDebug() << lastPnt.x() << " " << lastPnt.y();
//        } else if(listOfLabel[1] != NULL && QRect(listOfLabel[1]->x(), listOfLabel[1]->y(), listOfLabel[1]->width(), listOfLabel[1]->height()).contains(e->pos()) && //is the mouse is clicking the key
//                  (e->button() == Qt::LeftButton)) { //if the mouse click the right key)
//            lastPnt = e->pos();
//            isHover = true;
//            choosenLabel = 1;
//            qDebug() << "label " << choosenLabel << " is choosen";
//            qDebug() << lastPnt.x() << " " << lastPnt.y();
//        }
    }
    else if(evt->type() == QEvent::MouseMove && isHover)
    {
        QMouseEvent* e = static_cast<QMouseEvent*>(evt);
        int dx = e->pos().x() - lastPnt.x();
        int dy = e->pos().y() - lastPnt.y();
//        qDebug() << "mouse now at" << e->pos();
//        qDebug() << "moves " << dx << " " << dy;
        choosenLabel->move(choosenLabel->x() + dx, choosenLabel->y() + dy);
//        listOfLabel[choosenLabel]->move(listOfLabel[choosenLabel]->x()+dx,listOfLabel[choosenLabel]->y()+dy);
//        qDebug() << "label " << choosenLabel << "now " << listOfLabel[choosenLabel]->x() << " " << listOfLabel[choosenLabel]->y();
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
