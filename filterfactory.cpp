#include <QDebug>

#include "filterfactory.h"

FilterFactory::FilterFactory(QObject *parent) :
    QObject(parent)
{
    qDebug() << "FilterFactory constructor";
}

FilterFactory::~FilterFactory()
{
    qDebug() << "FilterFactory destructor";
}

Filter *FilterFactory::create(const QString &type)
{
    Filter *result = nullptr;

    if (type == "Adaptive threshold") {
        result = new AdaptiveThresholdFilter;
    } else {
        qDebug() << "FilterFactory::create(): not known filter type" << type;
    }

    return result;
}
