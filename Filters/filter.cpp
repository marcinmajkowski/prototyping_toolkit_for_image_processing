#include <QDebug>
#include <QtWidgets>

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
