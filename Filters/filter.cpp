#include <QDebug>
#include <QDialog>

#include "filter.h"

Filter::Filter(const QString &name, QObject *parent) :
    QObject(parent),
    m_dialog(nullptr),
    m_name(name)
{
}

Filter::~Filter()
{
    delete m_dialog;
}

cv::Mat &Filter::process(cv::Mat &input) const
{
    return input;
}

QString Filter::codeSnippet() const
{
    return "\\\\ Filter";
}

QString Filter::name() const
{
    return m_name;
}

QDialog *Filter::createDialog(QWidget *parent)
{
    //TODO default implementation

    if (!m_dialog) {
        m_dialog = new QDialog;
    }

    m_dialog->setParent(parent, Qt::Dialog);

    return m_dialog;
}
