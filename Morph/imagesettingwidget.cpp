#include "imagesettingwidget.h"

imageSettingWidget::imageSettingWidget(QWidget *parent) : QWidget(parent)
{
    createWidget();
}

void imageSettingWidget::changeIcononLoadingNew(QPixmap *image)
{
    if(buttonOccupy[0] == false){
        buttonOccupy[0] = true;
        choosenButton = sourceImageButton;
        choosenButton->setIcon(QIcon(*image));
        choosenButton->setIconSize(choosenButton->size());
    } else if(buttonOccupy[1] == false){
        buttonOccupy[1] = true;
        choosenButton = targetImageButton;
        choosenButton->setIcon(QIcon(*image));
        choosenButton->setIconSize(choosenButton->size());
    }
    choosenButton->setText("");
}

void imageSettingWidget::changeIcononChangingImage(QPixmap *image)
{
    choosenButton->setIcon(QIcon(*image));
    choosenButton->setIconSize(choosenButton->size());
}

void imageSettingWidget::createWidget()
{
    choosenButton = NULL;
    buttonOccupy[0] = false;
    buttonOccupy[1] = false;

    layout = new QGridLayout(this);

    sourceImageButton = new QPushButton(this);
    targetImageButton = new QPushButton(this);
    scaleUpButton = new QPushButton(this);
    scaleDownButton = new QPushButton(this);
    loadNewImageButton = new QPushButton(this);
    deleteImageButton = new QPushButton(this);


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

    connect(sourceImageButton, &QPushButton::clicked, this, &imageSettingWidget::slot_sourceImageButtonClicked);
    connect(targetImageButton, &QPushButton::clicked, this, &imageSettingWidget::slot_targetImageButtonClicked);
    connect(scaleUpButton, &QPushButton::clicked, this, &imageSettingWidget::slot_scaleUpButton);
    connect(scaleDownButton, &QPushButton::clicked, this, &imageSettingWidget::slot_scaleDownButton);
    connect(loadNewImageButton, &QPushButton::clicked, this, &imageSettingWidget::slot_loadNewImageButton);
    connect(deleteImageButton, &QPushButton::clicked, this, &imageSettingWidget::slot_deleteImageButton);

    layout->addWidget(sourceImageButton, 0, 0);
    layout->addWidget(targetImageButton, 0, 1);
    layout->addWidget(scaleUpButton, 1, 0);
    layout->addWidget(scaleDownButton, 1, 1);
    layout->addWidget(loadNewImageButton, 2, 0);
    layout->addWidget(deleteImageButton, 2, 1);
}

void imageSettingWidget::slot_sourceImageButtonClicked()
{
    emit chooseSourceImage(0);
}

void imageSettingWidget::slot_targetImageButtonClicked()
{
    emit chooseDestImage(1);
}

void imageSettingWidget::slot_scaleUpButton()
{
    emit scaleUp();
}

void imageSettingWidget::slot_scaleDownButton()
{
    emit scaleDown();
}

void imageSettingWidget::slot_loadNewImageButton()
{
    emit loadNewImage();
}

void imageSettingWidget::slot_deleteImageButton()
{
    emit deleteImage();
    choosenButton->setIcon(QIcon());
    if(choosenButton == sourceImageButton){
        choosenButton->setText("源图片");
        buttonOccupy[0] = false;
    }
    else{
        choosenButton->setText("目标图片");
        buttonOccupy[1] = false;
    }
    if(buttonOccupy[0])
        choosenButton = sourceImageButton;
    else if(buttonOccupy[1])
        choosenButton = targetImageButton;
    else
        choosenButton = NULL;
}


