#include <QDebug>
#include <QDialog>

#include "filter.h"

Filter::Filter(const QString &name, QObject *parent) :
    QObject(parent),
    m_name(name)
{
}

Filter::~Filter()
{
}

cv::Mat &Filter::process(cv::Mat &input) const
{
    return input;
}

QStringList Filter::codeSnippet() const
{
    return QStringList("\\\\ Filter");
}

QString Filter::name() const
{
    return m_name;
}

QDialog *Filter::createDialog(QWidget *parent)
{
    //TODO default implementation
    return new QDialog(parent);
}
