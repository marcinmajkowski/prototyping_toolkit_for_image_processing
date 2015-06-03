#include <QtWidgets>

#include <opencv2/core/core.hpp>

#include "imagewidget.h"

ImageWidget::ImageWidget(QWidget *parent) :
    QScrollArea(parent)
{
    // defaults:
    m_scaleFactor = 1.0;
    m_fitToWindow = false;

    imageLabel = new QLabel;
    imageLabel->setBackgroundRole(QPalette::Base);
    imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    imageLabel->setScaledContents(true);

    setBackgroundRole(QPalette::Dark);
    setWidget(imageLabel);
}

void ImageWidget::setFitToWindow(bool value)
{
    m_fitToWindow = value;

    //TODO insert here what was in fitToWindow function
}

bool ImageWidget::fitToWindow() const
{
    return m_fitToWindow;
}

void ImageWidget::setScaleFactor(double value)
{
    m_scaleFactor = value;

    //TODO insert here what was in zoomIn and zoomOut
    //TODO and in scalelImage()
}

double ImageWidget::scaleFactor() const
{
    return m_scaleFactor;
}

void ImageWidget::setPixmap(const QPixmap &)
{
    //imageLabel setPixmap
    //TODO if not fitToWindow adjust size
}

void ImageWidget::setMat(const cv::Mat)
{

}


void ImageWidget::adjustScrollBar(QScrollBar *scrollBar, double factor)
{
    //TODO
}
