#include <QVBoxLayout>
#include <QPushButton>

#include "filter.h"

Filter::Filter()
{
}

Filter::Filter(const QString &name, QWidget *parent)
    : m_parent(parent)
    , m_dialog(new QDialog(parent)) //TODO temporary
    , m_name(name)
{
    QLayout *layout = new QVBoxLayout();
    QWidget *button = new QPushButton("Test");
    QWidget *button2 = new QPushButton("test2");
    layout->addWidget(button);
    layout->addWidget(button2);
    m_dialog->setLayout(layout);
}

Filter::~Filter()
{
    delete m_dialog; //TODO need better solution
}

QDialog *Filter::dialog()
{
    return m_dialog;
}

QString Filter::name()
{
    return m_name;
}
