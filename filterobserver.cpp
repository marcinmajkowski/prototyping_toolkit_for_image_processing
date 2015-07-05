#include "filterobserver.h"

FilterObserver::FilterObserver(QObject *parent) :
    QObject(parent)
{
}

void FilterObserver::update()
{
    emit updated();
}
