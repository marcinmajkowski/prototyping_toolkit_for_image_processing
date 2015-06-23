#include <QDebug>
#include <QDialog>

#include "filter.h"

Filter::Filter(const QString &name, QObject *parent) :
    QObject(parent),
    m_status(NotReady),
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

int Filter::status()
{
    return m_status;
}

QDialog *Filter::createDialog()
{
    //TODO
    qDebug() << "createDialog() called in Filter";
    return new QDialog;
}
