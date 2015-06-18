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
    Filter(const QString &name, QWidget *parent);
    virtual ~Filter();

    QDialog *dialog();
    QString getSignature();
    QString name();
    cv::Mat process(cv::Mat);

protected:
    QWidget *m_parent;
    QDialog *m_dialog;
    QString m_name;
};

#endif // FILTER_H
