#ifndef MESH_H
#define MESH_H

#include <QWidget>
#include <QGridLayout>
#include <QPalette>
#include <QDebug>
#include <QPixmap>
#include <QLabel>
#include <string>
#include <QDir>
#include "pointbutton.h"
#include "typedef_cxx.h"
#include "image_util.h"
#include "image_io_processor.h"


class Mesh : public QWidget
{
    Q_OBJECT
public:
    Mesh(QSize size, QPixmap *image, QWidget *partent = 0, int num = 5);
    ~Mesh();
    void setNewImage(QPixmap *image);

    void showButton(int size);
    void hideButton();

    void scaleUp();
    void scaleDown();

    void storeMesh(int type);

private:
    PointButton ***listOfButton;
    QGridLayout *layout_points;
    int sizeOfMesh;
//    QPixmap imagePixmap;
    QLabel *label;

signals:

public slots:
};

#endif // MESH_H
