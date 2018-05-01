#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->resize(QApplication::desktop()->width(), QApplication::desktop()->height());

    numOfLabel = 0;

    //set mainWindow layout
    widget = new QWidget();
    settingWidget = new QWidget();
    customWidget = new Widget(this);
    imageSettingWidget = new QWidget();
    pointSettingWidget = new QWidget();
    layout_main = new QHBoxLayout();
    layout_imageSetting = new QGridLayout();
    layout_setting = new QGridLayout();
    layout_pointsSetting = new QGridLayout();

    settingWidget->setFixedWidth(230);
    customWidget->show();

    layout_main->addWidget(settingWidget);
    layout_main->addWidget(customWidget);

    configureImageSetting();
    configurePointSetting();

    imageSettingWidget->setLayout(layout_imageSetting);
    pointSettingWidget->setLayout(layout_pointsSetting);
    layout_setting->addWidget(imageSettingWidget);
    layout_setting->addWidget(pointSettingWidget);
    settingWidget->setLayout(layout_setting);


    widget->setLayout(layout_main);
    this->setCentralWidget(widget);

    connect(ui->load, SIGNAL(triggered()), this, SLOT(slot_loadImage()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slot_loadImage()
{
    QStringList fileNames= loadFilePath();
    newSubWinAfterLoadImage(fileNames);
    setChoosenLabel(numOfLabel-1);
}

QStringList MainWindow::loadFilePath(){
    QFileDialog *fileDialog = new QFileDialog(this);
    fileDialog->setWindowTitle(tr("打开图片"));
    fileDialog->setDirectory(".");
    fileDialog->setNameFilter(tr("Images(*.png *.jpg *.jpeg *.bmp)"));
    //设置可以选择多个文件,默认为只能选择一个文件QFileDialog::ExistingFiles
//    fileDialog->setFileMode(QFileDialog::ExistingFiles);
    fileDialog->setViewMode(QFileDialog::Detail);
    QStringList fileNames;
    if(fileDialog->exec())
        fileNames = fileDialog->selectedFiles();
    return fileNames;
}

void MainWindow::newSubWinAfterLoadImage(QStringList paths)
{
    if(numOfLabel >= 2){
        QMessageBox::information(NULL, "提示", "导入的图片不能超过两个", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        return;
    }
    //根据路径载入图片
    //需要修改：多选图片时
    if(paths.count() > 0){
    QString path = paths.at(0);
    QPixmap *image = new QPixmap(path);
    if(image->isNull()){
        QMessageBox::information(NULL, "提示", "请选择图片", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        return;
    }
    customWidget->CreateImage(image);
    ++numOfLabel;
    }
}

void MainWindow::configureImageSetting(){
    QPushButton *sourceImageButton, *targetImageButton;
    QPushButton *scaleUpButton, *scaleDownButton, *loadNewImageButton, *deleteImageButton;
    sourceImageButton = new QPushButton();
    targetImageButton = new QPushButton();
    scaleUpButton = new QPushButton();
    scaleDownButton = new QPushButton();
    loadNewImageButton = new QPushButton();
    deleteImageButton = new QPushButton();


    sourceImageButton->setFixedSize(100, 100);
    sourceImageButton->setText("源图片");
    sourceImageButton->setFlat(true);
    targetImageButton->setFixedSize(100, 100);
    targetImageButton->setText("目标图片");
    targetImageButton->setFlat(true);

    scaleUpButton->setText("放大图片");
    scaleDownButton->setText("缩小图片");
    loadNewImageButton->setText("切换图片");
    deleteImageButton->setText("删除图片");

    connect(sourceImageButton, &QPushButton::clicked, this, &MainWindow::slot_sourceImageButtonClicked);
    connect(targetImageButton, &QPushButton::clicked, this, &MainWindow::slot_targetImageButtonClicked);
    connect(scaleUpButton, &QPushButton::clicked, this, &MainWindow::slot_scaleUpButton);
    connect(scaleDownButton, &QPushButton::clicked, this, &MainWindow::slot_scaleDownButton);
    connect(loadNewImageButton, &QPushButton::clicked, this, &MainWindow::slot_loadNewImageButton);
    connect(deleteImageButton, &QPushButton::clicked, this, &MainWindow::slot_deleteImageButton);

    this->layout_imageSetting->addWidget(sourceImageButton, 0, 0);
    this->layout_imageSetting->addWidget(targetImageButton, 0, 1);
    this->layout_imageSetting->addWidget(scaleUpButton, 1, 0);
    this->layout_imageSetting->addWidget(scaleDownButton, 1, 1);
    this->layout_imageSetting->addWidget(loadNewImageButton, 2, 0);
    this->layout_imageSetting->addWidget(deleteImageButton, 2, 1);
}

void MainWindow::configurePointSetting(){
    QTabWidget *tab = new QTabWidget();
    QWidget *meshTab, *pointsTab, *contourTab;
    meshTab = new QWidget();
    pointsTab = new QWidget();
    contourTab = new QWidget();
    tab->addTab(meshTab, "网格");
    tab->addTab(pointsTab, "选点");
    tab->addTab(contourTab, "轮廓");
    layout_pointsSetting->addWidget(tab);
}

void MainWindow::slot_sourceImageButtonClicked(){
    setChoosenLabel(0);
}

void MainWindow::slot_targetImageButtonClicked(){
    setChoosenLabel(1);
}

void MainWindow::setChoosenLabel(int num){
    this->customWidget->chooseImage(num);
//    qDebug() << num;
}

void MainWindow::slot_scaleUpButton(){
    this->customWidget->scaleUpImage();
}

void MainWindow::slot_scaleDownButton()
{
    this->customWidget->scalDownImage();
}

void MainWindow::slot_loadNewImageButton()
{
    QStringList paths = loadFilePath();
    QString path = paths.at(0);
    QPixmap *image = new QPixmap(path);
    if(image->isNull()){
        QMessageBox::information(NULL, "提示", "请选择图片", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        return;
    }
    this->customWidget->loadNewImage(image);
}

void MainWindow::slot_deleteImageButton()
{
    this->customWidget->deleteImage();
    numOfLabel--;
}
