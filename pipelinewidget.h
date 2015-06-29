#ifndef PIPELINEWIDGET_H
#define PIPELINEWIDGET_H

#include <QListWidget>

class QTreeWidgetItem;
class FilterFactory;
class Filter;

class PipelineWidget : public QListWidget
{
    Q_OBJECT
public:
    explicit PipelineWidget(QWidget *parent = 0);
    Filter *filter(int row) const;

signals:
    void sourceCodeChanged(const QString &sourceCode);

public slots:
    void appendItem(QTreeWidgetItem *item, int column);
    void deleteItem();

protected slots:
    void updateSourceCode();

protected:
    bool dropMimeData(int index, const QMimeData *data, Qt::DropAction action) Q_DECL_OVERRIDE;
    FilterFactory *m_filterFactory;
};

#endif // PIPELINEWIDGET_H
