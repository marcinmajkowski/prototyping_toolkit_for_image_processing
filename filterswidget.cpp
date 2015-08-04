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

    QTreeWidgetItem *treeItem;
    treeItem = new QTreeWidgetItem(this, QStringList("Image transformations"));
    treeItem->setFlags(treeItem->flags() ^ Qt::ItemIsDragEnabled);

    new QTreeWidgetItem(treeItem, QStringList("Threshold"));
    qRegisterMetaType<ThresholdFilter *>("Threshold");

    new QTreeWidgetItem(treeItem, QStringList("Adaptive threshold"));
    qRegisterMetaType<AdaptiveThresholdFilter *>("Adaptive threshold");

    new QTreeWidgetItem(treeItem, QStringList("Color space conversion"));
    qRegisterMetaType<ColorSpaceConversionFilter *>("Color space conversion");

    new QTreeWidgetItem(treeItem, QStringList("Blur"));
    qRegisterMetaType<BlurFilter *>("Blur");

    new QTreeWidgetItem(treeItem, QStringList("Histogram equalization"));
    qRegisterMetaType<HistogramEqualizationFilter *>("Histogram equalization");

    treeItem = new QTreeWidgetItem(this, QStringList("Morphological operations"));
    treeItem->setFlags(treeItem->flags() ^ Qt::ItemIsDragEnabled);

    new QTreeWidgetItem(treeItem, QStringList("Erode"));
    qRegisterMetaType<ErodeFilter *>("Erode");

    new QTreeWidgetItem(treeItem, QStringList("Dilate"));
    qRegisterMetaType<DilateFilter *>("Dilate");

    treeItem = new QTreeWidgetItem(this, QStringList("Array operations"));
    treeItem->setFlags(treeItem->flags() ^ Qt::ItemIsDragEnabled);

    new QTreeWidgetItem(treeItem, QStringList("Absolute difference"));
    qRegisterMetaType<AbsoluteDifferenceFilter *>("Absolute difference");

    new QTreeWidgetItem(treeItem, QStringList("Bitwise and"));
    qRegisterMetaType<BitwiseAndFilter *>("Bitwise and");

    treeItem = new QTreeWidgetItem(this, QStringList("Others"));
    treeItem->setFlags(treeItem->flags() ^ Qt::ItemIsDragEnabled);

    new QTreeWidgetItem(treeItem, QStringList("Other filter"));

    setDragEnabled(true);
}
