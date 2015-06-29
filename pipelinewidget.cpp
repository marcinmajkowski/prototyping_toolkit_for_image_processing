#include <QDebug>
#include <QMimeData>
#include <QShortcut>
#include <QTreeWidgetItem>

#include "pipelinewidget.h"
#include "pipelinewidgetitem.h"
#include "filterfactory.h"

PipelineWidget::PipelineWidget(QWidget *parent) :
    QListWidget(parent),
    m_filterFactory(new FilterFactory(this))
{
    setDropIndicatorShown(true);
    setDragDropMode(QAbstractItemView::DragDrop);
    setDefaultDropAction(Qt::MoveAction);

    setSelectionMode(QAbstractItemView::ExtendedSelection);

    QShortcut* shortcut = new QShortcut(QKeySequence(Qt::Key_Delete), this);
    connect(shortcut, SIGNAL(activated()), this, SLOT(deleteItem()));

    connect(model(), SIGNAL(rowsRemoved(QModelIndex,int,int)),
            this, SIGNAL(updated()));
    connect(model(), SIGNAL(rowsInserted(QModelIndex,int,int)),
            this, SIGNAL(updated()));
    connect(model(), SIGNAL(rowsMoved(QModelIndex,int,int,QModelIndex,int)),
            this, SIGNAL(updated()));
    connect(model(), SIGNAL(dataChanged(QModelIndex,QModelIndex)),
            this, SIGNAL(updated()));
}

Filter *PipelineWidget::filter(int row) const
{
    //TODO implement this in data() with extra role
    PipelineWidgetItem *pipelineItem = dynamic_cast<PipelineWidgetItem *>(item(row));
    if (pipelineItem) {
        return pipelineItem->filter();
    } else {
        return nullptr;
    }
}

void PipelineWidget::appendItem(QTreeWidgetItem *treeItem, int column)
{
    Q_UNUSED(column);

    if (treeItem->childCount() != 0) {
        return;
    }

    QString filterName = treeItem->text(0);
    Filter *filter = m_filterFactory->create(filterName);
    if (filter) {
        PipelineWidgetItem *item = new PipelineWidgetItem(filterName);
        item->setFilter(filter);
        addItem(item);
    }
}

void PipelineWidget::deleteItem()
{
    qDeleteAll(selectedItems());
}

bool PipelineWidget::dropMimeData(int index, const QMimeData *data, Qt::DropAction action)
{
    Q_UNUSED(action);

    //TODO tests for correctness
    QByteArray encoded = data->data(data->formats().at(0));
    QDataStream stream(&encoded, QIODevice::ReadOnly);

    int row, col;
    QMap<int, QVariant> roleDataMap;
    stream >> row >> col >> roleDataMap;
    QString filterName = roleDataMap.first().toString();

    Filter *filter = m_filterFactory->create(filterName);

    if (!filter) {
        return false;
    }

    PipelineWidgetItem *item = new PipelineWidgetItem(filterName);
    item->setFilter(filter);
    insertItem(index, item);

    return true;
    //    return QListWidget::dropMimeData(index, data, action);
}
