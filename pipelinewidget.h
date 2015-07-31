#ifndef PIPELINEWIDGET_H
#define PIPELINEWIDGET_H

#include <QListWidget>
#include <opencv2/core/core.hpp>

class QTreeWidgetItem;
class FilterFactory;
class FilterObserver;
class Filter;

class PipelineWidget : public QListWidget
{
    Q_OBJECT
public:
    explicit PipelineWidget(QWidget *parent = 0);

    QPixmap inputImage();
    QPixmap outputImage();
    QByteArray content();

signals:
    void sourceCodeChanged(const QString &sourceCode);
    void outputPixmapChanged(const QPixmap &pixmap);
    void inputPixmapChanged(const QPixmap &pixmap);

public slots:
    void appendItem(QTreeWidgetItem *item);
    void setInputPixmap(const QPixmap &pixmap);
    void setContent(const QByteArray &data);

protected slots:
    void deleteSelectedItems();
    void updateSourceCode();
    void updateOutputPixmap();

protected:
    bool dropMimeData(int index, const QMimeData *data, Qt::DropAction action) Q_DECL_OVERRIDE;
    FilterFactory *m_filterFactory;
    FilterObserver *m_filterObserver;
    cv::Mat m_inputImage;
    cv::Mat m_outputImage;
};

#endif // PIPELINEWIDGET_H
