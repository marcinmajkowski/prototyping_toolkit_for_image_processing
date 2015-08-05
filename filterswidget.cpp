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

    appendFilter<ThresholdFilter>("Threshold", treeItem);
    appendFilter<AdaptiveThresholdFilter>("Adaptive threshold", treeItem);
    appendFilter<ColorSpaceConversionFilter>("Color space conversion", treeItem);
    appendFilter<BlurFilter>("Blur", treeItem);
    appendFilter<HistogramEqualizationFilter>("Histogram equalization", treeItem);

    treeItem = new QTreeWidgetItem(this, QStringList("Morphological operations"));
    treeItem->setFlags(treeItem->flags() ^ Qt::ItemIsDragEnabled);

    appendFilter<ErodeFilter>("Erode", treeItem);
    appendFilter<DilateFilter>("Dilate", treeItem);

    treeItem = new QTreeWidgetItem(this, QStringList("Array operations"));
    treeItem->setFlags(treeItem->flags() ^ Qt::ItemIsDragEnabled);

    appendFilter<AbsoluteDifferenceFilter>("Absolute difference", treeItem);
    appendFilter<BitwiseAndFilter>("Bitwise and", treeItem);
}

template <class T>
void FiltersWidget::appendFilter(QString name, QTreeWidgetItem *treeItem)
{
    new QTreeWidgetItem(treeItem, QStringList(name));
    qRegisterMetaType<T *>(name.toUtf8().constData());
}
