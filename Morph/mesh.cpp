#include "mesh.h"

Mesh::Mesh(QSize size, QWidget *parent, int num) : QWidget(parent)
{
    sizeOfMesh = num;
    resize(size);
//    setContentsMargins(-10, -10, -10, -10);

    listOfPoints = new PointButton*[num];
    for(int i = 0; i < num; ++i)
        listOfPoints[i] = new PointButton[num];
    for(int i = 0; i < num; ++i)
        for(int j = 0; j < num; ++j){
            listOfPoints[i][j].x = j/num;
            listOfPoints[i][j].y = i/num;
        }

    layout_points = new QGridLayout();
    for(int i = 0; i < num; ++i)
        for(int j = 0; j < num; ++j)
            layout_points->addWidget(&listOfPoints[i][j], i, j);
    setLayout(layout_points);
}

Mesh::~Mesh()
{
    for(int i = 0; i < sizeOfMesh; ++i)
        delete[] listOfPoints[i];
}
