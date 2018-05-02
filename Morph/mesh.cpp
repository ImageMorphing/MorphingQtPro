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
            listOfButton[i][j]->x = j/(float)(num-1) * size.width();
            listOfButton[i][j]->y = i/(float)(num-1) * size.height();
            listOfButton[i][j]->moveTo(listOfButton[i][j]->x, listOfButton[i][j]->y);
            listOfButton[i][j]->hide();
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

void Mesh::showButton(int size)
{
    if(sizeOfMesh != size){
        for(int i = 0; i < sizeOfMesh; ++i){
            for(int j = 0; j < sizeOfMesh; ++j)
                delete listOfButton[i][j];
            delete[] listOfButton[i];
        }
        delete listOfButton;
        listOfButton = NULL;
        sizeOfMesh = size;
        listOfButton = new PointButton**[size];
        for(int i = 0; i < size; ++i){
            listOfButton[i] = new PointButton*[size];
            for(int j = 0; j < size; ++j)
                listOfButton[i][j] = new PointButton(i, j, this);
        }
        for(int i = 0; i < size; ++i)
            for(int j = 0; j < size; ++j){
                listOfButton[i][j]->x = j/(float)(size-1) * this->size().width();
                listOfButton[i][j]->y = i/(float)(size-1) * this->size().height();
                listOfButton[i][j]->moveTo(listOfButton[i][j]->x, listOfButton[i][j]->y);
                listOfButton[i][j]->show();
            }
    } else {
    for(int i = 0; i < sizeOfMesh; ++i)
        for(int j = 0; j < sizeOfMesh; ++j)
            listOfButton[i][j]->show();
    }
}

void Mesh::hideButton()
{
    for(int i = 0; i < sizeOfMesh; ++i)
        for(int j = 0; j < sizeOfMesh; ++j)
            listOfButton[i][j]->hide();
}
