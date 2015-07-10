#ifndef ERODEFILTER_H
#define ERODEFILTER_H

#include "filter.h"

class ErodeFilter : public Filter
{
    Q_OBJECT
public:
    explicit ErodeFilter(FilterObserver *observer = 0, QObject *parent = 0);
    cv::Mat &process(cv::Mat &input) const Q_DECL_OVERRIDE;

public slots:

private:
    cv::Mat m_kernel;
    cv::Point m_anchor;
    int m_iterations;
    int m_borderType;
    cv::Scalar m_borderValue;
};

#endif // ERODEFILTER_H
