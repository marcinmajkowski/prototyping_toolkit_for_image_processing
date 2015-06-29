#ifndef COLORSPACECONVERSIONFILTER_H
#define COLORSPACECONVERSIONFILTER_H

#include "filter.h"

class ColorSpaceConversionFilter : public Filter
{
    Q_OBJECT
public:
    explicit ColorSpaceConversionFilter(QObject *parent = 0);

    QString codeSnippet() const Q_DECL_OVERRIDE;

signals:

public slots:

protected:
    void process() Q_DECL_OVERRIDE;
};

#endif // COLORSPACECONVERSIONFILTER_H
