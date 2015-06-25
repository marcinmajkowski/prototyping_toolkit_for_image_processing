#include <QDebug>
#include <QBrush>
#include <QWidget>
#include <QDialog>

#include "asmOpenCV.h"

#include "pipelinemodel.h"
#include "filterfactory.h"
#include "Filters/filter.h"

PipelineModel::PipelineModel(QObject *parent) :
    QAbstractListModel(parent),
    filterFactory(new FilterFactory(this))
{
}

int PipelineModel::rowCount(const QModelIndex &/*parent*/) const
{
    return m_filters.size();
}

QVariant PipelineModel::data(const QModelIndex &index, int role) const
{
    QVariant result = QVariant();
    int row = index.row();

    if (row >= m_filters.size()) {
        return result;
    }

    QSharedPointer<Filter> filter = m_filters[row];

    switch (role) {
    case Qt::DisplayRole:
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
            case Filter::WaitingForInput:
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

    if (row >= m_filters.size()) {
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

        //TODO refactor

        //TODO when setting first filter - reset image

        // disconnect connections TO m_filters[row]...
        // ...and connect them to filter
        QSharedPointer<Filter> previous;
        for (int i = row - 1; i >= 0; --i) {
            if (m_filters[i]) {
                previous = m_filters[i];
                break;
            }
        }
        if (previous) {
            if (m_filters[row]) {
                disconnect(previous.data(), SIGNAL(resultChanged(cv::Mat)),
                           m_filters[row].data(), SLOT(setInput(cv::Mat)));
                disconnect(previous.data(), SIGNAL(resultExpired()),
                           m_filters[row].data(), SLOT(setWaitingForInput()));
            }
            connect(previous.data(), SIGNAL(resultChanged(cv::Mat)),
                    filter.data(), SLOT(setInput(cv::Mat)));
            connect(previous.data(), SIGNAL(resultExpired()),
                    filter.data(), SLOT(setWaitingForInput()));
        }

        // disconnect connections FROM m_filters[row]...
        // ...and use filter instead
        QSharedPointer<Filter> next;
        for (int i = row + 1; i < m_filters.size(); ++i) {
            if (m_filters[i]) {
                next = m_filters[i];
                break;
            }
        }
        if (next) {
            if (m_filters[row]) {
                disconnect(m_filters[row].data(), SIGNAL(resultChanged(cv::Mat)),
                           next.data(), SLOT(setInput(cv::Mat)));
                disconnect(m_filters[row].data(), SIGNAL(resultExpired()),
                           next.data(), SLOT(setWaitingForInput()));
            }
            connect(filter.data(), SIGNAL(resultChanged(cv::Mat)),
                    next.data(), SLOT(setInput(cv::Mat)));
            connect(filter.data(), SIGNAL(resultExpired()),
                    next.data(), SLOT(setWaitingForInput()));
        } else {
            if (m_filters[row]) {
                disconnect(m_filters[row].data(), SIGNAL(resultChanged(cv::Mat)),
                           this, SLOT(setResult(cv::Mat)));
            }
            connect(filter.data(), SIGNAL(resultChanged(cv::Mat)),
                    this, SLOT(setResult(cv::Mat)));
        }

        if (m_filters[row]) {
            disconnect(m_filters[row].data(), SIGNAL(statusChanged()),
                       this, SLOT(update()));
        }

        connect(filter.data(), SIGNAL(statusChanged()),
                this, SLOT(update()));

        // replace m_filters[row] with filter
        m_filters[row] = filter;
    }

    emit dataChanged(index, index);

    return true;
}

Qt::ItemFlags PipelineModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags flags = QAbstractListModel::flags(index);
    flags |= Qt::ItemIsUserCheckable;
    return flags;
}

void PipelineModel::setInitialPixmap(const QPixmap &pixmap)
{
    for (QSharedPointer<Filter> filter : m_filters) {
        if (filter) {
            filter->setInput(ASM::QPixmapToCvMat(pixmap));
            return;
        }
    }

    // there is no valid filter in the pipeline
    emit resultChanged(pixmap);
}

void PipelineModel::setResult(cv::Mat result)
{
    emit resultChanged(ASM::cvMatToQPixmap(result));
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

//    qDebug() << "Filter index" << i << "emmited update";

    if (i == m_filters.size()) {
        // sender filter is not stored in m_filters
        return;
    }

    QModelIndex modelIndex = index(i);
    emit dataChanged(modelIndex, modelIndex);
}
