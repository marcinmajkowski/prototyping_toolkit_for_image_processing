#ifndef BLURFILTER_H
#define BLURFILTER_H

#include <QMap>

#include "filter.h"

class BlurFilter : public Filter
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit BlurFilter(FilterObserver *observer = 0, QObject *parent = 0);
    QStringList codeSnippet() const Q_DECL_OVERRIDE;
    cv::Mat &process(cv::Mat &input) Q_DECL_OVERRIDE;

public slots:
    void setBorderType(const QString &type);

protected:
    QLayout *dialogParametersGroupLayout() Q_DECL_OVERRIDE;
    QLabel *dialogDescriptionLabel() Q_DECL_OVERRIDE;

private:
    cv::Size m_ksize;
    cv::Point m_anchor;
    int m_borderType;
    QMap<int, QString> m_borderTypeMap;
};

Q_DECLARE_METATYPE(BlurFilter *)

#endif // BLURFILTER_H
