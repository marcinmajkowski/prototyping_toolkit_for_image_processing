#include <QtWidgets>

#include "imagewidget.h"

ImageWidget::ImageWidget(QWidget *parent) :
    QScrollArea(parent),
    m_imageLabel(new QLabel),
    m_scaleFactor(1.0),
    m_fitToWindow(false)
{
    m_imageLabel->setBackgroundRole(QPalette::Base);
    m_imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    m_imageLabel->setScaledContents(true);

    setBackgroundRole(QPalette::Dark);
    setWidget(m_imageLabel);
    setAlignment(Qt::AlignCenter);
}

void ImageWidget::setFitToWindow(bool value)
{
    m_fitToWindow = value;

    setWidgetResizable(m_fitToWindow);
    if (!m_fitToWindow) {
        // this is normalSize() call from the example
        m_imageLabel->adjustSize();
        m_scaleFactor = 1.0;
    }
}

bool ImageWidget::fitToWindow() const
{
    return m_fitToWindow;
}

void ImageWidget::setScaleFactor(double newScaleFactor)
{
    Q_ASSERT(m_imageLabel->pixmap());

    double factor = newScaleFactor / m_scaleFactor;
    m_scaleFactor = newScaleFactor;

    m_imageLabel->resize(newScaleFactor * m_imageLabel->pixmap()->size());

    adjustScrollBar(horizontalScrollBar(), factor);
    adjustScrollBar(verticalScrollBar(), factor);
}

double ImageWidget::scaleFactor() const
{
    return m_scaleFactor;
}

QLabel *ImageWidget::imageLabel()
{
    return m_imageLabel;
}

void ImageWidget::setPixmap(const QPixmap &pixmap)
{
    m_imageLabel->setPixmap(pixmap);
    m_scaleFactor = 1.0;

    if (!m_fitToWindow) {
        m_imageLabel->adjustSize();
    }
}

void ImageWidget::updatePixmap(const QPixmap &pixmap) {
    m_imageLabel->setPixmap(pixmap);
}

void ImageWidget::adjustScrollBar(QScrollBar *scrollBar, double factor)
{
    scrollBar->setValue(int(factor * scrollBar->value()
                            + ((factor - 1) * scrollBar->pageStep() / 2)));
}
