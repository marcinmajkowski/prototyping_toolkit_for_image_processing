#include <QDebug>
#include <QDialog>

#include "filter.h"

Filter::Filter(const QString &name, QObject *parent) :
    QObject(parent),
    m_updated(false),
    m_dialog(nullptr), //TODO temporary
    m_name(name)
{
}

Filter::~Filter()
{
    delete m_dialog; //TODO need better solution
}

QDialog *Filter::dialog()
{
    if (!m_dialog) {
        m_dialog = createDialog();
    }

    return m_dialog;
}

QString Filter::name()
{
    return m_name;
}

bool Filter::updated()
{
    return m_updated;
}

QDialog *Filter::createDialog()
{
    //TODO
    qDebug() << "createDialog() called in Filter";
    return new QDialog;
}
