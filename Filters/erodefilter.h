#ifndef ERODEFILTER_H
#define ERODEFILTER_H

#include <QMap>

#include "filter.h"

class ErodeFilter : public Filter
{
    Q_OBJECT
public:
    explicit ErodeFilter(FilterObserver *observer = 0, QObject *parent = 0);
    QStringList codeSnippet() const Q_DECL_OVERRIDE;
    QDialog *createDialog(QWidget *parent = 0) Q_DECL_OVERRIDE;
    cv::Mat &process(cv::Mat &input) const Q_DECL_OVERRIDE;

public slots:

private:
    cv::Mat m_kernel;
    cv::Point m_anchor;
    int m_iterations;
    int m_borderType;
    cv::Scalar m_borderValue;
    QMap<int, QString> m_borderTypeMap;
};

#endif // ERODEFILTER_H
