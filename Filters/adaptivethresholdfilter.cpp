#include <QDebug>
#include <QtWidgets>

#include <opencv2/imgproc/imgproc.hpp>

#include "adaptivethresholdfilter.h"

AdaptiveThresholdFilter::AdaptiveThresholdFilter(FilterObserver *observer, QObject *parent) :
    Filter("Adaptive threshold", observer, parent),
    m_maxValue(255),
    m_adaptiveMethod(CV_ADAPTIVE_THRESH_MEAN_C),
    m_thresholdType(CV_THRESH_BINARY),
    m_blockSize(3),
    m_C(5)
{
}

QStringList AdaptiveThresholdFilter::codeSnippet() const
{
    QStringList snippet;

    QString adaptiveMethod;
    switch (m_adaptiveMethod) {
    case CV_ADAPTIVE_THRESH_MEAN_C:
        adaptiveMethod = "CV_ADAPTIVE_THRESH_MEAN_C";
        break;
    case CV_ADAPTIVE_THRESH_GAUSSIAN_C:
        adaptiveMethod = "CV_ADAPTIVE_THRESH_GAUSSIAN_C";
        break;
    default:
        qDebug() << "adaptiveThreshold: not known argument for adaptiveMethod";
    }

    QString thresholdType;
    switch (m_thresholdType) {
    case CV_THRESH_BINARY:
        thresholdType = "CV_THRESH_BINARY";
        break;
    case CV_THRESH_BINARY_INV:
        thresholdType = "CV_THRESH_BINARY_INV";
        break;
    default:
        qDebug() << "adaptiveThreshold: not known argument for thresholdType";
    }

    //TODO extra line with conversion when input has inappropriate type

    QString line = QString("cv::%1(%2, %3, %4, %5, %6, %7, %8);")
            .arg("adaptiveThreshold")
            .arg("src")
            .arg("dst")
            .arg(m_maxValue)
            .arg(adaptiveMethod)
            .arg(thresholdType)
            .arg(m_blockSize)
            .arg(m_C);

    snippet << line;

    return snippet;
}

//TODO int is temporary, should be double
void AdaptiveThresholdFilter::setMaxValue(int maxValue)
{
    m_maxValue = maxValue;
    emit updated();
}

//TODO QString is temporary, should be int
void AdaptiveThresholdFilter::setAdaptiveMethod(const QString &adaptiveMethod)
{
    if (adaptiveMethod == "CV_ADAPTIVE_THRESH_MEAN_C") {
        m_adaptiveMethod = CV_ADAPTIVE_THRESH_MEAN_C;
    } else if (adaptiveMethod == "CV_ADAPTIVE_THRESH_GAUSSIAN_C") {
        m_adaptiveMethod = CV_ADAPTIVE_THRESH_GAUSSIAN_C;
    }

    emit updated();
}

//TODO QString is temporary, should be int
void AdaptiveThresholdFilter::setThresholdType(const QString &thresholdType)
{
    if (thresholdType == "CV_THRESH_BINARY") {
        m_thresholdType = CV_THRESH_BINARY;
    } else if (thresholdType == "CV_THRESH_BINARY_INV") {
        m_thresholdType = CV_THRESH_BINARY_INV;
    }

    emit updated();
}

void AdaptiveThresholdFilter::setBlockSize(int)
{
    emit updated();
}

void AdaptiveThresholdFilter::setC(double)
{
    emit updated();
}

QDialog *AdaptiveThresholdFilter::createDialog(QWidget *parent)
{
    QDialog *dialog = new QDialog(parent);

    QLabel *signatureLabel = new QLabel;

    signatureLabel->setText("void <b>adaptiveThreshold</b>(<br>\
                            &nbsp; InputArray <b>src</b>,<br>\
                            &nbsp; OutputArray <b>dst</b>,<br>\
                            &nbsp; double <b>maxValue</b>,<br>\
                            &nbsp; int <b>adaptiveMethod</b>,<br>\
                            &nbsp; int <b>thresholdType</b>,<br>\
                            &nbsp; int <b>blockSize</b>,<br>\
                            &nbsp; double <b>C</b><br>\
                            )");

    QGroupBox *parametersGroup = new QGroupBox(tr("Parameters"));

    QFormLayout *formLayout = new QFormLayout;

    //TODO whole section
    QSlider *maxValue = new QSlider(Qt::Horizontal);
    maxValue->setRange(0, 255);
    maxValue->setValue(m_maxValue);
    formLayout->addRow(new QLabel("maxValue:"), maxValue);
    connect(maxValue, SIGNAL(valueChanged(int)),
            this, SLOT(setMaxValue(int)));

    QComboBox *adaptiveMethod = new QComboBox;
    adaptiveMethod->addItem("CV_ADAPTIVE_THRESH_MEAN_C");
    adaptiveMethod->addItem("CV_ADAPTIVE_THRESH_GAUSSIAN_C");
    switch(m_adaptiveMethod) {
    case CV_ADAPTIVE_THRESH_MEAN_C:
        adaptiveMethod->setCurrentText("CV_ADAPTIVE_THRESH_MEAN_C");
        break;
    case CV_ADAPTIVE_THRESH_GAUSSIAN_C:
        adaptiveMethod->setCurrentText("CV_ADAPTIVE_THRESH_GAUSSIAN_C");
        break;
    }
    formLayout->addRow(new QLabel("adaptiveMethod:"), adaptiveMethod);
    connect(adaptiveMethod, SIGNAL(currentIndexChanged(QString)),
            this, SLOT(setAdaptiveMethod(QString)));

    QComboBox *thresholdType = new QComboBox;
    thresholdType->addItem("CV_THRESH_BINARY");
    thresholdType->addItem("CV_THRESH_BINARY_INV");
    switch(m_thresholdType) {
    case CV_THRESH_BINARY:
        thresholdType->setCurrentText("CV_THRESH_BINARY");
        break;
    case CV_THRESH_BINARY_INV:
        thresholdType->setCurrentText("CV_THRESH_BINARY_INV");
        break;
    }
    formLayout->addRow(new QLabel("thresholdType:"), thresholdType);
    connect(thresholdType, SIGNAL(currentIndexChanged(QString)),
            this, SLOT(setThresholdType(QString)));

    formLayout->addRow(new QLabel("blockSize:"), new QLineEdit);
    formLayout->addRow(new QLabel("C:"), new QLineEdit);

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

cv::Mat &AdaptiveThresholdFilter::process(cv::Mat &input) const
{
    //TODO implement adaptive threshold
    switch (input.type()) {
    case CV_8UC4:
    case CV_8UC3:
        // adaptiveThreshold requires 8-bit single-channel input
        cv::cvtColor(input, input, CV_RGB2GRAY);
    case CV_8UC1:
        cv::adaptiveThreshold(input, input, m_maxValue, m_adaptiveMethod, m_thresholdType, m_blockSize, m_C);
        break;
    }

    return input;
}
