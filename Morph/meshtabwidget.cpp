#include "meshtabwidget.h"

meshTabWidget::meshTabWidget(QSize size, QWidget *parent) : QWidget(parent)
{
    this->resize(size);
    QLabel *label = new QLabel("网格大小", this);
    sizeOfMesh = new QLineEdit(this);
    startChoose = new QPushButton(this);
    finishChoose = new QPushButton(this);
    layout = new QGridLayout();

    sizeOfMesh->setText("5");
    startChoose->setText("开始选点");
    finishChoose->setText("结束选点");

    setContentsMargins(0, 0, 0, 0);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(label, 0, 0, 1, 3);
    layout->addWidget(sizeOfMesh, 0, 3, 1, 2);
    layout->addWidget(startChoose, 2, 0, 1, 3);
    layout->addWidget(finishChoose, 2, 3, 1, 3);
    setLayout(layout);
    connect(startChoose, &QPushButton::clicked, this, &meshTabWidget::startClicked);
    connect(finishChoose, &QPushButton::clicked, this, &meshTabWidget::finishClicked);
}

void meshTabWidget::startClicked()
{
    emit startChoosing(sizeOfMesh->text().toInt());
}

void meshTabWidget::finishClicked()
{
    emit finishChoosing();
}


