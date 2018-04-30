#include "pointbutton.h"

PointButton::PointButton()
{
    setFixedWidth(10);
    setFixedHeight(10);
    QRect *rect = new QRect(0, 0, 8, 8);
    QRegion *region = new QRegion(*rect, QRegion::Ellipse);
    setMask(*region);
}
