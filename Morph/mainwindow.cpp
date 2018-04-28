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
    layout_main = new QHBoxLayout();
    customWidget = new Widget(this);

    settingWidget->setFixedWidth(200);
    customWidget->show();

    layout_main->setSpacing(10);
    layout_main->addWidget(settingWidget);
    layout_main->addWidget(customWidget);

    //set settingWidget
//    settingWidget


    widget->setLayout(layout_main);
    this->setCentralWidget(widget);

    connect(ui->load, SIGNAL(triggered()), this, SLOT(loadImageSlot()));
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
    } else
        return;
    newSubWinAfterLoadImage(fileNames);
}

void MainWindow::newSubWinAfterLoadImage(QStringList paths)
{
    if(numOfLabel >= 2){
        QMessageBox::information(NULL, "提示", "一次导入的图片不能超过两个", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        return;
    }
    //根据路径载入图片
    //需要修改：多选图片时
    QString path = paths.at(0);
    QPixmap *image = new QPixmap(path);
    if(image->isNull()){
        QMessageBox::information(NULL, "提示", "请选择图片", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        return;
    }
    customWidget->CreateLabel(image, numOfLabel);
    ++numOfLabel;
}
