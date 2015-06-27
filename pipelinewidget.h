#ifndef PIPELINEWIDGET_H
#define PIPELINEWIDGET_H

#include <QListWidget>

class QTreeWidgetItem;

class PipelineWidget : public QListWidget
{
    Q_OBJECT
public:
    explicit PipelineWidget(QWidget *parent = 0);

signals:

public slots:
    void appendItem(QTreeWidgetItem *item, int column);
    void deleteItem();

protected:
    bool dropMimeData(int index, const QMimeData *data, Qt::DropAction action) Q_DECL_OVERRIDE;
};

#endif // PIPELINEWIDGET_H
