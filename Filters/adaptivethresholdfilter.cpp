#include <QDebug>
#include "adaptivethresholdfilter.h"

AdaptiveThresholdFilter::AdaptiveThresholdFilter(QWidget *parent)
    : Filter("Adaptive threshold", parent)
{
    qDebug() << "Adaptive threshold filter constructor.";
}

AdaptiveThresholdFilter::~AdaptiveThresholdFilter()
{
    qDebug() << "Adaptive threshold filter destructor.";
}
