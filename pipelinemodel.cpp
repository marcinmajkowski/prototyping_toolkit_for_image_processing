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
    QVariant result;

    switch (role) {
    case Qt::DisplayRole:
        //TODO move these ifs to the top
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
    case DialogRole:
        //TODO
        if (m_filters[index.row()]) {
            QDialog *dialog = m_filters[index.row()]->dialog();
            result = QVariant::fromValue(dialog);
        } else {
            //TODO
            result = QVariant::fromValue(0);
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
