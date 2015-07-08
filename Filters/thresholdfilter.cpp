#include <QDebug>
#include <QtWidgets>

#include <opencv2/imgproc/imgproc.hpp>

#include "thresholdfilter.h"

ThresholdFilter::ThresholdFilter(FilterObserver *observer, QObject *parent) :
    Filter("Threshold", observer, parent),
    m_threshold(127),
    m_maxValue(255),
    m_type(CV_THRESH_BINARY)
{
}

QStringList ThresholdFilter::codeSnippet() const
{
    QStringList snippet;

    QString type;
    switch (m_type) {
    case CV_THRESH_BINARY:
        type = "CV_THRESH_BINARY";
        break;
    case CV_THRESH_BINARY_INV:
        type = "CV_THRESH_BINARY_INV";
        break;
    case CV_THRESH_TRUNC:
        type = "CV_THRESH_TRUNC";
        break;
    case CV_THRESH_TOZERO:
        type = "CV_THRESH_TOZERO";
        break;
    case CV_THRESH_TOZERO_INV:
        type = "CV_THRESH_TOZERO_INV";
        break;
    default:
        qDebug() << "threshold: not known argument for threshold";
    }

    //TODO extra line with conversion when input has inappropriate type

    QString line = QString("cv::%1(%2, %3, %4, %5, %6);")
            .arg("threshold")
            .arg("src")
            .arg("dst")
            .arg(m_threshold)
            .arg(m_maxValue)
            .arg(type);

    snippet << line;

    return snippet;
}

QDialog *ThresholdFilter::createDialog(QWidget *parent)
{
    //TODO
    QDialog *dialog = new QDialog(parent);

    QLabel *signatureLabel = new QLabel;

    signatureLabel->setText("void <b>threshold</b>(<br>\
                            &nbsp; InputArray <b>src</b>,<br>\
                            &nbsp; OutputArray <b>dst</b>,<br>\
                            &nbsp; double <b>threshold</b>,<br>\
                            &nbsp; double <b>maxValue</b>,<br>\
                            &nbsp; int <b>type</b>,<br>\
                            )");

    QGroupBox *parametersGroup = new QGroupBox(tr("Parameters"));

    QFormLayout *formLayout = new QFormLayout;

    //TODO whole section
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
    type->addItem("CV_THRESH_BINARY");
    type->addItem("CV_THRESH_BINARY_INV");
    type->addItem("CV_THRESH_TRUNC");
    type->addItem("CV_THRESH_TOZERO");
    type->addItem("CV_THRESH_TOZERO_INV");
    switch(m_type) {
    case CV_THRESH_BINARY:
        type->setCurrentText("CV_THRESH_BINARY");
        break;
    case CV_THRESH_BINARY_INV:
        type->setCurrentText("CV_THRESH_BINARY_INV");
        break;
    case CV_THRESH_TRUNC:
        type->setCurrentText("CV_THRESH_TRUNC");
        break;
    case CV_THRESH_TOZERO:
        type->setCurrentText("CV_THRESH_TOZERO");
        break;
    case CV_THRESH_TOZERO_INV:
        type->setCurrentText("CV_THRESH_TOZERO_INV");
        break;
    }
    formLayout->addRow(new QLabel("type:"), type);
    connect(type, SIGNAL(currentIndexChanged(QString)),
            this, SLOT(setType(QString)));

    parametersGroup->setLayout(formLayout);

    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
                                                       | QDialogButtonBox::Cancel);

    connect(buttonBox, SIGNAL(accepted()), dialog, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), dialog, SLOT(reject()));

    QVBoxLayout *mainLayout = new QVBoxLayout;

    mainLayout->addWidget(signatureLabel);
    mainLayout->addWidget(parametersGroup);
    mainLayout->addWidget(buttonBox);

    dialog->setLayout(mainLayout);

    dialog->setWindowTitle(tr("%1 %2").arg(m_name).arg("settings"));

    return dialog;
}

cv::Mat &ThresholdFilter::process(cv::Mat &input) const
{
    //TODO add support for images with floats
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
    if (type == "CV_THRESH_BINARY") {
        m_type = CV_THRESH_BINARY;
    } else if (type == "CV_THRESH_BINARY_INV") {
        m_type = CV_THRESH_BINARY_INV;
    } else if (type == "CV_THRESH_TRUNC") {
        m_type = CV_THRESH_TRUNC;
    } else if (type == "CV_THRESH_TOZERO") {
        m_type = CV_THRESH_TOZERO;
    } else if (type == "CV_THRESH_TOZERO_INV") {
        m_type = CV_THRESH_TOZERO_INV;
    }

    emit updated();
}
