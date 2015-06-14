#include <QBrush>

#include "pipelinemodel.h"

PipelineModel::PipelineModel(QObject *parent) :
    QAbstractListModel(parent)
{
    //TODO below only testing
    m_filters.push_back(QSharedPointer<Filter>(new AdaptiveThresholdFilter));
    m_filters.push_back(QSharedPointer<Filter>(new AdaptiveThresholdFilter));
    m_filters.push_back(QSharedPointer<Filter>(new AdaptiveThresholdFilter));
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
        result = m_filters[index.row()]->name();
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
