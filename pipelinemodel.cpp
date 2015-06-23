#include <QBrush>
#include <QWidget>
#include <QDialog>

#include "pipelinemodel.h"
#include "filterfactory.h"
#include "Filters/filter.h"

PipelineModel::PipelineModel(QObject *parent) :
    QAbstractListModel(parent)
{
    filterFactory = new FilterFactory(this);
    //TODO below only testing
//    m_filters.push_back(QSharedPointer<Filter>(new AdaptiveThresholdFilter));
//    m_filters.push_back(QSharedPointer<Filter>(new AdaptiveThresholdFilter));
//    m_filters.push_back(QSharedPointer<Filter>(new AdaptiveThresholdFilter));
//    m_filters.insert(m_filters.size(), 3, QSharedPointer<Filter>());
//    insertRow(rowCount());
//    setData(index(1), QVariant("Adaptive threshold"));
//    setData(index(2), QVariant("Other filter"));
}

int PipelineModel::rowCount(const QModelIndex &/*parent*/) const
{
    return m_filters.size();
}

QVariant PipelineModel::data(const QModelIndex &index, int role) const
{
    QVariant result = QVariant();
    int row = index.row();
    QSharedPointer<Filter> filter = m_filters[row];

    switch (role) {
    case Qt::DisplayRole:
        //TODO move these ifs to the top
        if (filter) {
            result = filter->name();
        } else {
            result = "[EMPTY]";
        }
        break;
    case Qt::BackgroundRole:
        if (filter) {
            if (filter->updated()) {
                result = QBrush(Qt::green);
            } else {
                result = QBrush(Qt::red);
            }
        }
        break;
    case DialogRole:
        //TODO
        if (filter) {
            result = QVariant::fromValue(filter->dialog());
        }
        break;
    }

    return result;
}

bool PipelineModel::insertRows(int row, int count, const QModelIndex &parent)
{
    if (row < 0 || row > m_filters.size()) {
        return false;
    }

    beginInsertRows(parent, row, row + count - 1);
    m_filters.insert(row, count, QSharedPointer<Filter>());
    endInsertRows();
    return true;
}

bool PipelineModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (role != Qt::EditRole) {
        return false;
    }

    int row = index.row();

    //TODO is it necessary here?
    if (row > m_filters.size()) {
        return false;
    }

    QString filterType = value.toString();

    m_filters[row] = QSharedPointer<Filter>(filterFactory->create(filterType));

    emit dataChanged(index, index);

    return true;
}

void PipelineModel::setInitialPixmap(const QPixmap &pixmap)
{
    //TODO store initial Mat and pass it through the pipeline
    emit resultChanged(pixmap); //TODO do this only if pipeline is empty
}
