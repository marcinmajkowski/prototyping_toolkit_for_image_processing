#ifndef ABSOLUTEDIFFERENCEFILTER_H
#define ABSOLUTEDIFFERENCEFILTER_H

#include <opencv2/core/core.hpp>

#include "binaryoperationfilter.h"

class AbsoluteDifferenceFilter : public BinaryOperationFilter
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit AbsoluteDifferenceFilter(FilterObserver *observer = 0,
                                                  QObject *parent = 0);

    static QString filterName;

    QString binaryOperationName() const;
    void binaryOperation(cv::Mat &input,
                         cv::Mat &secondInput);
};

Q_DECLARE_METATYPE(AbsoluteDifferenceFilter *)

#endif // ABSOLUTEDIFFERENCEFILTER_H
