#include <opencv2/imgproc/imgproc.hpp>

#include "colorspaceconversionfilter.h"

ColorSpaceConversionFilter::ColorSpaceConversionFilter(QObject *parent) :
    Filter("Color space conversion", parent)
{
}

QString ColorSpaceConversionFilter::codeSnippet() const
{
    return "cv::cvtColor(src, dst, CV_RGB2GRAY);";
}

cv::Mat &ColorSpaceConversionFilter::process(cv::Mat &input) const
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
