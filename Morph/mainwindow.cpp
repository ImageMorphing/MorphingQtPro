#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QDebug>
#include <QSizePolicy>
#include <QSizeGrip>
#include <QPixmap>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->loadImage, SIGNAL(triggered()), this, SLOT(loadImageSlot()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadImageSlot()
{
    //定义文件对话框类
    QFileDialog *fileDialog = new QFileDialog(this);
    //定义文件对话框标题
    fileDialog->setWindowTitle(tr("打开图片"));
    //设置默认文件路径
    fileDialog->setDirectory(".");
    //设置文件过滤器
    fileDialog->setNameFilter(tr("Images(*.png *.jpg *.jpeg *.bmp)"));
    //设置可以选择多个文件,默认为只能选择一个文件QFileDialog::ExistingFiles
//    fileDialog->setFileMode(QFileDialog::ExistingFiles);
    //设置视图模式
    fileDialog->setViewMode(QFileDialog::Detail);
    //打印所有选择的文件的路径
    QStringList fileNames;
    if(fileDialog->exec())
    {
        fileNames = fileDialog->selectedFiles();
    }
    newSubWinAfterLoadImage(fileNames);
}

void MainWindow::newSubWinAfterLoadImage(QStringList paths)
{
    //初始化子窗口
    newWin = new QMdiSubWindow();
    newWin->resize(100, 100);
    newWin->setWindowFlags(Qt::SubWindow);
    newWin->setWindowTitle("test");
    newWin->setAttribute(Qt::WA_DeleteOnClose);
    newWin->setGeometry(100, 100, 30, 30);

    //根据路径载入图片
    //需要修改：多选图片时
    QString path = paths.at(0);
    QLabel *imageLabel = new QLabel();
    QPixmap *image = new QPixmap(path);
    imageLabel->resize(newWin->width(), newWin->height());
    image->scaled(imageLabel->size(), Qt::KeepAspectRatio);
    imageLabel->setScaledContents(true);
    imageLabel->setPixmap(*image);

    //设置子窗口layout，添加控件
    QWidget *widget = new QWidget();
    newWin->setWidget(widget);
    QGridLayout *layout_main = new QGridLayout(widget);
    layout_main->setMargin(15);
    layout_main->setSpacing(10);
    layout_main->addWidget(imageLabel);
    widget->setLayout(layout_main);
    widget->resize(newWin->width(), newWin->height());

    //添加子窗口到主窗口
    ui->mdiArea->addSubWindow(newWin);
    newWin->show();
}

