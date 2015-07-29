#include <QDebug>
#include <QtWidgets>

//TODO move this class to Filters directory
#include "filterobserver.h"

#include "filter.h"

Filter::Filter(const QString &name, FilterObserver *observer, QObject *parent) :
    QObject(parent),
    m_name(name),
    m_filterObserver(observer)
{
    if (m_filterObserver) {
        connect(this, SIGNAL(updated()), m_filterObserver, SLOT(update()));
    }
}

Filter::~Filter()
{
    if (m_filterObserver) {
        disconnect(this, SIGNAL(updated()), m_filterObserver, SLOT(update()));
    }
}

cv::Mat &Filter::process(cv::Mat &input)
{
    return input;
}

QStringList Filter::codeSnippet() const
{
    return QStringList("// Filter");
}

QString Filter::name() const
{
    return m_name;
}

void Filter::read(QDataStream &data)
{
    qDebug() << "Filter::read() called";
}

void Filter::write(QDataStream &data) const
{
    qDebug() << "Filter::write() called";
}

void Filter::storeParameters()
{
    m_parameters.clear();
    QDataStream dataStream(&m_parameters, QIODevice::WriteOnly);
    write(dataStream);
}

void Filter::restoreParameters()
{
    QDataStream dataStream(&m_parameters, QIODevice::ReadOnly);
    read(dataStream);
}

QDialog *Filter::createDialog(QWidget *parent)
{
    QDialog *dialog = new QDialog(parent);

    QLabel *message = new QLabel("No settings for this filter.");

    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok);

    connect(buttonBox, SIGNAL(accepted()), dialog, SLOT(accept()));

    QVBoxLayout *mainLayout = new QVBoxLayout;

    mainLayout->addWidget(message);
    mainLayout->addWidget(buttonBox);

    dialog->setLayout(mainLayout);

    dialog->setWindowTitle(tr("%1 %2").arg(m_name).arg("settings"));

    return dialog;
}
