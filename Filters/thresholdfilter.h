#ifndef THRESHOLDFILTER_H
#define THRESHOLDFILTER_H

#include <QMap>

#include "filter.h"

class ThresholdFilter : public Filter
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit ThresholdFilter(FilterObserver *observer = 0, QObject *parent = 0);
    QStringList codeSnippet() const Q_DECL_OVERRIDE;
    cv::Mat &process(cv::Mat &input) Q_DECL_OVERRIDE;

public slots:
    void setThreshold(int threshold);
    void setMaxValue(int maxValue);
    void setType(const QString &type);

protected:
    QLayout *dialogParametersGroupLayout() Q_DECL_OVERRIDE;
    QLabel *dialogDescriptionLabel() Q_DECL_OVERRIDE;

private:
    double m_threshold;
    double m_maxValue;
    int m_type;
    QMap<int, QString> m_typeMap;
};

Q_DECLARE_METATYPE(ThresholdFilter *)

#endif // THRESHOLDFILTER_H
