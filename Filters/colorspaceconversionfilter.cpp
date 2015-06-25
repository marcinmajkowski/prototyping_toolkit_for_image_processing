#include <opencv2/imgproc/imgproc.hpp>

#include "colorspaceconversionfilter.h"

ColorSpaceConversionFilter::ColorSpaceConversionFilter(QObject *parent) :
    Filter("Color space conversion", parent)
{
}

void ColorSpaceConversionFilter::process()
{
    //TODO checking m_input format etc.
    cv::cvtColor(m_input, m_result, CV_RGB2GRAY);

    //TODO move out
    setStatus(Ready);
    emit resultChanged(m_result);
}
