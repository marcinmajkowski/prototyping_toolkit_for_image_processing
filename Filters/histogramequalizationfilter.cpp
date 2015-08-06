#include <QtWidgets>

#include <opencv2/imgproc/imgproc.hpp>

#include "histogramequalizationfilter.h"

HistogramEqualizationFilter::HistogramEqualizationFilter(FilterObserver *observer, QObject *parent) :
    Filter(filterName, observer, parent),
    m_convertInput(false)
{
}

QString HistogramEqualizationFilter::filterName = "Histogram equalization";

QStringList HistogramEqualizationFilter::codeSnippet() const
{
    QStringList snippet;

    // extra line with conversion when input has inappropriate type
    if (m_convertInput) {
        QString line = "cv::cvtColor(img, img, CV_RGB2GRAY);";
        snippet << line;
    }

    snippet << "cv::equalizeHist(img, img);";

    return snippet;
}

cv::Mat &HistogramEqualizationFilter::process(cv::Mat &input)
{
    if (input.type() != CV_8UC1) {
        // adaptiveThreshold requires 8-bit single-channel input
        cv::cvtColor(input, input, CV_RGB2GRAY);
        m_convertInput = true;
    } else {
        m_convertInput = false;
    }

    cv::equalizeHist(input, input);

    return input;
}

QLabel *HistogramEqualizationFilter::dialogDescriptionLabel()
{
    QLabel *label = new QLabel;
    label->setText("This filter equalizes the histogram of a "
                   "grayscale image.");
    label->setWordWrap(true);

    return label;
}
