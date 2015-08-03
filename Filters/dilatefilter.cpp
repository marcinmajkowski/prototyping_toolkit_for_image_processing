#include <QDebug>
#include <QtWidgets>

#include <opencv2/imgproc/imgproc.hpp>

#include "dilatefilter.h"

DilateFilter::DilateFilter(FilterObserver *observer, QObject *parent) :
    Filter("Dilate", observer, parent),
    m_kernelShape(cv::MORPH_ELLIPSE),
    m_kernelSizeWidth(3),
    m_kernelSizeHeight(3),
    m_kernelAnchor(cv::Point(-1, -1)),
    m_anchor(cv::Point(-1, -1)),
    m_iterations(1),
    m_borderType(cv::BORDER_CONSTANT),
    m_borderValue(cv::morphologyDefaultBorderValue())
{
    m_kernelShapeMap.insert(cv::MORPH_RECT, "cv::MORPH_RECT");
    m_kernelShapeMap.insert(cv::MORPH_ELLIPSE, "cv::MORPH_ELLIPSE");
    m_kernelShapeMap.insert(cv::MORPH_CROSS, "cv::MORPH_CROSS");

    m_borderTypeMap.insert(cv::BORDER_CONSTANT, "cv::BORDER_CONSTANT");
    m_borderTypeMap.insert(cv::BORDER_DEFAULT, "cv::BORDER_DEFAULT");
    m_borderTypeMap.insert(cv::BORDER_REFLECT, "cv::BORDER_REFLECT");
    m_borderTypeMap.insert(cv::BORDER_REFLECT_101, "cv::BORDER_REFLECT_101");
    m_borderTypeMap.insert(cv::BORDER_REPLICATE, "cv::BORDER_REPLICATE");
}

QStringList DilateFilter::codeSnippet() const
{
    //TODO
    QString kernelSize = QString("cv::%1(%2, %3)")
            .arg("Size")
            .arg(m_kernelSizeWidth)
            .arg(m_kernelSizeHeight);
    QString kernelAnchor = "cv::Point(-1, -1)";
    QString kernel = QString("cv::%1(%2, %3, %4)")
            .arg("getStructuringElement")
            .arg(kernelSize)
            .arg(m_kernelShapeMap[m_kernelShape])
            .arg(kernelAnchor);
    QString anchor = "cv::Point(-1, -1)";
    QString borderValue = "cv::morphologyDefaultBorderValue()";

    QStringList snippet;

    QString line = QString("cv::%1(%2, %3, %4, %5, %6, %7, %8);")
            .arg("dilate")
            .arg("img")
            .arg("img")
            .arg(kernel)
            .arg(anchor)
            .arg(m_iterations)
            .arg(m_borderTypeMap[m_borderType])
            .arg(borderValue);

    snippet << line;

    return snippet;
}

cv::Mat &DilateFilter::process(cv::Mat &input)
{
    cv::Size kernelSize = cv::Size(m_kernelSizeWidth, m_kernelSizeHeight);
    cv::Mat kernel = cv::getStructuringElement(m_kernelShape, kernelSize, m_kernelAnchor);
    cv::dilate(input, input, kernel, m_anchor, m_iterations, m_borderType, m_borderValue);

    return input;
}

void DilateFilter::read(QDataStream &data)
{
    //TODO read all parameters
    data >> m_iterations;

    emit updated();
}

void DilateFilter::write(QDataStream &data) const
{
    //TODO write all parameters
    data << m_iterations;
}

void DilateFilter::setKernelShape(const QString &borderType)
{
    m_kernelShape = m_kernelShapeMap.key(borderType);

    emit updated();
}

void DilateFilter::setKernelSizeWidth(int kernelSizeWidth)
{
    m_kernelSizeWidth = kernelSizeWidth;

    emit updated();
}

void DilateFilter::setKernelSizeHeight(int kernelSizeHeight)
{
    m_kernelSizeHeight = kernelSizeHeight;

    emit updated();
}

void DilateFilter::setBorderType(const QString &borderType)
{
    m_borderType = m_borderTypeMap.key(borderType);

    emit updated();
}

void DilateFilter::setIterations(int iterations)
{
    m_iterations = iterations;

    emit updated();
}

QLayout *DilateFilter::dialogParametersGroupLayout()
{
    QFormLayout *formLayout = new QFormLayout;

    formLayout->addRow(new QLabel("kernel:"));

    QComboBox *kernelShape = new QComboBox;
    foreach (const QString &s, m_kernelShapeMap) {
        kernelShape->addItem(s);
    }

    kernelShape->setCurrentText(m_kernelShapeMap[m_kernelShape]);
    formLayout->addRow(new QLabel("  shape:"), kernelShape);
    connect(kernelShape, SIGNAL(currentIndexChanged(QString)),
            this, SLOT(setKernelShape(QString)));

    QSlider *kernelSizeWidth = new QSlider(Qt::Horizontal);
    kernelSizeWidth->setRange(1, 30);
    kernelSizeWidth->setValue(m_kernelSizeWidth);
    formLayout->addRow(new QLabel("  size-width:"), kernelSizeWidth);
    connect(kernelSizeWidth, SIGNAL(valueChanged(int)),
            this, SLOT(setKernelSizeWidth(int)));

    QSlider *kernelSizeHeight = new QSlider(Qt::Horizontal);
    kernelSizeHeight->setRange(1, 30);
    kernelSizeHeight->setValue(m_kernelSizeHeight);
    formLayout->addRow(new QLabel("  size-height:"), kernelSizeHeight);
    connect(kernelSizeHeight, SIGNAL(valueChanged(int)),
            this, SLOT(setKernelSizeHeight(int)));

    QSlider *iterations = new QSlider(Qt::Horizontal);
    iterations->setRange(1, 30);
    iterations->setValue(m_iterations);
    formLayout->addRow(new QLabel("iterations:"), iterations);
    connect(iterations, SIGNAL(valueChanged(int)),
            this, SLOT(setIterations(int)));

    QComboBox *borderType = new QComboBox;
    foreach (const QString &s, m_borderTypeMap) {
        borderType->addItem(s);
    }

    borderType->setCurrentText(m_borderTypeMap[m_borderType]);
    formLayout->addRow(new QLabel("borderType:"), borderType);
    connect(borderType, SIGNAL(currentIndexChanged(QString)),
            this, SLOT(setBorderType(QString)));

    return formLayout;
}

QLabel *DilateFilter::dialogDescriptionLabel()
{
    QLabel *signatureLabel = new QLabel;

    signatureLabel->setText("void <b>dilate</b>(<br>\
                            &nbsp; InputArray <b>src</b>,<br>\
                            &nbsp; OutputArray <b>dst</b>,<br>\
                            &nbsp; Point <b>anchor</b>,<br>\
                            &nbsp; int <b>iterations</b>,<br>\
                            &nbsp; int <b>borderType</b>,<br>\
                            &nbsp; const Scalar &<b>borderValue</b>,<br>\
                            )");

    return signatureLabel;
}
