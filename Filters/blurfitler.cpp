#include <QDebug>
#include <QtWidgets>

#include <opencv2/imgproc/imgproc.hpp>

#include "blurfilter.h"

BlurFilter::BlurFilter(FilterObserver *observer, QObject *parent) :
    Filter("Blur", observer, parent),
    m_size(cv::Size(5, 5)),
    m_anchor(cv::Point(-1, -1)),
    m_borderType(cv::BORDER_DEFAULT)
{
    m_borderTypeMap.insert(cv::BORDER_CONSTANT, "cv::BORDER_CONSTANT");
    m_borderTypeMap.insert(cv::BORDER_DEFAULT, "cv::BORDER_DEFAULT");
    m_borderTypeMap.insert(cv::BORDER_REFLECT, "cv::BORDER_REFLECT");
    m_borderTypeMap.insert(cv::BORDER_REFLECT_101, "cv::BORDER_REFLECT_101");
    m_borderTypeMap.insert(cv::BORDER_REPLICATE, "cv::BORDER_REPLICATE");
    m_borderTypeMap.insert(cv::BORDER_WRAP, "cv::BORDER_WRAP"); // cv::exception
}

QStringList BlurFilter::codeSnippet() const
{
    //TODO
    return Filter::codeSnippet();
}

QDialog *BlurFilter::createDialog(QWidget *parent)
{
    //TODO
    return Filter::createDialog(parent);
}

cv::Mat &BlurFilter::process(cv::Mat &input)
{
    //TODO
    return Filter::process(input);
}

void BlurFilter::setBorderType(const QString &type)
{
    //TODO
}
