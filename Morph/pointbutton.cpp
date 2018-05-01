#include "pointbutton.h"

PointButton::PointButton(int x, int y, QWidget *parent) : QPushButton(parent)
{
    sizeW = 13, sizeH = 13;
    setFixedWidth(15);
    setFixedHeight(15);
    QRect *rect = new QRect(0, 0, sizeW, sizeH);
    QRegion *region = new QRegion(*rect, QRegion::Ellipse);
    setMask(*region);
    indexX = x;
    indexY = y;
    isHover = false;
//    installEventFilter(this);
}

void PointButton::moveTo(float x, float y)
{
    move(x - sizeW / 2, y - sizeH / 2);
}

void PointButton::mousePressEvent(QMouseEvent *e){
    dPos = e->globalPos() - this->pos();
    isHover = true;
}

void PointButton::mouseMoveEvent(QMouseEvent *e){
    if(isHover == true){
        this->move(e->globalPos() - dPos);
        x = this->pos().x();
        y = this->pos().y();
    }
}

void PointButton::mouseReleaseEvent(QMouseEvent *e){
    isHover = false;
}
