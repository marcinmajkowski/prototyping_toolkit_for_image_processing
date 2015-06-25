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
    bool enabled();

    enum { WaitingForInput, Processing, Ready };

signals:
    void resultChanged(cv::Mat result);
    void statusChanged();
    void resultExpired();

public slots:
    void setInput(cv::Mat input);
    void setWaitingForInput();
    void setEnabled(bool enabled);

protected:
    void setStatus(int status);

    int m_status;
    QDialog *m_dialog;
    QString m_name;
    bool m_enabled;

    cv::Mat m_input;
    cv::Mat m_result;

    virtual QDialog *createDialog();
    virtual void process();
};

#endif // FILTER_H
