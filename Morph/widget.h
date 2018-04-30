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
    void CreateLabel(QPixmap *image);
    void chooseLabel(int num);
    void scaleUpImage();
    void scalDownImage();
    void loadNewImage(QPixmap *image);
    void deleteImage();

private:
    QLabel *listOfLabel[2];
    QLabel *choosenLabel;
    int numOfChoosenLabel;
};
#endif // WIDGET_H
