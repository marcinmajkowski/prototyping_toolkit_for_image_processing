#include <QBrush>

#include "pipelinemodel.h"

PipelineModel::PipelineModel(QObject *parent) :
    QAbstractListModel(parent)
{
}

int PipelineModel::rowCount(const QModelIndex &/*parent*/) const
{
    return 5;
}

QVariant PipelineModel::data(const QModelIndex &index, int role) const
{
    QVariant result;

    switch (role) {
    case Qt::DisplayRole:
        result = QString("Row %1, Column %2")
                .arg(index.row() + 1)
                .arg(index.column() + 1);
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
