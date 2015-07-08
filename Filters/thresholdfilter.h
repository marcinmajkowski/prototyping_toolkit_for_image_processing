#ifndef THRESHOLDFILTER_H
#define THRESHOLDFILTER_H

#include <QMap>

#include "filter.h"

class ThresholdFilter : public Filter
{
    Q_OBJECT
public:
    explicit ThresholdFilter(FilterObserver *observer = 0, QObject *parent = 0);
    QStringList codeSnippet() const Q_DECL_OVERRIDE;
    QDialog *createDialog(QWidget *parent = 0) Q_DECL_OVERRIDE;
    cv::Mat &process(cv::Mat &input) const Q_DECL_OVERRIDE;

public slots:
    void setThreshold(int threshold);
    void setMaxValue(int maxValue);
    void setType(const QString &type);

private:
    double m_threshold;
    double m_maxValue;
    int m_type;
    QMap<int, QString> m_typeMap;
};

#endif // THRESHOLDFILTER_H
