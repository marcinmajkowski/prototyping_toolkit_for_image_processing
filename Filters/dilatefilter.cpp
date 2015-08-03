#include <QDebug>
#include <QtWidgets>

#include <opencv2/imgproc/imgproc.hpp>

#include "dilatefilter.h"

DilateFilter::DilateFilter(FilterObserver *observer, QObject *parent) :
    Filter("Dilate", observer, parent),
    m_kernel(cv::MORPH_ELLIPSE, 3, 3),
    m_anchor(cv::Point(-1, -1)),
    m_iterations(1),
    m_borderType(cv::BORDER_CONSTANT),
    m_borderValue(cv::morphologyDefaultBorderValue())
{
    m_borderTypeMap.insert(cv::BORDER_CONSTANT, "cv::BORDER_CONSTANT");
    m_borderTypeMap.insert(cv::BORDER_DEFAULT, "cv::BORDER_DEFAULT");
    m_borderTypeMap.insert(cv::BORDER_REFLECT, "cv::BORDER_REFLECT");
    m_borderTypeMap.insert(cv::BORDER_REFLECT_101, "cv::BORDER_REFLECT_101");
    m_borderTypeMap.insert(cv::BORDER_REPLICATE, "cv::BORDER_REPLICATE");
}

QStringList DilateFilter::codeSnippet() const
{
    QString anchor = "cv::Point(-1, -1)";
    QString borderValue = "cv::morphologyDefaultBorderValue()";

    QStringList snippet;

    QString line = QString("cv::%1(%2, %3, %4, %5, %6, %7, %8);")
            .arg("dilate")
            .arg("img")
            .arg("img")
            .arg(m_kernel.text())
            .arg(anchor)
            .arg(m_iterations)
            .arg(m_borderTypeMap[m_borderType])
            .arg(borderValue);

    snippet << line;

    return snippet;
}

cv::Mat &DilateFilter::process(cv::Mat &input)
{
    cv::dilate(input, input, m_kernel.value(), m_anchor, m_iterations, m_borderType, m_borderValue);

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
    formLayout->addRow(m_kernel.layout());
    connect(&m_kernel, SIGNAL(updated()),
            this, SIGNAL(updated()));

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
