#ifndef WIDGET_H
#define WIDGET_H
#include <QWidget>
#include <QLabel>
#include <QPixmap>
#include <QDebug>
#include "mesh.h"
class Widget : public QWidget
{
    Q_OBJECT
public:
    Widget(QWidget *parent = 0);
protected slots:
    bool eventFilter(QObject *, QEvent *);

public:
    void CreateImage(QPixmap *image);
    void chooseImage(int num);
    void scaleUpImage();
    void scalDownImage();
    void loadNewImage(QPixmap *image);
    void deleteImage();

private:
    Mesh *listOfImage[2];
    Mesh *choosenImage;
    int numOfChoosenLabel;
};
#endif // WIDGET_H
