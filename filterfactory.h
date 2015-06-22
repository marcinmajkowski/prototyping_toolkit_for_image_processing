#ifndef FILTERFACTORY_H
#define FILTERFACTORY_H

#include <QObject>

class Filter;

class FilterFactory : public QObject
{
    Q_OBJECT
public:
    explicit FilterFactory(QObject *parent = 0);

    Filter *create(const QString &type);

signals:

public slots:

};

#endif // FILTERFACTORY_H
