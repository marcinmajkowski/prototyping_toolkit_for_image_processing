#ifndef PIPELINEWIDGET_H
#define PIPELINEWIDGET_H

#include <QListWidget>

class QTreeWidgetItem;
class FilterFactory;

class PipelineWidget : public QListWidget
{
    Q_OBJECT
public:
    explicit PipelineWidget(QWidget *parent = 0);

signals:
    void dataChanged();

public slots:
    void appendItem(QTreeWidgetItem *item, int column);
    void deleteItem();

protected:
    bool dropMimeData(int index, const QMimeData *data, Qt::DropAction action) Q_DECL_OVERRIDE;
    FilterFactory *m_filterFactory;
};

#endif // PIPELINEWIDGET_H
