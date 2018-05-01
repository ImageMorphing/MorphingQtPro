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
}

void PointButton::moveTo(float x, float y)
{
    move(x - sizeW / 2, y - sizeH / 2);
}
