#ifndef COLORSPACECONVERSIONFILTER_H
#define COLORSPACECONVERSIONFILTER_H

#include "filter.h"

class ColorSpaceConversionFilter : public Filter
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit ColorSpaceConversionFilter(FilterObserver *filterObserver = 0, QObject *parent = 0);

    QStringList codeSnippet() const Q_DECL_OVERRIDE;
    cv::Mat &process(cv::Mat &input) Q_DECL_OVERRIDE;

signals:

public slots:

};

Q_DECLARE_METATYPE(ColorSpaceConversionFilter *)

#endif // COLORSPACECONVERSIONFILTER_H
