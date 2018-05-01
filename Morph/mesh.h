#ifndef MESH_H
#define MESH_H

#include <QWidget>
#include <QGridLayout>
#include <QPalette>
#include <QDebug>
#include <QPixmap>
#include "pointbutton.h"

class Mesh : public QWidget
{
    Q_OBJECT
public:
    Mesh(QSize size, QPixmap *image, QWidget *partent = 0, int num = 5);
    ~Mesh();
    void setNewImage(QPixmap *image);

private:
    PointButton ***listOfButton;
    QGridLayout *layout_points;
    int sizeOfMesh;

signals:

public slots:
};

#endif // MESH_H
