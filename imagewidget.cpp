#include <QtWidgets>

#include "imagewidget.h"

ImageWidget::ImageWidget(QWidget *parent) :
    QScrollArea(parent),
    imageLabel(new QLabel),
    m_scaleFactor(1.0),
    m_fitToWindow(false)
{
    imageLabel->setBackgroundRole(QPalette::Base);
    imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    imageLabel->setScaledContents(true);

    setBackgroundRole(QPalette::Dark);
    setWidget(imageLabel);
    setAlignment(Qt::AlignCenter);
}

void ImageWidget::setFitToWindow(bool value)
{
    m_fitToWindow = value;

    setWidgetResizable(m_fitToWindow);
    if (!m_fitToWindow) {
        // this is normalSize() call from the example
        imageLabel->adjustSize();
        m_scaleFactor = 1.0;
    }
}

bool ImageWidget::fitToWindow() const
{
    return m_fitToWindow;
}

void ImageWidget::setScaleFactor(double newScaleFactor)
{
    Q_ASSERT(imageLabel->pixmap());

    double factor = newScaleFactor / m_scaleFactor;
    m_scaleFactor = newScaleFactor;

    imageLabel->resize(newScaleFactor * imageLabel->pixmap()->size());

    adjustScrollBar(horizontalScrollBar(), factor);
    adjustScrollBar(verticalScrollBar(), factor);
}

double ImageWidget::scaleFactor() const
{
    return m_scaleFactor;
}

void ImageWidget::setPixmap(const QPixmap &pixmap)
{
    imageLabel->setPixmap(pixmap);
    m_scaleFactor = 1.0;

    if (!m_fitToWindow) {
        imageLabel->adjustSize();
    }
}

void ImageWidget::updatePixmap(const QPixmap &pixmap) {
    imageLabel->setPixmap(pixmap);
}

void ImageWidget::adjustScrollBar(QScrollBar *scrollBar, double factor)
{
    scrollBar->setValue(int(factor * scrollBar->value()
                            + ((factor - 1) * scrollBar->pageStep() / 2)));
}
