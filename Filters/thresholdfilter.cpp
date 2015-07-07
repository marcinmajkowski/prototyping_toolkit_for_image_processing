#include <QDebug>
#include <QtWidgets>

#include <opencv2/imgproc/imgproc.hpp>

#include "thresholdfilter.h"

ThresholdFilter::ThresholdFilter(FilterObserver *observer, QObject *parent) :
    Filter("Threshold", observer, parent),
    m_threshold(127),
    m_maxValue(255),
    m_type(CV_THRESH_BINARY)
{
}

QStringList ThresholdFilter::codeSnippet() const
{
    //TODO
    QStringList snippet;

    snippet << "threshold();";

    return snippet;
}

QDialog *ThresholdFilter::createDialog(QWidget *parent)
{
    //TODO
    QDialog *dialog = new QDialog(parent);

    return dialog;
}

cv::Mat &ThresholdFilter::process(cv::Mat &input) const
{
    switch (input.type()) {
    case CV_8UC4:
    case CV_8UC3:
        // adaptiveThreshold requires 8-bit single-channel input
        cv::cvtColor(input, input, CV_RGB2GRAY);
    case CV_8UC1:
        cv::threshold(input, input, m_threshold, m_maxValue, m_type);
        break;
    }

    return input;
}

void ThresholdFilter::setThreshold(int threshold)
{

}

void ThresholdFilter::setMaxValue(int maxValue)
{

}

void ThresholdFilter::setType(const QString &type)
{

}
