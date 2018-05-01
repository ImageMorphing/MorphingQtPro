#ifndef POINTBUTTON_H
#define POINTBUTTON_H

#include <QObject>
#include <QPushButton>
#include <QRect>
#include <QRegion>
#include <QPoint>
#include <QDebug>
#include <QMouseEvent>

class PointButton : public QPushButton
{
    Q_OBJECT
public:
    explicit PointButton(int x, int y, QWidget *parent = 0);
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);

public:
    float x, y;
    void moveTo(float x, float y);
    int indexX, indexY;
    int sizeW, sizeH;

private:
    bool isHover;
    QPoint dPos;

public slots:
};

#endif // POINTBUTTON_H
