#include <QDebug>
#include <QtWidgets>

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "absolutedifferencefilter.h"

AbsoluteDifferenceFilter::AbsoluteDifferenceFilter(FilterObserver *observer,
                                                   QObject *parent) :
    BinaryOperationFilter(filterName, observer, parent)
{
}

QString AbsoluteDifferenceFilter::binaryOperationName() const
{
    return "absdiff";
}

void AbsoluteDifferenceFilter::binaryOperation(cv::Mat &input, cv::Mat &secondInput)
{
    cv::absdiff(input, secondInput, input);
}

QString AbsoluteDifferenceFilter::filterName = "Absolute difference";
