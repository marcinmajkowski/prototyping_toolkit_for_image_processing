#include <QDebug>

#include "pipelinewidgetitem.h"
#include "Filters/filter.h"

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
    if (role == FilterRole) {
        QVariant var;
        var.setValue(m_filter);
        return var;
    } else {
        return QListWidgetItem::data(role);
    }
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
    setData(Qt::BackgroundColorRole, QBrush(Qt::red));
    setFlags(flags() | Qt::ItemIsUserCheckable);
    setCheckState(Qt::Checked);
}
