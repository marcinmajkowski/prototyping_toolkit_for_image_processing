#ifndef ADAPTIVETHRESHOLDFILTER_H
#define ADAPTIVETHRESHOLDFILTER_H

#include "filter.h"

class AdaptiveThresholdFilter : public Filter
{
    Q_OBJECT
public:
    explicit AdaptiveThresholdFilter(FilterObserver *observer = 0, QObject *parent = 0);
    QStringList codeSnippet() const Q_DECL_OVERRIDE;
    QDialog *createDialog(QWidget *parent = 0) Q_DECL_OVERRIDE;
    cv::Mat &process(cv::Mat &input) const Q_DECL_OVERRIDE;

public slots:
    void setMaxValue(int maxValue);
    void setAdaptiveMethod(int);
    void setThresholdType(int);
    void setBlockSize(int);
    void setC(double);

private:
    double m_maxValue;
    int m_adaptiveMethod;
    int m_thresholdType;
    int m_blockSize;
    double m_C;
};

#endif // ADAPTIVETHRESHOLDFILTER_H
