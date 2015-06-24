#include <QDebug>
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
            if (!filter->enabled()) {
                break;
            }
            switch (filter->status()) {
            case Filter::NotReady:
                result = QBrush(Qt::red);
                break;
            case Filter::Processing:
                result = QBrush(Qt::yellow);
                break;
            case Filter::Ready:
                result = QBrush(Qt::green);
            }
        }
        break;
    case Qt::CheckStateRole:
        if (filter) {
            if (filter->enabled()) {
                result = Qt::Checked;
            } else {
                result = Qt::Unchecked;
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
    int row = index.row();

    //TODO is it necessary here?
    if (row > m_filters.size()) {
        return false;
    }

    if (role == Qt::CheckStateRole) {
        int state = value.toInt();
        if (state == Qt::Checked) {
            m_filters[row]->setEnabled(true);
        } else if (state == Qt::Unchecked) {
            m_filters[row]->setEnabled(false);
        } else {
            return false;
        }
    } else if (role == Qt::EditRole) {
        QString filterType = value.toString();
        QSharedPointer<Filter> filter(filterFactory->create(filterType));
        m_filters[row] = filter;
        //TODO all necessary connections and DISCONNECTIONS
        // temporary below
        connect(filter.data(), SIGNAL(notReady()), this, SLOT(update()));
    }


    emit dataChanged(index, index);

    return true;
}

Qt::ItemFlags PipelineModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags flags = QAbstractListModel::flags(index);
    flags |= Qt::ItemIsUserCheckable;
//    flags ^= Qt::ItemIsSelectable;
    return flags;
}

void PipelineModel::setInitialPixmap(const QPixmap &pixmap)
{
    //TODO store initial Mat and pass it through the pipeline
    emit resultChanged(pixmap); //TODO do this only if pipeline is empty
}

void PipelineModel::update()
{
    Filter *sender = dynamic_cast<Filter *>(QObject::sender());

    if (sender == nullptr) {
        // sender is not a filter
        return;
    }

    // determine sender filter index
    int i = 0;
    for (QSharedPointer<Filter> f : m_filters) {
        if (f.data() == sender) {
            break;
        }
        ++i;
    }

    qDebug() << "Filter index" << i << "emmited update";

    if (i == m_filters.size()) {
        // sender filter is not stored in m_filters
        return;
    }

    QModelIndex modelIndex = index(i);
    emit dataChanged(modelIndex, modelIndex);
}
