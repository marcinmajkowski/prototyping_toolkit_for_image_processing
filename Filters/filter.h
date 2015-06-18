#ifndef FILTER_H
#define FILTER_H

#include <QString>
#include <QDialog>
#include <opencv2/core/core.hpp>

class QWidget;

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
    QString m_name;
    QDialog *m_dialog;
};

#endif // FILTER_H
