#include "mesh.h"

Mesh::Mesh(QSize size, QPixmap *image, QWidget *parent, int num) : QWidget(parent)
{
    sizeOfMesh = num;
    label = new QLabel(this);
    label->setPixmap(*image);
    label->resize(size);
    label->setScaledContents(true);
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
}

Mesh::~Mesh()
{
    for(int i = 0; i < sizeOfMesh; ++i)
        delete[] listOfButton[i];
}

void Mesh::setNewImage(QPixmap *image)
{
    label->setPixmap(*image);
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

void Mesh::scaleUp()
{
    resize(this->width() * 1.1, this->height() * 1.1);
    label->resize(this->width(), this->height());
    for(int i = 0; i < sizeOfMesh; ++i)
        for(int j = 0; j < sizeOfMesh; ++j){
            listOfButton[i][j]->x = j/(float)(sizeOfMesh-1) * this->size().width();
            listOfButton[i][j]->y = i/(float)(sizeOfMesh-1) * this->size().height();
            listOfButton[i][j]->moveTo(listOfButton[i][j]->x, listOfButton[i][j]->y);
        }
}

void Mesh::scaleDown()
{
    resize(this->width() * 0.9, this->height() * 0.9);
    label->resize(this->width(), this->height());
    for(int i = 0; i < sizeOfMesh; ++i)
        for(int j = 0; j < sizeOfMesh; ++j){
            listOfButton[i][j]->x = j/(float)(sizeOfMesh-1) * this->size().width();
            listOfButton[i][j]->y = i/(float)(sizeOfMesh-1) * this->size().height();
            listOfButton[i][j]->moveTo(listOfButton[i][j]->x, listOfButton[i][j]->y);
        }
}

void Mesh::storeMesh(int type)
{
    image_util *util = new image_util("../Resources/Temp");
    std::string name;
    image_ptr M = util->allo_image(sizeOfMesh, sizeOfMesh, MESH);
    int *x = (int *)M->ch[0], *y = (int *)M->ch[1];
    for(int i = 0; i < sizeOfMesh; ++i)
        for(int j = 0; j < sizeOfMesh; ++j){
            x[i*sizeOfMesh+j] = listOfButton[i][j]->x;
            y[i*sizeOfMesh+j] = listOfButton[i][j]->y;
            x++;
            y++;
        }
    if(type == 0)
        name = "1.mesh";
    else
        name = "2.mesh";
    util->save_mesh(M, name);
}
