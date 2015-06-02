#ifndef IMAGEWIDGET_H
#define IMAGEWIDGET_H

#include <QScrollArea>

class QLabel;
class QString;

class ImageWidget : public QScrollArea
{
    Q_OBJECT
public:
    explicit ImageWidget(QWidget *parent = 0);

/* loadFile() is a member of ImageWidget class since this widget
 * knows the best what files it can handle. */
    bool loadFile(const QString &filename);

signals:

public slots:
    void zoomIn();
    void zoomOut();
    void normalSize();
    void fitToWindow();

private:
    void scaleImage(double factor);
    void adjustScrollBar(QScrollBar *scrollBar, double factor);

    QLabel *imageLabel;
    double scaleFactor;
};

#endif // IMAGEWIDGET_H
