#ifndef ADAPTIVETHRESHOLDFILTER_H
#define ADAPTIVETHRESHOLDFILTER_H

#include "filter.h"

class AdaptiveThresholdFilter : public Filter
{
    Q_OBJECT
public:
    explicit AdaptiveThresholdFilter(QObject *parent = 0);
    ~AdaptiveThresholdFilter();

public slots:
    void setMaxValue(double);
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

    QDialog *createDialog();
};

#endif // ADAPTIVETHRESHOLDFILTER_H
