#ifndef ABSOLUTEDIFFERENCEFILTER_H
#define ABSOLUTEDIFFERENCEFILTER_H

#include <opencv2/core/core.hpp>

#include "filter.h"

class AbsoluteDifferenceFilter : public Filter
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit AbsoluteDifferenceFilter(FilterObserver *observer = 0, QObject *parent = 0);
    QStringList codeSnippet() const Q_DECL_OVERRIDE;
    cv::Mat &process(cv::Mat &input) Q_DECL_OVERRIDE;

    void read(QDataStream &data) Q_DECL_OVERRIDE;
    void write(QDataStream &data) const Q_DECL_OVERRIDE;

public slots:
    void setSecondInput(const QString &adaptiveMethod);

protected:
    QLayout *dialogParametersGroupLayout() Q_DECL_OVERRIDE;
    QLabel *dialogDescriptionLabel() Q_DECL_OVERRIDE;

private:
    QString m_secondInputPath;
    cv::Mat m_secondInputImage;

    enum AdjustSecondInput {
        NONE,
        SCALE,
        CROP
    };

    AdjustSecondInput m_adjustSecondInput;
};

Q_DECLARE_METATYPE(AbsoluteDifferenceFilter *)

#endif // ABSOLUTEDIFFERENCEFILTER_H
