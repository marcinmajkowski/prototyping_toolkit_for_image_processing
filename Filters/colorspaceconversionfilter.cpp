#include <opencv2/imgproc/imgproc.hpp>

#include "colorspaceconversionfilter.h"

ColorSpaceConversionFilter::ColorSpaceConversionFilter(FilterObserver *observer, QObject *parent):
    Filter("Color space conversion", observer, parent)
{
}

QStringList ColorSpaceConversionFilter::codeSnippet() const
{
    //TODO
    QStringList snippet;
    snippet << "cv::cvtColor(img, img, CV_RGB2GRAY);";
    return snippet;
}

cv::Mat &ColorSpaceConversionFilter::process(cv::Mat &input)
{
    //TODO checking m_input format etc.
    switch (input.type()) {
    case CV_8UC4:
    case CV_8UC3:
        cv::cvtColor(input, input, CV_RGB2GRAY);
        break;
    case CV_8UC1:
        break;
    }

    return input;
}
