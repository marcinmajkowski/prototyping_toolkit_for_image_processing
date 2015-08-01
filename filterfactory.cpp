#include <QDebug>

#include "filterfactory.h"

#include "Filters/filter.h"

FilterFactory::FilterFactory(QObject *parent) :
    QObject(parent)
{
}

Filter *FilterFactory::create(const QString &type, FilterObserver *observer, QObject *parent)
{
    Filter *filter = nullptr;

    int filterType = QMetaType::type(type.toUtf8().constData());
    if (filterType != QMetaType::UnknownType) {
        const QMetaObject *metaObject = QMetaType::metaObjectForType(filterType);
        QObject *object = metaObject->newInstance(
                    Q_ARG(FilterObserver *, observer), Q_ARG(QObject *, parent));
        filter = dynamic_cast<Filter *>(object);
    }

    if (filter == nullptr) {
        qDebug() << "FilterFactory::create(): not known filter type" << type;
    }

    return filter;
}
