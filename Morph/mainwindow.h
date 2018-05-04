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
#include <string>
#include <QFile>
#include "widget.h"
#include "meshtabwidget.h"
#include "main_component.h"
#include "imagesettingwidget.h"
#include "pointsettingwidget.h"

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
    void slot_loadNewImage();

//private variables
private:
    Ui::MainWindow *ui;
    void configureImageSetting();
    void configurePointSetting();
    void setChoosenLabel(int num);
    void Morphing();
    void connectSigAndSlot();
    void newSubWinAfterLoadImage(QStringList paths);
    void configureDir();
    bool copyResource();
    QStringList loadFilePath();
    QString sourcePath, targetPath;

    QWidget *widget, *settingWidget;
    imageSettingWidget *imageSetting;
    pointSettingWidget *pointSetting;
    QGridLayout *layout_main;
    QGridLayout *layout_setting, *layout_imageSetting, *layout_pointsSetting;

    //for widget
    Widget *customWidget;
    QPushButton *choosenButton;
    QPushButton *startMorphing;
};

#endif // MAINWINDOW_H
