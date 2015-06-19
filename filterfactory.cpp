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
