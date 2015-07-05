#ifndef FILTER_H
#define FILTER_H

#include <QObject>
#include <QString>
#include <QStringList>
#include <opencv2/core/core.hpp>

Q_DECLARE_METATYPE(cv::Mat)

class QDialog;
class FilterObserver;

class Filter : public QObject
{
    Q_OBJECT
public:
    explicit Filter(const QString &name = QString(), FilterObserver *observer = 0, QObject *parent = 0);
    ~Filter();

    virtual cv::Mat &process(cv::Mat &input) const;

    virtual QStringList codeSnippet() const;
    virtual QDialog *createDialog(QWidget *parent = 0);
    QString name() const;

protected:
    QString m_name;
    FilterObserver *m_filterObserver;

signals:
    void updated();

};

Q_DECLARE_METATYPE(Filter *)

#endif // FILTER_H
