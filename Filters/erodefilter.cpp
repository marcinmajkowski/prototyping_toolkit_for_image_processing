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

QStringList ErodeFilter::codeSnippet() const
{
    //TODO
    QString kernel = "cv::Mat()";
    QString anchor = "cv::Point(-1, -1)";
    QString borderValue = "cv::morphologyDefaultBorderValue()";

    QStringList snippet;

    QString line = QString("cv::%1(%2, %3, %4, %5, %6, %7, %8);")
            .arg("erode")
            .arg("img")
            .arg("img")
            .arg(kernel)
            .arg(anchor)
            .arg(m_iterations)
            .arg("enum") //TODO
            .arg(borderValue);

    snippet << line;

    return snippet;
}

QDialog *ErodeFilter::createDialog(QWidget *parent)
{
    return new QDialog(parent);
}

cv::Mat &ErodeFilter::process(cv::Mat &input) const
{
    cv::erode(input, input, m_kernel, m_anchor, m_iterations, m_borderType, m_borderValue);

    return input;
}
