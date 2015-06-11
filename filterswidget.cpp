#include "filterswidget.h"

#include <QHeaderView>

FiltersWidget::FiltersWidget(QWidget *parent) :
    QTreeWidget(parent)
{
    // remove header
    header()->close();
}
