#ifndef PIPELINEMODEL_H
#define PIPELINEMODEL_H

#include <QAbstractListModel>
#include <QSharedPointer>
#include <QVector>
#include <opencv2/core/core.hpp>

class FilterFactory;
class Filter;

class PipelineModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit PipelineModel(QObject *parent = 0);

    enum { DialogRole = Qt::UserRole };

    int rowCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) Q_DECL_OVERRIDE;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) Q_DECL_OVERRIDE;
    Qt::ItemFlags flags(const QModelIndex &index) const Q_DECL_OVERRIDE;
    Qt::DropActions supportedDropActions() const Q_DECL_OVERRIDE;
    bool moveRows(const QModelIndex &sourceParent, int sourceRow, int count, const QModelIndex &destinationParent, int destinationChild) Q_DECL_OVERRIDE;
    bool dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent) Q_DECL_OVERRIDE;
    QMimeData *mimeData(const QModelIndexList &indexes) const Q_DECL_OVERRIDE;

signals:
    void resultChanged(const QPixmap &pixmap);

public slots:
    void setInitialPixmap(const QPixmap &pixmap);
    void setResult(cv::Mat result);
    void update();

protected:
    QVector<QSharedPointer<Filter> > m_filters;
    FilterFactory *filterFactory;
};

#endif // PIPELINEMODEL_H
