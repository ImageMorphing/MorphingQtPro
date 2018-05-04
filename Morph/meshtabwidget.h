#ifndef MESHTABWIDGET_H
#define MESHTABWIDGET_H

#include <QWidget>
#include <QSize>
#include <QGridLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>

class meshTabWidget : public QWidget
{
    Q_OBJECT
public:
    explicit meshTabWidget(QSize size, QWidget *parent = nullptr);
    int numOfFrame();

signals:
    void startChoosing(int);
    void finishChoosing();
private slots:
    void startClicked();
    void finishClicked();
private:
    QGridLayout *layout;
    QLineEdit *lineEdit_sizeOfMesh, *lineEdit_numOfFrame;
    QPushButton *startChoose, *finishChoose;
signals:

public slots:
};

#endif // MESHTABWIDGET_H
