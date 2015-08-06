#include "filterswidget.h"

#include <QHeaderView>

#include "Filters/adaptivethresholdfilter.h"
#include "Filters/thresholdfilter.h"
#include "Filters/colorspaceconversionfilter.h"
#include "Filters/dilatefilter.h"
#include "Filters/erodefilter.h"
#include "Filters/blurfilter.h"
#include "Filters/histogramequalizationfilter.h"
#include "Filters/absolutedifferencefilter.h"
#include "Filters/bitwiseandfilter.h"

FiltersWidget::FiltersWidget(QWidget *parent) :
    QTreeWidget(parent)
{
    header()->close();
    setDragEnabled(true);

    QTreeWidgetItem *treeItem;
    treeItem = new QTreeWidgetItem(this, QStringList("Image transformations"));
    treeItem->setFlags(treeItem->flags() ^ Qt::ItemIsDragEnabled);

    appendFilter<ThresholdFilter>(treeItem);
    appendFilter<AdaptiveThresholdFilter>(treeItem);
    appendFilter<ColorSpaceConversionFilter>(treeItem);
    appendFilter<BlurFilter>(treeItem);
    appendFilter<HistogramEqualizationFilter>(treeItem);

    treeItem = new QTreeWidgetItem(this, QStringList("Morphological operations"));
    treeItem->setFlags(treeItem->flags() ^ Qt::ItemIsDragEnabled);

    appendFilter<ErodeFilter>(treeItem);
    appendFilter<DilateFilter>(treeItem);

    treeItem = new QTreeWidgetItem(this, QStringList("Array operations"));
    treeItem->setFlags(treeItem->flags() ^ Qt::ItemIsDragEnabled);

    appendFilter<AbsoluteDifferenceFilter>(treeItem);
    appendFilter<BitwiseAndFilter>(treeItem);
}

template <class T>
void FiltersWidget::appendFilter(QTreeWidgetItem *treeItem)
{
    new QTreeWidgetItem(treeItem, QStringList(T::filterName));
    qRegisterMetaType<T *>(T::filterName.toUtf8().constData());
}
