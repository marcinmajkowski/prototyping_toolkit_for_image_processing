#include "mainwindow.h"
#include <QApplication>
#include <QStyle>
#include <QDesktopWidget>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("Prototyping Toolkit for Image Processing");

    // Center a Window on the Screen
    w.setGeometry(QStyle::alignedRect(
                      Qt::LeftToRight, Qt::AlignCenter, w.size(),
                      qApp->desktop()->availableGeometry()));

    w.show();

    return a.exec();
}
