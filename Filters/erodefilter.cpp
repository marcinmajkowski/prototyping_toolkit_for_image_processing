#include <QDebug>
#include <QtWidgets>

#include <opencv2/imgproc/imgproc.hpp>

#include "erodefilter.h"

ErodeFilter::ErodeFilter(FilterObserver *observer, QObject *parent) :
    Filter("Dilate", observer, parent),
    m_kernel(cv::Mat()),
    m_anchor(cv::Point(-1, - 1)),
    m_iterations(1),
    m_borderType(cv::BORDER_CONSTANT),
    m_borderValue(cv::morphologyDefaultBorderValue())
{
}

cv::Mat &ErodeFilter::process(cv::Mat &input) const
{
    cv::erode(input, input, m_kernel, m_anchor, m_iterations, m_borderType, m_borderValue);

    return input;
}