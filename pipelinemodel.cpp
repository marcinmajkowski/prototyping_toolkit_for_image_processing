#include <QBrush>

#include "pipelinemodel.h"

PipelineModel::PipelineModel(QObject *parent) :
    QAbstractListModel(parent)
{
    //TODO below only testing
    m_filters.push_back(QSharedPointer<Filter>(new AdaptiveThresholdFilter));
    m_filters.push_back(QSharedPointer<Filter>(new AdaptiveThresholdFilter));
    m_filters.push_back(QSharedPointer<Filter>(new AdaptiveThresholdFilter));
//    m_filters.insert(m_filters.size(), 3, QSharedPointer<Filter>());
//    insertRow(rowCount());
}

int PipelineModel::rowCount(const QModelIndex &/*parent*/) const
{
    return m_filters.size();
}

QVariant PipelineModel::data(const QModelIndex &index, int role) const
{
    QVariant result;

    switch (role) {
    case Qt::DisplayRole:
        if (m_filters[index.row()]) {
            result = m_filters[index.row()]->name();
        } else {
            result = "[EMPTY]";
        }
        break;
    case Qt::BackgroundRole:
        if (index.row() % 2) {
            QBrush redBackground(Qt::red);
            result = redBackground;
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
