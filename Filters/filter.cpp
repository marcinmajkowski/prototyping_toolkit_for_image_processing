#include "filter.h"

Filter::Filter()
{
}

Filter::Filter(const QString &name)
    : m_name(name)
{
}

Filter::~Filter()
{

}

QString Filter::name()
{
    return m_name;
}
