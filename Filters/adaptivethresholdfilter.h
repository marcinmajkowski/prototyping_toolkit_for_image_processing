#ifndef ADAPTIVETHRESHOLDFILTER_H
#define ADAPTIVETHRESHOLDFILTER_H

#include <QMap>

#include "filter.h"

class AdaptiveThresholdFilter : public Filter
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit AdaptiveThresholdFilter(FilterObserver *observer = 0,
                                                 QObject *parent = 0);
    QStringList codeSnippet() const Q_DECL_OVERRIDE;
    cv::Mat &process(cv::Mat &input) Q_DECL_OVERRIDE;

    void read(QDataStream &data) Q_DECL_OVERRIDE;
    void write(QDataStream &data) const Q_DECL_OVERRIDE;

    static QString filterName;

public slots:
    void setMaxValue(int maxValue);
    void setAdaptiveMethod(const QString &adaptiveMethod);
    void setThresholdType(const QString &thresholdType);
    void setBlockSize(int blockSize);
    void setC(double c);

protected:
    QLayout *dialogParametersGroupLayout() Q_DECL_OVERRIDE;
    QLabel *dialogDescriptionLabel() Q_DECL_OVERRIDE;

private:
    double m_maxValue;
    int m_adaptiveMethod;
    int m_thresholdType;
    int m_blockSize;
    double m_C;

    bool m_convertInput;

    QMap<int, QString> m_adaptiveMethodMap;
    QMap<int, QString> m_thresholdTypeMap;
};

Q_DECLARE_METATYPE(AdaptiveThresholdFilter *)

#endif // ADAPTIVETHRESHOLDFILTER_H
