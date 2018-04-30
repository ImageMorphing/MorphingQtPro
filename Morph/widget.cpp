#include <QEvent>
#include <QLabel>
#include <QMouseEvent>
#include "widget.h"

Widget::Widget(QWidget *parent):QWidget(parent)
{
    setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);
    listOfLabel[0] = NULL;
    listOfLabel[1] = NULL;
    choosenLabel = NULL;
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

void Widget::CreateLabel(QPixmap *image)
{
    QLabel *label = new QLabel(this);
    label->setScaledContents(true);
    label->setPixmap(*image);
    label->resize(100, 100);
    label->installEventFilter(this);
    label->show();
    choosenLabel = label;
    if(listOfLabel[0] == NULL)
        listOfLabel[0] = label;
    else if (listOfLabel[1] == NULL)
        listOfLabel[1] = label;
    Mesh *mesh = new Mesh(label->size(), this);
    mesh->show();
}

void Widget::chooseLabel(int num){
    if(listOfLabel[num] != NULL){
        choosenLabel = listOfLabel[num];
        choosenLabel->raise();
    }
}

void Widget::scaleUpImage()
{
    if(choosenLabel != NULL){
        int width = choosenLabel->width(), height = choosenLabel->height();
        choosenLabel->resize(width * 1.1, height * 1.1);
    }
}

void Widget::scalDownImage()
{
    if(choosenLabel != NULL){
        int width = choosenLabel->width(), height = choosenLabel->height();
        choosenLabel->resize(width * 0.9, height * 0.9);
    }
}

void Widget::loadNewImage(QPixmap *image)
{
    if(choosenLabel != NULL){
        choosenLabel->setPixmap(*image);
    }
}

void Widget::deleteImage()
{
    if(choosenLabel != NULL){
        if(listOfLabel[0] == choosenLabel)
            listOfLabel[0] = NULL;
        else if(listOfLabel[1] == choosenLabel)
            listOfLabel[1] = NULL;
        delete choosenLabel;
        choosenLabel = NULL;
        if(listOfLabel[0] != NULL)
            choosenLabel = listOfLabel[0];
        else if(listOfLabel[1] != NULL)
            choosenLabel = listOfLabel[1];
    }
}


