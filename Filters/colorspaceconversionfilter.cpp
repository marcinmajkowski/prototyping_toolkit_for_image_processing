#include <opencv2/imgproc/imgproc.hpp>
#include <QLabel>

#include "colorspaceconversionfilter.h"

ColorSpaceConversionFilter::ColorSpaceConversionFilter(FilterObserver *observer, QObject *parent):
    Filter(filterName, observer, parent)
{
}

QString ColorSpaceConversionFilter::filterName = "Color space conversion";

QStringList ColorSpaceConversionFilter::codeSnippet() const
{
    QStringList snippet;
    snippet << "cv::cvtColor(img, img, CV_RGB2GRAY);";
    return snippet;
}

cv::Mat &ColorSpaceConversionFilter::process(cv::Mat &input)
{
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

QLabel *ColorSpaceConversionFilter::dialogDescriptionLabel()
{
    QLabel *label = new QLabel;
    label->setText("This filter converts 3 and 4-channel images to "
                   "1-channel image using cv::cvtColor() function.");
    label->setWordWrap(true);

    return label;
}
