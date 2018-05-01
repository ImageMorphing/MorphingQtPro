#include "mesh.h"

Mesh::Mesh(QSize size, QPixmap *image, QWidget *parent, int num) : QWidget(parent)
{
    sizeOfMesh = num;
    resize(size);
    setContentsMargins(0, 0, 0, 0);
    listOfButton = new PointButton**[num];
    for(int i = 0; i < num; ++i){
        listOfButton[i] = new PointButton*[num];
        for(int j = 0; j < num; ++j)
            listOfButton[i][j] = new PointButton(i, j, this);
    }
    for(int i = 0; i < num; ++i)
        for(int j = 0; j < num; ++j){
            listOfButton[i][j]->x = j/(float)(num-1);
            listOfButton[i][j]->y = i/(float)(num-1);
            listOfButton[i][j]->moveTo(listOfButton[i][j]->x * size.width(), listOfButton[i][j]->y * size.height());
            listOfButton[i][j]->show();
        }

    QPalette pal;
    pal.setBrush(backgroundRole(), QBrush(*image));
    setAutoFillBackground(true);
    setPalette(pal);
    move(10, 10);
}

Mesh::~Mesh()
{
    for(int i = 0; i < sizeOfMesh; ++i)
        delete[] listOfButton[i];
}

void Mesh::setNewImage(QPixmap *image)
{
    QPalette pal;
    pal.setBrush(backgroundRole(), QBrush(*image));
    setPalette(pal);
}
