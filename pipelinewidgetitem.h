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

    QVariant data(int role) const Q_DECL_OVERRIDE;
    void setData(int role, const QVariant &value) Q_DECL_OVERRIDE;

    enum ItemType { FilterType = QListWidgetItem::ItemType::UserType + 1 };
    enum {
        FilterRole = Qt::UserRole + 1,
        FilterDialogRole
    };

private:
    void init();
    Filter *m_filter;
};

#endif // PIPELINEWIDGETITEM_H
