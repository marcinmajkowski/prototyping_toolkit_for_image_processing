#include <QDebug>
#include <QMimeData>
#include <QShortcut>
#include <QTreeWidgetItem>

#include "pipelinewidget.h"
#include "pipelinewidgetitem.h"
#include "Filters/filterobserver.h"
#include "Filters/filter.h"
#include "asmOpenCV.h"

PipelineWidget::PipelineWidget(QWidget *parent) :
    QListWidget(parent),
    m_filterObserver(new FilterObserver(this))
{
    setDropIndicatorShown(true);
    setDragDropMode(QAbstractItemView::DragDrop);
    setDefaultDropAction(Qt::MoveAction);

    setSelectionMode(QAbstractItemView::ExtendedSelection);

    QShortcut* shortcut = new QShortcut(QKeySequence(Qt::Key_Delete), this);
    connect(shortcut, SIGNAL(activated()), this, SLOT(deleteSelectedItems()));

    connect(model(), SIGNAL(rowsRemoved(QModelIndex,int,int)),
            this, SLOT(updateOutputPixmap()));
    connect(model(), SIGNAL(rowsInserted(QModelIndex,int,int)),
            this, SLOT(updateOutputPixmap()));
    connect(model(), SIGNAL(rowsMoved(QModelIndex,int,int,QModelIndex,int)),
            this, SLOT(updateOutputPixmap()));
    connect(model(), SIGNAL(dataChanged(QModelIndex,QModelIndex)),
            this, SLOT(updateOutputPixmap()));
    connect(model(), SIGNAL(modelReset()),
            this, SLOT(updateOutputPixmap()));
    connect(m_filterObserver, SIGNAL(updated()),
            this, SLOT(updateOutputPixmap()));
}

QPixmap PipelineWidget::inputImage()
{
    return ASM::cvMatToQPixmap(m_inputImage);
}

QPixmap PipelineWidget::outputImage()
{
    return ASM::cvMatToQPixmap(m_outputImage);
}

QByteArray PipelineWidget::content()
{
    QByteArray data;
    QDataStream dataStream(&data, QIODevice::WriteOnly);

    for (int i = 0; i < count(); ++i) {
        QListWidgetItem *widgetItem = item(i);
        Filter *f = widgetItem->data(PipelineWidgetItem::FilterRole).value<Filter *>();

        // store filter name
        dataStream << f->name();

        // store filter parameters
        f->write(dataStream);

        // store item state (checked/unchecked)
        dataStream << (widgetItem->checkState() == Qt::Checked);
    }

    return data;
}

void PipelineWidget::appendItem(QTreeWidgetItem *treeItem)
{
    if (treeItem->childCount() != 0) {
        return;
    }

    QString filterName = treeItem->text(0);
    Filter *filter = createFilter(filterName);
    if (filter) {
        QListWidgetItem *item = new PipelineWidgetItem(filterName);
        QVariant var;
        var.setValue(filter);
        item->setData(PipelineWidgetItem::FilterRole, var);
        addItem(item);
    }
}

void PipelineWidget::setInputPixmap(const QPixmap &pixmap)
{
    m_inputImage =  ASM::QPixmapToCvMat(pixmap);
    emit inputPixmapChanged(pixmap);
    updateOutputPixmap();
}

void PipelineWidget::setContent(const QByteArray &data)
{
    clear();

    QByteArray dataCopy(data);
    QDataStream dataStream(&dataCopy, QIODevice::ReadOnly);

    while (!dataStream.atEnd()) {
        QString filterName;

        // read filter name
        dataStream >> filterName;

        Filter *filter = createFilter(filterName);

        // read filter parameters
        filter->read(dataStream);

        bool checkState;

        // read check state
        dataStream >> checkState;

        QListWidgetItem *item = new PipelineWidgetItem(filterName);
        item->setCheckState(checkState ? Qt::Checked : Qt::Unchecked);

        QVariant var;
        var.setValue(filter);
        item->setData(PipelineWidgetItem::FilterRole, var);
        addItem(item);
    }
}

void PipelineWidget::deleteSelectedItems()
{
    qDeleteAll(selectedItems());
}

void PipelineWidget::updateSourceCode()
{
    QStringList sourceCode;

    for (int i = 0; i < count(); ++i) {
        QListWidgetItem *widgetItem = item(i);
        Filter *f = widgetItem->data(PipelineWidgetItem::FilterRole).value<Filter *>();
        if (f) {
            QStringList snippet = f->codeSnippet();
            if (widgetItem->checkState() == Qt::Unchecked) {
                // comment every line if unchecked
                for (QStringList::iterator it = snippet.begin(); it != snippet.end(); ++it) {
                    // only if it isn't already a comment
                    if (!it->startsWith("//")) {
                        it->prepend("// ");
                    }
                }
            }
            sourceCode << snippet;
        }
    }

    emit sourceCodeChanged(sourceCode.join("\n"));
}

void PipelineWidget::updateOutputPixmap()
{
    m_outputImage = m_inputImage.clone();

    for (int i = 0; i < count(); ++i) {
        QListWidgetItem *widgetItem = item(i);
        if (widgetItem->checkState() == Qt::Checked) {
            Filter *f = widgetItem->data(PipelineWidgetItem::FilterRole).value<Filter *>();
            if (f) {
                m_outputImage = f->process(m_outputImage);
            }
        }
    }

    updateSourceCode();

    emit outputPixmapChanged(ASM::cvMatToQPixmap(m_outputImage));
}

bool PipelineWidget::dropMimeData(int index, const QMimeData *data, Qt::DropAction action)
{
    Q_UNUSED(action);

    //TODO tests for correctness
    QByteArray encoded = data->data(data->formats().at(0));
    QDataStream stream(&encoded, QIODevice::ReadOnly);

    int row, col;
    QMap<int, QVariant> roleDataMap;
    stream >> row >> col >> roleDataMap;
    QString filterName = roleDataMap.first().toString();

    Filter *filter = createFilter(filterName);

    if (!filter) {
        return false;
    }

    QListWidgetItem *item = new PipelineWidgetItem(filterName);
    QVariant var;
    var.setValue(filter);
    item->setData(PipelineWidgetItem::FilterRole, var);
    insertItem(index, item);

    return true;
    //TODO preserve default behaviour
    //    return QListWidget::dropMimeData(index, data, action);
}

Filter *PipelineWidget::createFilter(const QString &type, QObject *parent)
{
    Filter *filter = nullptr;

    int filterType = QMetaType::type(type.toUtf8().constData());
    if (filterType != QMetaType::UnknownType) {
        const QMetaObject *metaObject = QMetaType::metaObjectForType(filterType);
        QObject *object = metaObject->newInstance(
                    Q_ARG(FilterObserver *, m_filterObserver), Q_ARG(QObject *, parent));
        filter = dynamic_cast<Filter *>(object);
    }

    if (filter == nullptr) {
        qDebug() << "PipelineWidget::createFilter(): not known filter type" << type;
    }

    return filter;
}
