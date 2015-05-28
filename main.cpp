#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("Prototyping Toolkit for Image Processing");
    w.show();

    return a.exec();
}
