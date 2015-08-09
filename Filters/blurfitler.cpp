#include <QDebug>
#include <QtWidgets>

#include <opencv2/imgproc/imgproc.hpp>

#include "blurfilter.h"

BlurFilter::BlurFilter(FilterObserver *observer, QObject *parent) :
    Filter(filterName, observer, parent),
    m_ksize(cv::Size(5, 5)),
    m_anchor(cv::Point(-1, -1)),
    m_borderType(cv::BORDER_DEFAULT)
{
    m_borderTypeMap.insert(cv::BORDER_CONSTANT, "cv::BORDER_CONSTANT");
    m_borderTypeMap.insert(cv::BORDER_DEFAULT, "cv::BORDER_DEFAULT");
    m_borderTypeMap.insert(cv::BORDER_REFLECT, "cv::BORDER_REFLECT");
    m_borderTypeMap.insert(cv::BORDER_REFLECT_101, "cv::BORDER_REFLECT_101");
    m_borderTypeMap.insert(cv::BORDER_REPLICATE, "cv::BORDER_REPLICATE");

    // might trow cv::exception
    m_borderTypeMap.insert(cv::BORDER_WRAP, "cv::BORDER_WRAP");
}

QString BlurFilter::filterName = "Blur";

cv::Mat &BlurFilter::process(cv::Mat &input)
{
    cv::blur(input, input, m_ksize, m_anchor, m_borderType);

    return input;
}

QStringList BlurFilter::codeSnippet() const
{
    QStringList snippet;
    QString line = QString("cv::blur(img, img, %1, %2, %3);")
            .arg("cv::Size(5, 5)")
            .arg("cv::Point(-1, -1)")
            .arg(m_borderTypeMap[m_borderType]);
    snippet << line;
    return snippet;
}
