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

protected:
    QStringList mimeTypes() const Q_DECL_OVERRIDE;
    QMimeData *mimeData(const QList<QTreeWidgetItem *> items) const Q_DECL_OVERRIDE;
};

#endif // FILTERSWIDGET_H
