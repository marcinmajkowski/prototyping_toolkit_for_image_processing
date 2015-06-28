#ifndef PIPELINEWIDGETITEM_H
#define PIPELINEWIDGETITEM_H

#include <QListWidgetItem>

class PipelineWidgetItem : public QListWidgetItem
{
public:
    PipelineWidgetItem(QListWidget *parent = 0, int type = FilterType);
    PipelineWidgetItem(const QString &text, QListWidget *parent = 0, int type = FilterType);
    PipelineWidgetItem(const QIcon &icon, const QString &text, QListWidget *parent = 0, int type = FilterType);
    PipelineWidgetItem(const QListWidgetItem &other);
    ~PipelineWidgetItem();

    enum ItemType { FilterType = QListWidgetItem::ItemType::UserType + 1 };

private:
    void init();
};

#endif // PIPELINEWIDGETITEM_H
