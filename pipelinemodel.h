#ifndef PIPELINEMODEL_H
#define PIPELINEMODEL_H

#include <QAbstractListModel>

class PipelineModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit PipelineModel(QObject *parent = 0);

    int rowCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;

signals:

public slots:

};

#endif // PIPELINEMODEL_H
