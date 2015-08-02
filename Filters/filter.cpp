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

QLayout *Filter::dialogParametersGroupLayout()
{
    QLabel *message = new QLabel("No settings for this filter.");

    QLayout *layout = new QVBoxLayout;
    layout->addWidget(message);

    return layout;
}

QLabel *Filter::dialogDescriptionLabel()
{
    QLabel *label = new QLabel;
    label->setText("Default filter (blank).");

    return label;
}

QDialog *Filter::createDialog(QWidget *parent)
{
    QGroupBox *parametersGroup = new QGroupBox(tr("Parameters"));
    parametersGroup->setLayout(dialogParametersGroupLayout());

    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
                                                       | QDialogButtonBox::Cancel);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(dialogDescriptionLabel());
    mainLayout->addWidget(parametersGroup);
    mainLayout->addWidget(buttonBox);

    QDialog *dialog = new QDialog(parent);
    dialog->setLayout(mainLayout);
    dialog->setWindowTitle(tr("%1 %2").arg(m_name).arg("settings"));

    connect(buttonBox, SIGNAL(accepted()), dialog, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), dialog, SLOT(reject()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(restoreParameters()));

    storeParameters(); //TODO should execute on every dialog->exec()

    return dialog;
}
