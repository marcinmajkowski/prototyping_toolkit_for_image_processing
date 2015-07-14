#include <QDebug>
#include <QtWidgets>

#include <opencv2/imgproc/imgproc.hpp>

#include "dilatefilter.h"

DilateFilter::DilateFilter(FilterObserver *observer, QObject *parent) :
    Filter("Dilate", observer, parent),
    m_kernel(cv::Mat()),
    m_anchor(cv::Point(-1, -1)),
    m_iterations(1),
    m_borderType(cv::BORDER_CONSTANT),
    m_borderValue(cv::morphologyDefaultBorderValue())
{
    m_borderTypeMap.insert(cv::BORDER_CONSTANT, "cv::BORDER_CONSTANT");
    m_borderTypeMap.insert(cv::BORDER_DEFAULT, "cv::BORDER_DEFAULT");
    m_borderTypeMap.insert(cv::BORDER_REFLECT, "cv::BORDER_REFLECT");
    m_borderTypeMap.insert(cv::BORDER_REFLECT_101, "cv::BORDER_REFLECT_101");
    m_borderTypeMap.insert(cv::BORDER_REPLICATE, "cv::BORDER_REPLICATE");
    m_borderTypeMap.insert(cv::BORDER_WRAP, "cv::BORDER_WRAP");
}

QStringList DilateFilter::codeSnippet() const
{
    //TODO
    QString kernel = "cv::Mat()";
    QString anchor = "cv::Point(-1, -1)";
    QString borderValue = "cv::morphologyDefaultBorderValue()";

    QStringList snippet;

    QString line = QString("cv::%1(%2, %3, %4, %5, %6, %7, %8);")
            .arg("dilate")
            .arg("img")
            .arg("img")
            .arg(kernel)
            .arg(anchor)
            .arg(m_iterations)
            .arg(m_borderTypeMap[m_borderType])
            .arg(borderValue);

    snippet << line;

    return snippet;
}

QDialog *DilateFilter::createDialog(QWidget *parent)
{
    return new QDialog(parent);
}

cv::Mat &DilateFilter::process(cv::Mat &input) const
{
    cv::dilate(input, input, m_kernel, m_anchor, m_iterations, m_borderType, m_borderValue);

    return input;
}
