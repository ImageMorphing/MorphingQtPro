#ifndef POINTSETTINGWIDGET_H
#define POINTSETTINGWIDGET_H

#include <QWidget>
#include <QTabWidget>
#include <QGridLayout>
#include "meshtabwidget.h"

class pointSettingWidget : public QWidget
{
    Q_OBJECT
public:
    explicit pointSettingWidget(QWidget *parent = nullptr);
    int numOfFrame();

signals:
    void startChoosing(int);
    void finishChoosing();

public slots:

private:
    void configure();
    QGridLayout *layout;
    meshTabWidget *meshTab;
};

#endif // POINTSETTINGWIDGET_H
