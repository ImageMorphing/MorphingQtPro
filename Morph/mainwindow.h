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
#include <QPushButton>
#include <QRadioButton>
#include <QTabWidget>
#include "widget.h"
#include "meshtabwidget.h"

#include <image_portrait_processor.h>

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
    void slot_loadImage();
    void newSubWinAfterLoadImage(QStringList paths);
    void slot_sourceImageButtonClicked();
    void slot_targetImageButtonClicked();
    void slot_scaleUpButton();
    void slot_scaleDownButton();
    void slot_loadNewImageButton();
    void slot_deleteImageButton();

//private variables
private:
    Ui::MainWindow *ui;

    void configureImageSetting();
    void configurePointSetting();
    void setChoosenLabel(int num);
    QStringList loadFilePath();

    //for layout
    QWidget *widget, *settingWidget;
    QWidget *imageSettingWidget, *pointSettingWidget;

    QHBoxLayout *layout_main;
    QGridLayout *layout_setting, *layout_imageSetting, *layout_pointsSetting;

    //for widget
    Widget *customWidget;


    int numOfLabel;
    QLabel *ListOfLabels[2];
};

#endif // MAINWINDOW_H
