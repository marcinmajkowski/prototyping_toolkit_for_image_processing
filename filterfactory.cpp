#include <QDebug>

#include "filterfactory.h"

#include "Filters/adaptivethresholdfilter.h"
#include "Filters/thresholdfilter.h"
#include "Filters/colorspaceconversionfilter.h"
#include "Filters/dilatefilter.h"
#include "Filters/erodefilter.h"

FilterFactory::FilterFactory(QObject *parent) :
    QObject(parent)
{
}

Filter *FilterFactory::create(const QString &type, FilterObserver *observer, QObject *parent)
{
    Filter *result = nullptr;

    if (type == "Adaptive threshold") {
        result = new AdaptiveThresholdFilter(observer, parent);
    } else if (type == "Threshold") {
        result = new ThresholdFilter(observer, parent);
    } else if (type == "Color space conversion") {
        result = new ColorSpaceConversionFilter(observer, parent);
    } else if (type == "Dilate") {
        result = new DilateFilter(observer, parent);
    } else if (type == "Erode") {
        result = new ErodeFilter(observer, parent);
    } else {
        qDebug() << "FilterFactory::create(): not known filter type" << type;
    }

    return result;
}
