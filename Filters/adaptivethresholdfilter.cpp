#include <QDebug>
#include <QtWidgets>

#include <opencv2/imgproc/imgproc.hpp>

#include "adaptivethresholdfilter.h"

AdaptiveThresholdFilter::AdaptiveThresholdFilter(QObject *parent) :
    Filter("Adaptive threshold", parent),
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

void AdaptiveThresholdFilter::setMaxValue(double)
{

}

void AdaptiveThresholdFilter::setAdaptiveMethod(int)
{

}

void AdaptiveThresholdFilter::setThresholdType(int)
{

}

void AdaptiveThresholdFilter::setBlockSize(int)
{

}

void AdaptiveThresholdFilter::setC(double)
{

}

QDialog *AdaptiveThresholdFilter::createDialog(QWidget *parent)
{
    if (!m_dialog) {
        m_dialog = new QDialog; //TODO here use e.g. FilterDialog class
        // derived FilterDialog should on exec() (onShow with event not spontaneous)
        // store current values somehow so they can be restored later

        // add appropriate widgets and set their values to current parameters
        QVBoxLayout *dialogLayout = new QVBoxLayout;
        QHBoxLayout *buttonsLayout = new QHBoxLayout;
        QLabel *signatureLabel = new QLabel;
        QPushButton *acceptButton = new QPushButton("OK");
        QPushButton *rejectButton = new QPushButton("Cancel");
        QGroupBox *parametersGroup = new QGroupBox(tr("Parameters"));

        signatureLabel->setText("void <b>adaptiveThreshold</b>(InputArray <b>src</b>, OutputArray <b>dst</b>, double <b>maxValue</b>, int <b>adaptiveMethod</b>, int <b>thresholdType</b>, int <b>blockSize</b>, double <b>C</b>)");
        signatureLabel->setWordWrap(true);

        buttonsLayout->addStretch();
        buttonsLayout->addWidget(rejectButton);
        buttonsLayout->addWidget(acceptButton);

        dialogLayout->addWidget(signatureLabel);
        dialogLayout->addWidget(parametersGroup);
        dialogLayout->addStretch();
        dialogLayout->addLayout(buttonsLayout);

        m_dialog->setLayout(dialogLayout);

        connect(acceptButton, SIGNAL(clicked()), m_dialog, SLOT(accept()));
        connect(rejectButton, SIGNAL(clicked()), m_dialog, SLOT(reject()));
    }

    m_dialog->setParent(parent, Qt::Dialog);

    return m_dialog;
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
