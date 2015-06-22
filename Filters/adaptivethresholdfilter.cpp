#include <QDebug>
#include <QtWidgets>

#include "adaptivethresholdfilter.h"

AdaptiveThresholdFilter::AdaptiveThresholdFilter(QObject *parent) :
    Filter("Adaptive threshold", parent)
{
    qDebug() << "Adaptive threshold filter constructor.";
}

AdaptiveThresholdFilter::~AdaptiveThresholdFilter()
{
    qDebug() << "Adaptive threshold filter destructor.";
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

QDialog *AdaptiveThresholdFilter::createDialog()
{
    qDebug() << "createDialog() called in AdaptiveThresholdFilter";

    QDialog *dialog = new QDialog; //TODO here use e.g. FilterDialog class
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

    dialog->setLayout(dialogLayout);

    connect(acceptButton, SIGNAL(clicked()), dialog, SLOT(accept()));
    connect(rejectButton, SIGNAL(clicked()), dialog, SLOT(reject()));

    // connect widgets valueChange signals to appropriate slots/setters


    return dialog;
}
