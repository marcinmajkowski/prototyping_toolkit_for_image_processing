#ifndef FILTERFACTORY_H
#define FILTERFACTORY_H

#include <QObject>

class Filter;
class FilterObserver;

class FilterFactory : public QObject
{
    Q_OBJECT
public:
    explicit FilterFactory(QObject *parent = 0);

    Filter *create(const QString &type, FilterObserver *observer = 0, QObject *parent = 0);

signals:

public slots:

};

#endif // FILTERFACTORY_H
