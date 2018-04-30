#ifndef POINTBUTTON_H
#define POINTBUTTON_H

#include <QObject>
#include <QPushButton>
#include <QRect>
#include <QRegion>

class PointButton : public QPushButton
{
    Q_OBJECT
public:
    explicit PointButton();

public:
    float x, y;

signals:

public slots:
};

#endif // POINTBUTTON_H
