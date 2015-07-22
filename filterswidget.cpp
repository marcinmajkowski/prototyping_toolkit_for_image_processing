#include "filterswidget.h"

#include <QHeaderView>

FiltersWidget::FiltersWidget(QWidget *parent) :
    QTreeWidget(parent)
{
    header()->close();

    QTreeWidgetItem *treeItem;
    treeItem = new QTreeWidgetItem(this, QStringList("Image transformations"));
    treeItem->setFlags(treeItem->flags() ^ Qt::ItemIsDragEnabled);
    new QTreeWidgetItem(treeItem, QStringList("Threshold"));
    new QTreeWidgetItem(treeItem, QStringList("Adaptive threshold"));
    new QTreeWidgetItem(treeItem, QStringList("Color space conversion"));
    new QTreeWidgetItem(treeItem, QStringList("Blur"));

    treeItem = new QTreeWidgetItem(this, QStringList("Morphological operations"));
    treeItem->setFlags(treeItem->flags() ^ Qt::ItemIsDragEnabled);
    new QTreeWidgetItem(treeItem, QStringList("Erode"));
    new QTreeWidgetItem(treeItem, QStringList("Dilate"));

    treeItem = new QTreeWidgetItem(this, QStringList("Others"));
    treeItem->setFlags(treeItem->flags() ^ Qt::ItemIsDragEnabled);
    new QTreeWidgetItem(treeItem, QStringList("Other filter"));

    setDragEnabled(true);
}
