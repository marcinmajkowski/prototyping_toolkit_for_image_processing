#ifndef IMAGEWIDGET_H
#define IMAGEWIDGET_H

#include <QScrollArea>
#include <opencv2/core/core.hpp>

class QLabel;
class QString;

class ImageWidget : public QScrollArea
{
    Q_OBJECT
public:
    explicit ImageWidget(QWidget *parent = 0);

/* loadFile() is a member of ImageWidget class since this widget
 * knows the best what files it can handle. */
    //TODO it was stupid since it can handle QImage/QPixmap
    //TODO move it out from here
    bool loadFile(const QString &fileName);

    void setFitToWindow(bool fitToWindow);
    bool fitToWindow() const;

    void setScaleFactor(double scaleFactor);
    double scaleFactor() const;

public slots:
    void setPixmap(const QPixmap &);
    void setMat(const cv::Mat);

private:
    void adjustScrollBar(QScrollBar *scrollBar, double factor);

    QLabel *imageLabel;
    double m_scaleFactor;
    bool m_fitToWindow;
};

#endif // IMAGEWIDGET_H
