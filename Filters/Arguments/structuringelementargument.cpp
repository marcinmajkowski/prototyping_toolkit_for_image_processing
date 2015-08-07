#include <opencv2/imgproc/imgproc.hpp>
#include <QtWidgets>

#include "structuringelementargument.h"

StructuringElementArgument::StructuringElementArgument(int shape, int sizeWidth, int sizeHeight, QObject *parent) :
    QObject(parent),
    m_shape(shape),
    m_sizeWidth(sizeWidth),
    m_sizeHeight(sizeHeight),
    m_anchor(cv::Point(-1, -1))
{
    m_shapeMap.insert(cv::MORPH_RECT, "cv::MORPH_RECT");
    m_shapeMap.insert(cv::MORPH_ELLIPSE, "cv::MORPH_ELLIPSE");
    m_shapeMap.insert(cv::MORPH_CROSS, "cv::MORPH_CROSS");
}

QLayout *StructuringElementArgument::layout()
{
    QFormLayout *formLayout = new QFormLayout;

    QComboBox *shape = new QComboBox;
    foreach (const QString &s, m_shapeMap) {
        shape->addItem(s);
    }

    shape->setCurrentText(m_shapeMap[m_shape]);
    formLayout->addRow(new QLabel("  shape:"), shape);
    connect(shape, SIGNAL(currentIndexChanged(QString)),
            this, SLOT(setShape(QString)));

    int maximumDimension = 100;

    QSlider *sizeWidth = new QSlider(Qt::Horizontal);
    sizeWidth->setRange(1, maximumDimension);
    sizeWidth->setValue(m_sizeWidth);
    formLayout->addRow(new QLabel("  size-width:"), sizeWidth);
    connect(sizeWidth, SIGNAL(valueChanged(int)),
            this, SLOT(setSizeWidth(int)));

    QSlider *sizeHeight = new QSlider(Qt::Horizontal);
    sizeHeight->setRange(1, maximumDimension);
    sizeHeight->setValue(m_sizeHeight);
    formLayout->addRow(new QLabel("  size-height:"), sizeHeight);
    connect(sizeHeight, SIGNAL(valueChanged(int)),
            this, SLOT(setSizeHeight(int)));

    return formLayout;
}

QString StructuringElementArgument::text() const
{
    QString size = QString("cv::%1(%2, %3)")
            .arg("Size")
            .arg(m_sizeWidth)
            .arg(m_sizeHeight);
    QString anchor = "cv::Point(-1, -1)";
    QString structuringElement = QString("cv::%1(%2, %3, %4)")
            .arg("getStructuringElement")
            .arg(size)
            .arg(m_shapeMap[m_shape])
            .arg(anchor);

    return structuringElement;
}

cv::Mat StructuringElementArgument::value()
{
    cv::Size size = cv::Size(m_sizeWidth, m_sizeHeight);

    return cv::getStructuringElement(m_shape, size, m_anchor);
}

void StructuringElementArgument::setShape(const QString &shape)
{
    m_shape = m_shapeMap.key(shape);

    emit updated();
}

void StructuringElementArgument::setSizeWidth(int sizeWidth)
{
    m_sizeWidth = sizeWidth;

    emit updated();
}

void StructuringElementArgument::setSizeHeight(int sizeHeight)
{
    m_sizeHeight = sizeHeight;

    emit updated();
}

QDataStream &operator<<(QDataStream &dataStream,
                                   const StructuringElementArgument &structuringElementArgument)
{
    dataStream << structuringElementArgument.m_shape
               << structuringElementArgument.m_sizeWidth
               << structuringElementArgument.m_sizeHeight
               << structuringElementArgument.m_anchor.x
               << structuringElementArgument.m_anchor.y;

    return dataStream;
}
QDataStream &operator>>(QDataStream &dataStream,
                                   StructuringElementArgument &structuringElementArgument)
{
    dataStream >> structuringElementArgument.m_shape
               >> structuringElementArgument.m_sizeWidth
               >> structuringElementArgument.m_sizeHeight
               >> structuringElementArgument.m_anchor.x
               >> structuringElementArgument.m_anchor.y;

    return dataStream;
}
