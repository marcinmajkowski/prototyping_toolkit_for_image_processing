#ifndef FILTER_H
#define FILTER_H

#include <QObject>
#include <QString>
#include <opencv2/core/core.hpp>

class QDialog;

class Filter : public QObject
{
    Q_OBJECT
public:
    explicit Filter(const QString &name = QString(), QObject *parent = 0);
    ~Filter();

    QDialog *dialog();
    QString getSignature();
    QString name();
    cv::Mat process(cv::Mat);

signals:

public slots:

protected:
    QDialog *m_dialog;
    QString m_name;
};

#endif // FILTER_H
