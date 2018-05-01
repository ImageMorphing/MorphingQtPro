#include <QEvent>
#include <QLabel>
#include <QMouseEvent>
#include "widget.h"

Widget::Widget(QWidget *parent):QWidget(parent)
{
    setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);
    listOfImage[0] = NULL;
    if(listOfImage[0] != NULL);
    listOfImage[1] = NULL;
    choosenImage = NULL;
}

bool Widget::eventFilter(QObject *, QEvent *evt)
{
    static QPoint lastPnt;
    static bool isHover = false;
    if(evt->type() == QEvent::MouseButtonPress)
    {
        QMouseEvent* e = static_cast<QMouseEvent*>(evt);
        if(QRect(choosenImage->mapToGlobal(QPoint(0, 0)), QSize(choosenImage->width(), choosenImage->height())).contains(e->globalPos()))
            if(choosenImage->rect().contains(e->pos())){
                lastPnt = e->globalPos();
                isHover = true;
            }
    }
    else if(evt->type() == QEvent::MouseMove && isHover)
    {
        QMouseEvent* e = static_cast<QMouseEvent*>(evt);
        int dx = e->globalPos().x() - lastPnt.x();
        int dy = e->globalPos().y() - lastPnt.y();
        choosenImage->move(choosenImage->x() + dx, choosenImage->y() + dy);
        lastPnt = e->globalPos();
    }else if(evt->type() == QEvent::MouseButtonRelease && isHover)
    {
        isHover = false;
    }
    return false;
}

void Widget::CreateImage(QPixmap *image)
{
    installEventFilter(this);
    Mesh *mesh = new Mesh(image->size(), image, this);
    mesh->show();
    choosenImage = mesh;
    if(listOfImage[0] == NULL)
        listOfImage[0] = mesh;
    else if(listOfImage[1] == NULL)
        listOfImage[1] = mesh;
}

void Widget::chooseImage(int num){
    if(listOfImage[num] != NULL){
        choosenImage = listOfImage[num];
        choosenImage->raise();
    }
    qDebug() << num;
}

void Widget::scaleUpImage()
{
    if(choosenImage != NULL){
        int width = choosenImage->width(), height = choosenImage->height();
        choosenImage->resize(width * 1.1, height * 1.1);
    }
}

void Widget::scalDownImage()
{
    if(choosenImage != NULL){
        int width = choosenImage->width(), height = choosenImage->height();
        choosenImage->resize(width * 0.9, height * 0.9);
    }
}

void Widget::loadNewImage(QPixmap *image)
{
    if(choosenImage != NULL){
        choosenImage->setNewImage(image);
    }
}

void Widget::deleteImage()
{
    if(choosenImage != NULL){
        if(listOfImage[0] == choosenImage)
            listOfImage[0] = NULL;
        else if(listOfImage[1] == choosenImage)
            listOfImage[1] = NULL;
        delete choosenImage;
        choosenImage = NULL;
        if(listOfImage[0] != NULL)
            choosenImage = listOfImage[0];
        else if(listOfImage[1] != NULL)
            choosenImage = listOfImage[1];
    }
}


