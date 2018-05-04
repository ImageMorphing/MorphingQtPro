#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->resize(QApplication::desktop()->width(), QApplication::desktop()->height());

    //set mainWindow layout
    widget = new QWidget();
    settingWidget = new QWidget();
    customWidget = new Widget(this);
    imageSetting = new imageSettingWidget(this);
    pointSetting = new pointSettingWidget(this);
    layout_main = new QGridLayout();
    layout_imageSetting = new QGridLayout();
    layout_setting = new QGridLayout();
    layout_pointsSetting = new QGridLayout();
    startMorphing = new QPushButton();

    QWidget *tmpWid = new QWidget(this);
    QGridLayout *layout_tmpWid = new QGridLayout();
    tmpWid->setFixedWidth(230);
    layout_tmpWid->addWidget(imageSetting, 0, 0, 3, 1);
    layout_tmpWid->addWidget(pointSetting, 3, 0, 5, 1);
    layout_tmpWid->addWidget(startMorphing, 8, 0, 1, 1);
    tmpWid->setLayout(layout_tmpWid);

    customWidget->show();
    startMorphing->setText("Start");

    layout_main->addWidget(tmpWid, 0, 0);
    layout_main->addWidget(customWidget, 0, 1);
    widget->setLayout(layout_main);
    this->setCentralWidget(widget);

    connect(ui->load, SIGNAL(triggered()), this, SLOT(slot_loadImage()));
    connect(startMorphing, &QPushButton::clicked, this, &MainWindow::Morphing);
    connectSigAndSlot();
    configureDir();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slot_loadImage()
{
    QStringList fileNames= loadFilePath();
    if(fileNames.count() > 0){
        newSubWinAfterLoadImage(fileNames);
    }
}

void MainWindow::slot_loadNewImage()
{
    QStringList fileName = loadFilePath();
    if(fileName.count() > 0){
        QString path = fileName.at(0);
        QPixmap *image = new QPixmap(path);
        if(!image->isNull()){
            customWidget->loadNewImage(image);
            imageSetting->changeIcononChangingImage(image);
            if(customWidget->sourOrDest() == 0)
                sourcePath = path;
            else if(customWidget->sourOrDest() == 1)
                targetPath = path;
        }else
            QMessageBox::information(NULL, "提示", "请选择图片", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    }
}

QStringList MainWindow::loadFilePath(){
    QFileDialog *fileDialog = new QFileDialog(this);
    fileDialog->setWindowTitle(tr("打开图片"));
    fileDialog->setDirectory(".");
    fileDialog->setNameFilter(tr("Images(*.png *.jpg *.jpeg *.bmp)"));
    fileDialog->setViewMode(QFileDialog::Detail);
    QStringList fileNames;
    if(fileDialog->exec())
        fileNames = fileDialog->selectedFiles();
    return fileNames;
}

void MainWindow::newSubWinAfterLoadImage(QStringList paths)
{
    if(!customWidget->readyToLoadNew()){
        QMessageBox::information(NULL, "提示", "导入的图片不能超过两个", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        return;
    }
    //根据路径载入图片
    //需要修改：多选图片时
    if(paths.count() > 0){
        QString path = paths.at(0);
        QPixmap *image = new QPixmap(path);
        if(!image->isNull()){
            customWidget->CreateImage(image);
            imageSetting->changeIcononLoadingNew(image);
            if(customWidget->sourOrDest() == 0)
                sourcePath = path;
            else if(customWidget->sourOrDest() == 1)
                targetPath = path;
        }else
            QMessageBox::information(NULL, "提示", "请选择图片", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    }
}

void MainWindow::configureDir()
{
    QDir *temp = new QDir();
    bool exist = temp->exists("../Resources/Temp");
    if(!exist)
        temp->mkdir("../Resources/Temp");
}

bool MainWindow::copyResource()
{
    QString sName, dName;
    QStringList tmp1, tmp2;
    tmp1 = sourcePath.split("/");
    tmp2 = targetPath.split("/");
    sName = tmp1.at(tmp1.size()-1);
    dName = tmp2.at(tmp2.size()-1);
    QString path = "../Resources/Temp";
    if(!QFile::exists(path)){
        QDir *temp = new QDir();
        temp->mkdir("../Resources/Temp");
    }
    if(QFile::exists(path + QDir::separator() + sName))
        QFile::remove(path + QDir::separator() + sName);
    if(QFile::exists(path + QDir::separator() + dName))
        QFile::remove(path + QDir::separator() + dName);
    if(!QFile::copy(sourcePath, path + QDir::separator() + sName)){
//        QMessageBox::information(NULL, "提示", "请重试", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        return false;
    }
    if(!QFile::copy(targetPath, path + QDir::separator() + dName)){
//        QMessageBox::information(NULL, "提示", "请重试", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        return false;
    }
    return true;
}

void MainWindow::Morphing()
{
    if(customWidget->readyToStoreMesh()){
        QString sName, dName;
        QStringList tmp1, tmp2;
        tmp1 = sourcePath.split("/");
        tmp2 = targetPath.split("/");
        sName = tmp1.at(tmp1.size()-1);
        dName = tmp2.at(tmp2.size()-1);
        customWidget->storeMesh();
        if(!copyResource())
            return;
        main_component *morph = new main_component("../Resources/Temp", "job", pointSetting->numOfFrame());
        morph->execute(sName.toStdString(), dName.toStdString());
    }
}

void MainWindow::connectSigAndSlot()
{
    connect(imageSetting, &imageSettingWidget::chooseSourceImage, customWidget, &Widget::chooseImage);
    connect(imageSetting, &imageSettingWidget::chooseDestImage, customWidget, &Widget::chooseImage);
    connect(imageSetting, &imageSettingWidget::scaleUp, customWidget, &Widget::scaleUpImage);
    connect(imageSetting, &imageSettingWidget::scaleDown, customWidget, &Widget::scalDownImage);
    connect(imageSetting, &imageSettingWidget::loadNewImage, this, &MainWindow::slot_loadNewImage);
    connect(imageSetting, &imageSettingWidget::deleteImage, customWidget, &Widget::deleteImage);
    connect(pointSetting, &pointSettingWidget::startChoosing, customWidget, &Widget::showMesh);
    connect(pointSetting, &pointSettingWidget::finishChoosing, customWidget, &Widget::hideMesh);

}
