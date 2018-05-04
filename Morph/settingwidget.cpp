#include "settingwidget.h"

settingWidget::settingWidget(QWidget *parent) : QWidget(parent)
{
    setFixedWidth(230);
    layout = new QGridLayout(this);
}
