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
    bool updated();
    cv::Mat process(cv::Mat);

signals:
    void resultChanged();
    void parametersChanged();
    void inputChanged();

public slots:

protected:
    bool m_updated;
    QDialog *m_dialog;
    QString m_name;

    virtual QDialog *createDialog();
};

#endif // FILTER_H
