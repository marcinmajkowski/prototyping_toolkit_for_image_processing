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
    //TODO consider sharing data between filters
    if (input.data != m_input.data) {
        // do not copy if called by setEnabled()
        //TODO need better solution
        m_input = input.clone();
    }

    //TODO add flag to avoid unnecessary processing
    setStatus(Processing);
    emit resultExpired();

    if (m_enabled) {
        process(); //TODO call it in another thread
    } else {
        Filter::process(); // pass input to output, emit signal, change status
    }
}

void Filter::setWaitingForInput()
{
    setStatus(WaitingForInput);
    emit resultExpired();
}

void Filter::setEnabled(bool enabled)
{
    if (m_enabled == enabled) {
        return;
    }

    m_enabled = enabled;

    //TODO need better solution
    //now it will compute result even if it's appropriate
    setInput(m_input);
}

void Filter::setStatus(int status)
{
    if (status != m_status) {
        m_status = status;
        emit statusChanged();
    }
}

QDialog *Filter::createDialog()
{
    //TODO
    qDebug() << "createDialog() called in Filter";
    return new QDialog;
}

void Filter::process()
{
    setStatus(Ready);

    //TODO move out:
    setStatus(Ready);
    emit resultChanged(m_input); //TODO move out
}
