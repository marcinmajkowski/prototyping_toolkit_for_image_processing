#include <QDebug>
#include <QDialog>

#include "filter.h"

Filter::Filter(const QString &name, QObject *parent) :
    QObject(parent),
    m_status(WaitingForInput),
    m_dialog(nullptr), //TODO temporary
    m_name(name),
    m_enabled(true)
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

bool Filter::enabled()
{
    return m_enabled;
}

void Filter::setInput(cv::Mat input)
{
    m_input = input.clone();
    m_status = Processing;
    emit resultExpired();

    if (m_enabled) {
        process(); //TODO call it in another thread
    } else {
        Filter::process(); // pass input to output, emit signal, change status
    }
}

void Filter::setWaitingForInput()
{
    m_status = WaitingForInput;
    emit resultExpired();
}

void Filter::setEnabled(bool enabled)
{
    m_enabled = enabled;
    //TODO change output to input
}

QDialog *Filter::createDialog()
{
    //TODO
    qDebug() << "createDialog() called in Filter";
    return new QDialog;
}

void Filter::process()
{
    //Do processing here
    m_result = m_input.clone(); //this is a default behaviour

    m_status = Ready;
    emit resultChanged(m_result);
}
