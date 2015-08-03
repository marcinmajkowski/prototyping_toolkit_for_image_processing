#ifndef DILATEFILTER_H
#define DILATEFILTER_H

#include <QMap>

#include "filter.h"

class DilateFilter : public Filter
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit DilateFilter(FilterObserver *observer = 0, QObject *parent = 0);
    QStringList codeSnippet() const Q_DECL_OVERRIDE;
    cv::Mat &process(cv::Mat &input) Q_DECL_OVERRIDE;

    virtual void read(QDataStream &data);
    virtual void write(QDataStream &data) const;

public slots:
    void setKernelShape(const QString &borderType);
    void setKernelSizeWidth(int kernelSizeWidth);
    void setKernelSizeHeight(int kernelSizeHeight);
    void setBorderType(const QString &borderType);
    void setIterations(int iterations);

protected:
    QLayout *dialogParametersGroupLayout() Q_DECL_OVERRIDE;
    QLabel *dialogDescriptionLabel() Q_DECL_OVERRIDE;

private:
    int m_kernelShape;
    QMap<int, QString> m_kernelShapeMap;
    int m_kernelSizeWidth;
    int m_kernelSizeHeight;
    cv::Point m_kernelAnchor;
    cv::Point m_anchor;
    int m_iterations;
    int m_borderType;
    cv::Scalar m_borderValue;
    QMap<int, QString> m_borderTypeMap;
};

Q_DECLARE_METATYPE(DilateFilter *)

#endif // DILATEFILTER_H
