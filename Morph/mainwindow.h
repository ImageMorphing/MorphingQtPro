#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QSize>
#include <QFileDialog>
#include <QDebug>
#include <QSizePolicy>
#include <QSizeGrip>
#include <QPixmap>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QDesktopWidget>
#include "widget.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

//public slots
public slots:
    void loadImageSlot();
    void newSubWinAfterLoadImage(QStringList paths);

//private variables
private:
    Ui::MainWindow *ui;

    //for layout
    QWidget *widget, *settingWidget;
    QHBoxLayout *layout_main;

    //for widget
    Widget *customWidget;


    int numOfLabel;
    QLabel *ListOfLabels[2];
};

#endif // MAINWINDOW_H
