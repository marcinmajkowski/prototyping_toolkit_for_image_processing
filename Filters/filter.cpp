#include "filter.h"

Filter::Filter()
{
}

Filter::Filter(const QString &name)
    : m_name(name)
    , m_dialog(new QDialog()) //TODO temporary
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
