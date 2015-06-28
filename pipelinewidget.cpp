#include <QDebug>
#include <QMimeData>
#include <QShortcut>
#include <QTreeWidgetItem>

#include "pipelinewidget.h"
#include "pipelinewidgetitem.h"

PipelineWidget::PipelineWidget(QWidget *parent) :
    QListWidget(parent)
{
    setDropIndicatorShown(true);
    setDragDropMode(QAbstractItemView::DragDrop);
    setDefaultDropAction(Qt::MoveAction);

    setSelectionMode(QAbstractItemView::ExtendedSelection);

    QShortcut* shortcut = new QShortcut(QKeySequence(Qt::Key_Delete), this);
    connect(shortcut, SIGNAL(activated()), this, SLOT(deleteItem()));
}

void PipelineWidget::appendItem(QTreeWidgetItem *treeItem, int column)
{
    Q_UNUSED(column);

    if (treeItem->childCount() != 0) {
        return;
    }

    QString filterName = treeItem->text(0);
    QListWidgetItem *item = new PipelineWidgetItem(filterName);
    addItem(item);
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

    QListWidgetItem *item = new PipelineWidgetItem(filterName);
    insertItem(index, item);

    return true;
//    return QListWidget::dropMimeData(index, data, action);
}
