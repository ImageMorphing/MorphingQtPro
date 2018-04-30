#ifndef MESH_H
#define MESH_H

#include <QWidget>
#include <QGridLayout>
#include "pointbutton.h"

class Mesh : public QWidget
{
    Q_OBJECT
public:
    Mesh(QSize size, QWidget *partent = 0, int num = 5);
    ~Mesh();

private:
    PointButton **listOfPoints;
    QGridLayout *layout_points;
    int sizeOfMesh;

signals:

public slots:
};

#endif // MESH_H
