#include "filter.h"

Filter::Filter()
{
}

Filter::Filter(const QString &name)
    : m_name(name)
    , m_widget(new QWidget()) //TODO temporary
{
    m_widget->setWindowTitle("Filter widget window title test"); //TODO
}

Filter::~Filter()
{
    delete m_widget; //TODO need better solution
}

QWidget *Filter::widget()
{
    return m_widget;
}

QString Filter::name()
{
    return m_name;
}
