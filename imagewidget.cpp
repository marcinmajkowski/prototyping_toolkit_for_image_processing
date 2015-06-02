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

bool ImageWidget::loadFile(const QString &fileName)
{
    QImage image(fileName);
    if (image.isNull()) {
        QMessageBox::information(this, QGuiApplication::applicationDisplayName(),
                                 tr("Cannot load %1").arg(QDir::toNativeSeparators(fileName)));
        setWindowFilePath(QString());
        imageLabel->setPixmap(QPixmap());
        imageLabel->adjustSize();
        return false;
    }
    imageLabel->setPixmap(QPixmap::fromImage(image));
    m_scaleFactor = 1.0;

    if (!m_fitToWindow) {
        imageLabel->adjustSize();
    }

    setWindowFilePath(fileName);
    return true;
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

}

void ImageWidget::setMat(const cv::Mat)
{

}


void ImageWidget::adjustScrollBar(QScrollBar *scrollBar, double factor)
{
    //TODO
}
