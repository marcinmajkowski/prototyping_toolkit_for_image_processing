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

signals:
    void sourceCodeChanged(const QString &sourceCode);
    void outputPixmapChanged(const QPixmap &pixmap);

public slots:
    void appendItem(QTreeWidgetItem *item);
    void setInputPixmap(const QPixmap &pixmap);

protected slots:
    void deleteSelectedItems();
    void updateSourceCode();
    void updateOutputPixmap();

protected:
    bool dropMimeData(int index, const QMimeData *data, Qt::DropAction action) Q_DECL_OVERRIDE;
    FilterFactory *m_filterFactory;
    QPixmap m_inputPixmap;
};

#endif // PIPELINEWIDGET_H
