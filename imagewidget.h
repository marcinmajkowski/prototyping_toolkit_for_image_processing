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

    void setFitToWindow(bool fitToWindow);
    bool fitToWindow() const;

    void setScaleFactor(double newScaleFactor);
    double scaleFactor() const;

public slots:
    void setPixmap(const QPixmap &pixmap);
    void setMat(const cv::Mat);

private:
    void adjustScrollBar(QScrollBar *scrollBar, double factor);

    QLabel *imageLabel;
    double m_scaleFactor;
    bool m_fitToWindow;
};

#endif // IMAGEWIDGET_H
