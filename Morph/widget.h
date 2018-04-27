#ifndef WIDGET_H
#define WIDGET_H
#include <QWidget>
#include <QLabel>
#include <QPixmap>
#include <QDebug>
class Widget : public QWidget
{
    Q_OBJECT
public:
    Widget(QWidget *parent = 0);
protected slots:
    bool eventFilter(QObject *, QEvent *);

public:
    void CreateLabel(QPixmap *image, int labelNum);

private:
    QLabel *listOfLabel[2];
    QLabel *choosenLabel;
    void chooseLabel(int num);
//    QLabel *label;
};
#endif // WIDGET_H
