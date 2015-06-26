#include "filterswidget.h"

#include <QHeaderView>
#include <QMimeData>

FiltersWidget::FiltersWidget(QWidget *parent) :
    QTreeWidget(parent)
{
    // remove header
    header()->close();

    setDragDropMode(QAbstractItemView::DragOnly);
}

QStringList FiltersWidget::mimeTypes() const
{
    return QStringList("text/plain");
}

QMimeData *FiltersWidget::mimeData(const QList<QTreeWidgetItem *> items) const
{
    QMimeData *mimeData = new QMimeData;
    QStringList strings;

    foreach (QTreeWidgetItem *item, items) {
        strings << item->text(0);
    }

    return mimeData;
}
