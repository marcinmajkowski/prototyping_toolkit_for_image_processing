#ifndef FILTERFACTORY_H
#define FILTERFACTORY_H

#include <QObject>

class FilterFactory : public QObject
{
    Q_OBJECT
public:
    explicit FilterFactory(QObject *parent = 0);
    ~FilterFactory();

signals:

public slots:

};

#endif // FILTERFACTORY_H
