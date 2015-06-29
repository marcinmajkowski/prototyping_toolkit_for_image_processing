#ifndef PIPELINEWIDGETITEM_H
#define PIPELINEWIDGETITEM_H

#include <QListWidgetItem>

class Filter;

class PipelineWidgetItem : public QListWidgetItem
{
public:
    PipelineWidgetItem(QListWidget *parent = 0, int type = FilterType);
    PipelineWidgetItem(const QString &text, QListWidget *parent = 0, int type = FilterType);
    PipelineWidgetItem(const QIcon &icon, const QString &text, QListWidget *parent = 0, int type = FilterType);
    PipelineWidgetItem(const QListWidgetItem &other);
    ~PipelineWidgetItem();

    void setFilter(Filter *filter);
    Filter *filter();

    enum ItemType { FilterType = QListWidgetItem::ItemType::UserType + 1 };

private:
    void init();
    Filter *m_filter;
};

#endif // PIPELINEWIDGETITEM_H
