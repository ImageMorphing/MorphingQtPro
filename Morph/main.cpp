#include "mainwindow.h"
#include "widget.h"
#include <cv.hpp>
#include <highgui.hpp>
#include <imgproc.hpp>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
//    std::string
//    IplImage *t = cvLoadImage("");
//    cv::imwrite()
    return a.exec();
}
