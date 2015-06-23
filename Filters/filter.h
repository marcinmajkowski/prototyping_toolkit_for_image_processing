#ifndef FILTER_H
#define FILTER_H

#include <QObject>
#include <QString>
#include <opencv2/core/core.hpp>

Q_DECLARE_METATYPE(cv::Mat)

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
    int status();

    enum { NotReady, Processing, Ready };

signals:
    void resultChanged(cv::Mat result);
    void notReady();

public slots:
    void setInput(cv::Mat input);
    void setNotReady();

protected:
    int m_status;
    QDialog *m_dialog;
    QString m_name;

    cv::Mat m_input;
    cv::Mat m_result;

    virtual QDialog *createDialog();
    virtual void process();
};

#endif // FILTER_H
