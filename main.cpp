#include "mainwindow.h"
#include <QApplication>
#include <QStyle>
#include <QDesktopWidget>
#include <QMetaType>
#include <opencv2/core/core.hpp>

int main(int argc, char *argv[])
{
    qRegisterMetaType<cv::Mat>("cv::Mat");
    QApplication a(argc, argv);
    a.setApplicationName("Prototyping Toolkit for Image Processing");
    MainWindow w;

    // Center a Window on the Screen
    w.setGeometry(QStyle::alignedRect(
                      Qt::LeftToRight, Qt::AlignCenter, w.size(),
                      qApp->desktop()->availableGeometry()));

    w.show();

    return a.exec();
}
