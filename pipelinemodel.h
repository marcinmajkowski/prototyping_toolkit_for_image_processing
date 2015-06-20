#ifndef PIPELINEMODEL_H
#define PIPELINEMODEL_H

#include <QAbstractListModel>
#include <QSharedPointer>
#include <QVector>

class FilterFactory;
class Filter;

class PipelineModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit PipelineModel(QObject *parent = 0);

    enum { WidgetRole = Qt::UserRole };

    int rowCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) Q_DECL_OVERRIDE;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) Q_DECL_OVERRIDE;

signals:

public slots:

protected:
    QVector<QSharedPointer<Filter> > m_filters;
    FilterFactory *filterFactory;
};

#endif // PIPELINEMODEL_H
