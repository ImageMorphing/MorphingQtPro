#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSize>
#include <QMdiSubWindow>
#include <QLabel>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
public slots:
    void loadImageSlot();

private:
    Ui::MainWindow *ui;
    QMdiSubWindow *newWin;

    void newSubWinAfterLoadImage(QStringList paths);

};

#endif // MAINWINDOW_H
