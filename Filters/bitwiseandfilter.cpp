#include <QDebug>
#include <QtWidgets>

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "bitwiseandfilter.h"

BitwiseAndFilter::BitwiseAndFilter(FilterObserver *observer,
                                   QObject *parent) :
    BinaryOperationFilter(filterName, observer, parent)
{
}

QString BitwiseAndFilter::binaryOperationName() const
{
    return "bitwise_and";
}

void BitwiseAndFilter::binaryOperation(cv::Mat &input, cv::Mat &secondInput)
{
    cv::bitwise_and(input, secondInput, input);
}

QString BitwiseAndFilter::filterName = "Bitwise and";
