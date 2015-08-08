#ifndef BITWISEANDFILTER_H
#define BITWISEANDFILTER_H

#include <opencv2/core/core.hpp>

#include "binaryoperationfilter.h"

class BitwiseAndFilter : public BinaryOperationFilter
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit BitwiseAndFilter(FilterObserver *observer = 0,
                                          QObject *parent = 0);

    static QString filterName;

    QString binaryOperationName() const;
    void binaryOperation(cv::Mat &input,
                         cv::Mat &secondInput);
};

Q_DECLARE_METATYPE(BitwiseAndFilter *)

#endif // BITWISEANDFILTER_H
