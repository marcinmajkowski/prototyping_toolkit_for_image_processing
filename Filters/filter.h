#ifndef FILTER_H
#define FILTER_H

#include <QString>
#include <QWidget>
#include <opencv2/core/core.hpp>

class QWidget;

class Filter
{
public:
    Filter();
    Filter(const QString &name);
    virtual ~Filter();

    QWidget *widget();
    QString getSignature();
    QString name();
    cv::Mat process(cv::Mat);

protected:
    QString m_name;
    QWidget *m_widget;
};

#endif // FILTER_H
