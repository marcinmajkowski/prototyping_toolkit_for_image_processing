#include "pipelineview.h"

PipelineView::PipelineView(QWidget *parent) :
    QListView(parent)
{
    setDragEnabled(true);
    setDragDropMode(QAbstractItemView::InternalMove);
//    setDragDropMode(QAbstractItemView::DragDrop);
    setDropIndicatorShown(true);
//    setAcceptDrops(true);
}
