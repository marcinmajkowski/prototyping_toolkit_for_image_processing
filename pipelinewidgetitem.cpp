#include "pipelinewidgetitem.h"

PipelineWidgetItem::PipelineWidgetItem(QListWidget *parent, int type) :
    QListWidgetItem(parent, type)
{
    init();
}

PipelineWidgetItem::PipelineWidgetItem(const QString &text, QListWidget *parent, int type) :
    QListWidgetItem(text, parent, type)
{
    init();
}

PipelineWidgetItem::PipelineWidgetItem(const QIcon &icon, const QString &text, QListWidget *parent, int type) :
    QListWidgetItem(icon, text, parent, type)
{
    init();
}

PipelineWidgetItem::PipelineWidgetItem(const QListWidgetItem &other) :
    QListWidgetItem(other)
{

}

PipelineWidgetItem::~PipelineWidgetItem()
{

}

void PipelineWidgetItem::init()
{
    setData(Qt::BackgroundColorRole, QBrush(Qt::red));
    setFlags(flags() | Qt::ItemIsUserCheckable);
    setCheckState(Qt::Checked);
}
