#ifndef DILATEFILTER_H
#define DILATEFILTER_H

#include <QMap>

#include "Arguments/structuringelementargument.h"

#include "filter.h"

class DilateFilter : public Filter
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit DilateFilter(FilterObserver *observer = 0,
                                      QObject *parent = 0);
    QStringList codeSnippet() const Q_DECL_OVERRIDE;
    cv::Mat &process(cv::Mat &input) Q_DECL_OVERRIDE;

    virtual void read(QDataStream &data);
    virtual void write(QDataStream &data) const;

    static QString filterName;

public slots:
    void setBorderType(const QString &borderType);
    void setIterations(int iterations);

protected:
    QLayout *dialogParametersGroupLayout() Q_DECL_OVERRIDE;
    QLabel *dialogDescriptionLabel() Q_DECL_OVERRIDE;

private:
    StructuringElementArgument m_kernel;
    cv::Point m_anchor;
    int m_iterations;
    int m_borderType;
    cv::Scalar m_borderValue;
    QMap<int, QString> m_borderTypeMap;
};

Q_DECLARE_METATYPE(DilateFilter *)

#endif // DILATEFILTER_H
