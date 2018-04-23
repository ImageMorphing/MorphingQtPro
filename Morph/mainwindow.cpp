#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QDebug>
#include <QSizePolicy>


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
    int imageNumber = paths.count();
    QString path = paths.at(0);
    QLabel *imageLabel = new QLabel;
    QImage image(path);
    imageLabel->setPixmap(QPixmap::fromImage(image));
    imageLabel->show();
//    QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
//    sizePolicy.setHorizontalStretch(0);
//    sizePolicy.setVerticalStretch(0);
    newWin = new QMdiSubWindow;
    newWin->setWindowTitle("test");
    newWin->resize(ui->mdiArea->height()/2, ui->mdiArea->width()/2);
    newWin->setWidget(imageLabel);
    newWin->setAttribute(Qt::WA_DeleteOnClose);
    ui->mdiArea->addSubWindow(newWin);
    newWin->show();
//    for()
}

