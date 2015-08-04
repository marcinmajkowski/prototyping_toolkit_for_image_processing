#include "absolutedifferencefilter.h"

AbsoluteDifferenceFilter::AbsoluteDifferenceFilter(FilterObserver *observer, QObject *parent) :
    Filter("Absolute difference", observer, parent),
    m_adjustSecondInput(NONE)
{
}

QStringList AbsoluteDifferenceFilter::codeSnippet() const
{
    //TODO
    return Filter::codeSnippet();
}

cv::Mat &AbsoluteDifferenceFilter::process(cv::Mat &input)
{
    //TODO
    return Filter::process(input);
}

void AbsoluteDifferenceFilter::read(QDataStream &data)
{
    //TODO
}

void AbsoluteDifferenceFilter::write(QDataStream &data) const
{
    //TODO
}

void AbsoluteDifferenceFilter::setSecondInput(const QString &adaptiveMethod)
{
    //TODO
}

QLayout *AbsoluteDifferenceFilter::dialogParametersGroupLayout()
{
    return Filter::dialogParametersGroupLayout();
}

QLabel *AbsoluteDifferenceFilter::dialogDescriptionLabel()
{
    return Filter::dialogDescriptionLabel();
}
