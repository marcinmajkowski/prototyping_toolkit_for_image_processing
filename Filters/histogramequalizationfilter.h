#ifndef EQUALIZEHISTOGRAMFILTER_H
#define EQUALIZEHISTOGRAMFILTER_H

#include "filter.h"

class HistogramEqualizationFilter : public Filter
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit HistogramEqualizationFilter(
            FilterObserver *observer = 0, QObject *parent = 0);
    QStringList codeSnippet() const Q_DECL_OVERRIDE;
    cv::Mat &process(cv::Mat &input) Q_DECL_OVERRIDE;

    static QString filterName;

protected:
    QLabel *dialogDescriptionLabel() Q_DECL_OVERRIDE;

private:
    bool m_convertInput;
};

#endif // EQUALIZEHISTOGRAMFILTER_H
