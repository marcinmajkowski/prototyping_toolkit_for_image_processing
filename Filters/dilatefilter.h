#ifndef DILATEFILTER_H
#define DILATEFILTER_H

#include "filter.h"

class DilateFilter : public Filter
{
    Q_OBJECT
public:
    explicit DilateFilter(FilterObserver *observer = 0, QObject *parent = 0);
    cv::Mat &process(cv::Mat &input) const Q_DECL_OVERRIDE;

public slots:

private:
    cv::Mat m_kernel;
    cv::Point m_anchor;
    int m_iterations;
    int m_borderType;
    cv::Scalar m_borderValue;
};

#endif // DILATEFILTER_H
