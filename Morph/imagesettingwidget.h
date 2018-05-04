#ifndef IMAGESETTINGWIDGET_H
#define IMAGESETTINGWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QPixmap>

class imageSettingWidget : public QWidget
{
    Q_OBJECT
public:
    explicit imageSettingWidget(QWidget *parent = nullptr);
    void changeIcononLoadingNew(QPixmap *image);
    void changeIcononChangingImage(QPixmap *image);

signals:
    void chooseSourceImage(int);
    void chooseDestImage(int);
    void scaleUp();
    void scaleDown();
    void loadNewImage();
    void deleteImage();
public slots:
    void slot_sourceImageButtonClicked();
    void slot_targetImageButtonClicked();
    void slot_scaleUpButton();
    void slot_scaleDownButton();
    void slot_loadNewImageButton();
    void slot_deleteImageButton();

private:
    bool buttonOccupy[2];
    QPushButton *choosenButton;
    QGridLayout *layout;
    QPushButton *sourceImageButton, *targetImageButton;
    QPushButton *scaleUpButton, *scaleDownButton, *loadNewImageButton, *deleteImageButton;
    void createWidget();
};

#endif // IMAGESETTINGWIDGET_H
