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
    m_adaptiveMethodMap.insert(CV_ADAPTIVE_THRESH_MEAN_C, "CV_ADAPTIVE_THRESH_MEAN_C");
    m_adaptiveMethodMap.insert(CV_ADAPTIVE_THRESH_GAUSSIAN_C, "CV_ADAPTIVE_THRESH_GAUSSIAN_C");

    m_thresholdTypeMap.insert(CV_THRESH_BINARY, "CV_THRESH_BINARY");
    m_thresholdTypeMap.insert(CV_THRESH_BINARY_INV, "CV_THRESH_BINARY_INV");
}

QStringList AdaptiveThresholdFilter::codeSnippet() const
{
    QStringList snippet;

    //TODO extra line with conversion when input has inappropriate type

    QString line = QString("cv::%1(%2, %3, %4, %5, %6, %7, %8);")
            .arg("adaptiveThreshold")
            .arg("img")
            .arg("img")
            .arg(m_maxValue)
            .arg(m_adaptiveMethodMap[m_adaptiveMethod])
            .arg(m_thresholdTypeMap[m_thresholdType])
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
    m_adaptiveMethod = m_adaptiveMethodMap.key(adaptiveMethod);

    emit updated();
}

//TODO QString is temporary, should be int
void AdaptiveThresholdFilter::setThresholdType(const QString &thresholdType)
{
    m_thresholdType = m_thresholdTypeMap.key(thresholdType);

    emit updated();
}

void AdaptiveThresholdFilter::setBlockSize(int blockSize)
{
    if  (blockSize % 2 != 1) {
        blockSize++;
    }

    m_blockSize = blockSize;

    emit updated();
}

void AdaptiveThresholdFilter::setC(double c)
{
    m_C = c;

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
    foreach (const QString &s, m_adaptiveMethodMap) {
        adaptiveMethod->addItem(s);
    }

    adaptiveMethod->setCurrentText(m_adaptiveMethodMap[m_adaptiveMethod]);
    formLayout->addRow(new QLabel("adaptiveMethod:"), adaptiveMethod);
    connect(adaptiveMethod, SIGNAL(currentIndexChanged(QString)),
            this, SLOT(setAdaptiveMethod(QString)));

    QComboBox *thresholdType = new QComboBox;
    foreach(const QString &s, m_thresholdTypeMap) {
        thresholdType->addItem(s);
    }

    thresholdType->setCurrentText(m_thresholdTypeMap[m_thresholdType]);
    formLayout->addRow(new QLabel("thresholdType:"), thresholdType);
    connect(thresholdType, SIGNAL(currentIndexChanged(QString)),
            this, SLOT(setThresholdType(QString)));

//    QSpinBox blockSize = new QSpinBox;
    QSlider *blockSize = new QSlider(Qt::Horizontal);
    blockSize->setRange(3, 399);
    blockSize->setSingleStep(2);
    blockSize->setPageStep(6);
    blockSize->setValue(m_blockSize);
    formLayout->addRow(new QLabel("blockSize:"), blockSize);
    connect(blockSize, SIGNAL(valueChanged(int)),
            this, SLOT(setBlockSize(int)));

    QDoubleSpinBox *c = new QDoubleSpinBox;
    c->setMinimum(-c->maximum());
    c->setValue(m_C);
    formLayout->addRow(new QLabel("C:"), c);
    connect(c, SIGNAL(valueChanged(double)),
            this, SLOT(setC(double)));

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
