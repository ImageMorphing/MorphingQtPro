#include "meshtabwidget.h"

meshTabWidget::meshTabWidget(QSize size, QWidget *parent) : QWidget(parent)
{
    this->resize(size);
    QLabel *label_sizeOfMesh = new QLabel("网格大小", this);
    QLabel *label_numOfFrame = new QLabel("图像数量", this);
    lineEdit_numOfFrame = new QLineEdit(this);
    lineEdit_sizeOfMesh = new QLineEdit(this);
    startChoose = new QPushButton(this);
    finishChoose = new QPushButton(this);
    layout = new QGridLayout();

    lineEdit_sizeOfMesh->setText("5");
    lineEdit_numOfFrame->setText("10");
    startChoose->setText("开始选点");
    finishChoose->setText("结束选点");

    setContentsMargins(0, 0, 0, 0);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(label_sizeOfMesh, 0, 0, 1, 3);
    layout->addWidget(lineEdit_sizeOfMesh, 0, 3, 1, 2);
    layout->addWidget(label_numOfFrame, 2, 0, 1, 3);
    layout->addWidget(lineEdit_numOfFrame, 2, 3, 1, 2);
    layout->addWidget(startChoose, 3, 0, 1, 3);
    layout->addWidget(finishChoose, 3, 3, 1, 3);
    setLayout(layout);
    connect(startChoose, &QPushButton::clicked, this, &meshTabWidget::startClicked);
    connect(finishChoose, &QPushButton::clicked, this, &meshTabWidget::finishClicked);
}

int meshTabWidget::numOfFrame()
{
    return lineEdit_numOfFrame->text().toInt();
}

void meshTabWidget::startClicked()
{
    emit startChoosing(lineEdit_sizeOfMesh->text().toInt());
}

void meshTabWidget::finishClicked()
{
    emit finishChoosing();
}


