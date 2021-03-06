#include <QDebug>
#include <QtWidgets>

#include <opencv2/imgproc/imgproc.hpp>

#include "thresholdfilter.h"

ThresholdFilter::ThresholdFilter(FilterObserver *observer, QObject *parent) :
    Filter(filterName, observer, parent),
    m_threshold(127),
    m_maxValue(255),
    m_type(CV_THRESH_BINARY)
{
    m_typeMap.insert(CV_THRESH_BINARY, "CV_THRESH_BINARY");
    m_typeMap.insert(CV_THRESH_BINARY_INV, "CV_THRESH_BINARY_INV");
    m_typeMap.insert(CV_THRESH_TRUNC, "CV_THRESH_TRUNC");
    m_typeMap.insert(CV_THRESH_TOZERO, "CV_THRESH_TOZERO");
    m_typeMap.insert(CV_THRESH_TOZERO_INV, "CV_THRESH_TOZERO_INV");
}

QString ThresholdFilter::filterName = "Threshold";

QStringList ThresholdFilter::codeSnippet() const
{
    QStringList snippet;

    //TODO extra line with conversion when input has inappropriate type

    QString line = QString("cv::%1(%2, %3, %4, %5, %6);")
            .arg("threshold")
            .arg("img")
            .arg("img")
            .arg(m_threshold)
            .arg(m_maxValue)
            .arg(m_typeMap[m_type]);

    snippet << line;

    return snippet;
}

cv::Mat &ThresholdFilter::process(cv::Mat &input)
{
    switch (input.type()) {
    case CV_8UC4:
    case CV_8UC3:
        // adaptiveThreshold requires 8-bit single-channel input
        cv::cvtColor(input, input, CV_RGB2GRAY);
    case CV_8UC1:
        cv::threshold(input, input, m_threshold, m_maxValue, m_type);
        break;
    }

    return input;
}

void ThresholdFilter::setThreshold(int threshold)
{
    m_threshold = threshold;
    emit updated();
}

void ThresholdFilter::setMaxValue(int maxValue)
{
    m_maxValue = maxValue;
    emit updated();
}

void ThresholdFilter::setType(const QString &type)
{
    m_type = m_typeMap.key(type);

    emit updated();
}

QLayout *ThresholdFilter::dialogParametersGroupLayout()
{
    QFormLayout *formLayout = new QFormLayout;

    QSlider *threshold = new QSlider(Qt::Horizontal);
    threshold->setRange(0, 255);
    threshold->setValue(m_threshold);
    formLayout->addRow(new QLabel("threshold"), threshold);
    connect(threshold, SIGNAL(valueChanged(int)),
            this, SLOT(setThreshold(int)));

    QSlider *maxValue = new QSlider(Qt::Horizontal);
    maxValue->setRange(0, 255);
    maxValue->setValue(m_maxValue);
    formLayout->addRow(new QLabel("maxValue:"), maxValue);
    connect(maxValue, SIGNAL(valueChanged(int)),
            this, SLOT(setMaxValue(int)));

    QComboBox *type = new QComboBox;
    foreach (const QString &s, m_typeMap) {
        type->addItem(s);
    }

    type->setCurrentText(m_typeMap[m_type]);
    formLayout->addRow(new QLabel("type:"), type);
    connect(type, SIGNAL(currentIndexChanged(QString)),
            this, SLOT(setType(QString)));

    return formLayout;
}

QLabel *ThresholdFilter::dialogDescriptionLabel()
{
    QLabel *signatureLabel = new QLabel;

    signatureLabel->setText("void <b>threshold</b>(<br>\
                            &nbsp; InputArray <b>src</b>,<br>\
                            &nbsp; OutputArray <b>dst</b>,<br>\
                            &nbsp; double <b>threshold</b>,<br>\
                            &nbsp; double <b>maxValue</b>,<br>\
                            &nbsp; int <b>type</b>,<br>\
                            )");

    return signatureLabel;
}
