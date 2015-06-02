#include <QtWidgets>

#include "imagewidget.h"

ImageWidget::ImageWidget(QWidget *parent) :
    QScrollArea(parent)
{
    imageLabel = new QLabel;
    imageLabel->setBackgroundRole(QPalette::Base);
    imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    imageLabel->setScaledContents(true);

    setBackgroundRole(QPalette::Dark);
    setWidget(imageLabel);
}

bool ImageWidget::loadFile(const QString &filename)
{

}

void ImageWidget::zoomIn()
{

}

void ImageWidget::zoomOut()
{

}

void ImageWidget::normalSize()
{

}

void ImageWidget::fitToWindow()
{

}

void ImageWidget::scaleImage(double factor)
{

}

void ImageWidget::adjustScrollBar(QScrollBar *scrollBar, double factor)
{

}
