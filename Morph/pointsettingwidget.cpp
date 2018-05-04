#include "pointsettingwidget.h"

pointSettingWidget::pointSettingWidget(QWidget *parent) : QWidget(parent)
{
    configure();
}

int pointSettingWidget::numOfFrame()
{
    return meshTab->numOfFrame();
}

void pointSettingWidget::configure()
{
    layout = new QGridLayout(this);
    QTabWidget *tab = new QTabWidget(this);
    QWidget *contourTab;
    meshTab = new meshTabWidget(tab->size(), tab);
    contourTab = new QWidget();
    tab->addTab(meshTab, "网格");
    tab->addTab(contourTab, "轮廓");
    layout->addWidget(tab);
    connect(meshTab, &meshTabWidget::startChoosing, this, &pointSettingWidget::startChoosing);
    connect(meshTab, &meshTabWidget::finishChoosing, this, &pointSettingWidget::finishChoosing);
}
