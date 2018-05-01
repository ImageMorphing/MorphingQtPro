#ifndef POINTBUTTON_H
#define POINTBUTTON_H

#include <QObject>
#include <QPushButton>
#include <QRect>
#include <QRegion>
#include <QDebug>

class PointButton : public QPushButton
{
    Q_OBJECT
public:
    explicit PointButton(int x, int y, QWidget *parent = 0);

public:
    float x, y;
    void moveTo(float x, float y);
    int indexX, indexY;
    int sizeW, sizeH;

signals:

public slots:
};

#endif // POINTBUTTON_H
