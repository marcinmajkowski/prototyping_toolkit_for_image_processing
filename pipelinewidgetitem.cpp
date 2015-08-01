#include <QDebug>

#include "pipelinewidgetitem.h"
#include "Filters/filter.h"

Q_DECLARE_OPAQUE_POINTER(QDialog *)
Q_DECLARE_METATYPE(QDialog *)

PipelineWidgetItem::PipelineWidgetItem(QListWidget *parent, int type) :
    QListWidgetItem(parent, type),
    m_filter(nullptr)
{
    init();
}

PipelineWidgetItem::PipelineWidgetItem(const QString &text, QListWidget *parent, int type) :
    QListWidgetItem(text, parent, type),
    m_filter(nullptr)
{
    init();
}

PipelineWidgetItem::PipelineWidgetItem(const QIcon &icon, const QString &text, QListWidget *parent, int type) :
    QListWidgetItem(icon, text, parent, type),
    m_filter(nullptr)
{
    init();
}

PipelineWidgetItem::PipelineWidgetItem(const QListWidgetItem &other) :
    QListWidgetItem(other),
    m_filter(nullptr)
{

}

PipelineWidgetItem::~PipelineWidgetItem()
{
    delete m_filter;
}

QVariant PipelineWidgetItem::data(int role) const
{
    QVariant var;

    switch (role) {
    case FilterRole:
        var.setValue(m_filter);
        break;
    case FilterDialogRole:
        var.setValue(m_filter->createDialog(listWidget()));
        break;
    default:
        var = QListWidgetItem::data(role);
    }

    return var;
}

void PipelineWidgetItem::setData(int role, const QVariant &value)
{
    if (role == FilterRole) {
        delete m_filter;
        m_filter = value.value<Filter *>();
    } else {
        QListWidgetItem::setData(role, value);
    }
}

void PipelineWidgetItem::init()
{
    setFlags(flags() | Qt::ItemIsUserCheckable);
    setCheckState(Qt::Checked);
}
