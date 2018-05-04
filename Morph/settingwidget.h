#ifndef SETTINGWIDGET_H
#define SETTINGWIDGET_H

#include <QWidget>
#include <QGridLayout>

class settingWidget : public QWidget
{
    Q_OBJECT
public:
    explicit settingWidget(QWidget *parent = nullptr);

signals:

public slots:

private :
    QGridLayout *layout;
};

#endif // SETTINGWIDGET_H
