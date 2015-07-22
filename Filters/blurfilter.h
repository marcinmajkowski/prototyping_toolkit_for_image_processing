#ifndef BLURFILTER_H
#define BLURFILTER_H

#include <QMap>

#include "filter.h"

class BlurFilter : public Filter
{
    Q_OBJECT
public:
    explicit BlurFilter(FilterObserver *observer = 0, QObject *parent = 0);
    QStringList codeSnippet() const Q_DECL_OVERRIDE;
    QDialog *createDialog(QWidget *parent = 0) Q_DECL_OVERRIDE;
    cv::Mat &process(cv::Mat &input) Q_DECL_OVERRIDE;

public slots:
    void setBorderType(const QString &type);

private:
    cv::Size m_size;
    cv::Point m_anchor;
    int m_borderType;
    QMap<int, QString> m_borderTypeMap;
};

#endif // BLURFILTER_H
