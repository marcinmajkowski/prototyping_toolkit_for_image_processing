#include <QDialog>

#include "filter.h"

Filter::Filter(const QString &name, QObject *parent) :
    QObject(parent),
    m_dialog(new QDialog()), //TODO temporary
    m_name(name)
{
}

Filter::~Filter()
{
    delete m_dialog; //TODO need better solution
}

QDialog *Filter::dialog()
{
    return m_dialog;
}

QString Filter::name()
{
    return m_name;
}
