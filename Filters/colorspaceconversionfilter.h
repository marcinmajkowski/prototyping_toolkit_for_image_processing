#ifndef COLORSPACECONVERSIONFILTER_H
#define COLORSPACECONVERSIONFILTER_H

#include "filter.h"

class ColorSpaceConversionFilter : public Filter
{
    Q_OBJECT
public:
    explicit ColorSpaceConversionFilter(QObject *parent = 0);

    QStringList codeSnippet() const Q_DECL_OVERRIDE;
    cv::Mat &process(cv::Mat &input) const Q_DECL_OVERRIDE;

signals:

public slots:

};

#endif // COLORSPACECONVERSIONFILTER_H
