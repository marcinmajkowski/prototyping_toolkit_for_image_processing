#include <QDebug>
#include "adaptivethresholdfilter.h"

AdaptiveThresholdFilter::AdaptiveThresholdFilter()
    : Filter("Adaptive threshold")
{
    qDebug() << "Adaptive threshold filter constructor.";
}

AdaptiveThresholdFilter::~AdaptiveThresholdFilter()
{
    qDebug() << "Adaptive threshold filter destructor.";
}
