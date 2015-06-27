#include "pipelineview.h"

PipelineView::PipelineView(QWidget *parent) :
    QListView(parent)
{
    setDragEnabled(true);
    setDragDropMode(QAbstractItemView::DragDrop);
    setDropIndicatorShown(true);
    setAcceptDrops(true);
    viewport()->setAcceptDrops(true);
}
