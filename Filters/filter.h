#ifndef FILTER_H
#define FILTER_H

#include <opencv2/core/core.hpp>

class QWidget;
class QString;

class Filter
{
public:
    Filter();
    virtual ~Filter();

    QWidget *getWidget();
    QString getSignature();
    QString getName();
    cv::Mat process(cv::Mat);
};

#endif // FILTER_H
