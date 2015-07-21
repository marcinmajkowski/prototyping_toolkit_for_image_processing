#ifndef COLORSPACECONVERSIONFILTER_H
#define COLORSPACECONVERSIONFILTER_H

#include "filter.h"

class ColorSpaceConversionFilter : public Filter
{
    Q_OBJECT
public:
    explicit ColorSpaceConversionFilter(FilterObserver *filterObserver = 0, QObject *parent = 0);

    QStringList codeSnippet() const Q_DECL_OVERRIDE;
    cv::Mat &process(cv::Mat &input) Q_DECL_OVERRIDE;

signals:

public slots:

};

#endif // COLORSPACECONVERSIONFILTER_H
