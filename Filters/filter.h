#ifndef FILTER_H
#define FILTER_H

#include <QString>
#include <opencv2/core/core.hpp>

class QDialog;

class Filter
{
public:
    Filter();
    Filter(const QString &name);
    virtual ~Filter();

    QDialog *dialog();
    QString getSignature();
    QString name();
    cv::Mat process(cv::Mat);

protected:
    QDialog *m_dialog;
    QString m_name;
};

#endif // FILTER_H
