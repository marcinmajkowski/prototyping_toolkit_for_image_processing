#include <QDebug>
#include <QDialog>
#include "adaptivethresholdfilter.h"

AdaptiveThresholdFilter::AdaptiveThresholdFilter(QObject *parent)
    : Filter("Adaptive threshold", parent)
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
    return new QDialog;
}
