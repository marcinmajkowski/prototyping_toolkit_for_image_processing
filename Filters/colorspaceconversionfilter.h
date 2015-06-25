#ifndef COLORSPACECONVERSIONFILTER_H
#define COLORSPACECONVERSIONFILTER_H

#include "filter.h"

class ColorSpaceConversionFilter : public Filter
{
    Q_OBJECT
public:
    explicit ColorSpaceConversionFilter(QObject *parent = 0);

signals:

public slots:

protected:
    void process();
};

#endif // COLORSPACECONVERSIONFILTER_H
