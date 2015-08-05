#ifndef FILTERSWIDGET_H
#define FILTERSWIDGET_H

#include <QTreeWidget>

class FiltersWidget : public QTreeWidget
{
    Q_OBJECT
public:
    explicit FiltersWidget(QWidget *parent = 0);

signals:

public slots:

private:
    template <class T>
    void appendFilter(QString name, QTreeWidgetItem *treeItem);

};

#endif // FILTERSWIDGET_H
