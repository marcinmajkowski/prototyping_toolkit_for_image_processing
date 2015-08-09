#include <QDebug>
#include <QtWidgets>

#include <opencv2/imgproc/imgproc.hpp>

#include "erodefilter.h"

ErodeFilter::ErodeFilter(FilterObserver *observer, QObject *parent) :
    Filter(filterName, observer, parent),
    m_kernel(cv::MORPH_ELLIPSE, 3, 3),
    m_anchor(cv::Point(-1, - 1)),
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

QString ErodeFilter::filterName = "Erode";

QStringList ErodeFilter::codeSnippet() const
{
    QString anchor = "cv::Point(-1, -1)";
    QString borderValue = "cv::morphologyDefaultBorderValue()";

    QStringList snippet;

    QString line = QString("cv::%1(%2, %3, %4, %5, %6, %7, %8);")
            .arg("erode")
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

cv::Mat &ErodeFilter::process(cv::Mat &input)
{
    cv::erode(input, input, m_kernel.value(), m_anchor, m_iterations,
              m_borderType, m_borderValue);

    return input;
}

void ErodeFilter::read(QDataStream &data)
{
    data >> m_kernel
         >> m_anchor.x
         >> m_anchor.y
         >> m_iterations
         >> m_borderType
         >> m_borderValue[0]
         >> m_borderValue[1]
         >> m_borderValue[2]
         >> m_borderValue[3];

    emit updated();
}

void ErodeFilter::write(QDataStream &data) const
{
    data << m_kernel
         << m_anchor.x
         << m_anchor.y
         << m_iterations
         << m_borderType
         << m_borderValue[0]
         << m_borderValue[1]
         << m_borderValue[2]
         << m_borderValue[3];
}

void ErodeFilter::setBorderType(const QString &borderType)
{
    m_borderType = m_borderTypeMap.key(borderType);

    emit updated();
}

void ErodeFilter::setIterations(int iterations)
{
    m_iterations = iterations;

    emit updated();
}

QLabel *ErodeFilter::dialogDescriptionLabel()
{
    QLabel *signatureLabel = new QLabel;

    signatureLabel->setText("void <b>erode</b>(<br>\
                            &nbsp; InputArray <b>src</b>,<br>\
                            &nbsp; OutputArray <b>dst</b>,<br>\
                            &nbsp; Point <b>anchor</b>,<br>\
                            &nbsp; int <b>iterations</b>,<br>\
                            &nbsp; int <b>borderType</b>,<br>\
                            &nbsp; const Scalar &<b>borderValue</b>,<br>\
                            )");

    return signatureLabel;
}

QLayout *ErodeFilter::dialogParametersGroupLayout()
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
