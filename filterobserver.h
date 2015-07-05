#ifndef FILTEROBSERVER_H
#define FILTEROBSERVER_H

#include <QObject>

class FilterObserver : public QObject
{
    Q_OBJECT
public:
    explicit FilterObserver(QObject *parent = 0);

signals:
    void updated();

public slots:
    void update();
};

#endif // FILTEROBSERVER_H
