#ifndef BINARYOPERATIONFILTER_H
#define BINARYOPERATIONFILTER_H

#include <opencv2/core/core.hpp>

#include "filter.h"

class QLineEdit;

class BinaryOperationFilter : public Filter
{
    Q_OBJECT

// protected constructor prevents instantiation - this is an abstract class
protected:
    explicit BinaryOperationFilter(const QString &name = QString(),
                                   FilterObserver *observer = 0,
                                   QObject *parent = 0);

public:
    virtual ~BinaryOperationFilter();
    virtual QStringList codeSnippet() const Q_DECL_OVERRIDE;
    virtual cv::Mat &process(cv::Mat &input) Q_DECL_OVERRIDE;

    virtual void read(QDataStream &data) Q_DECL_OVERRIDE;
    virtual void write(QDataStream &data) const Q_DECL_OVERRIDE;

    virtual QString binaryOperationName() const = 0;
    virtual void binaryOperation(cv::Mat &input,
                                 cv::Mat &secondInput) = 0;

public slots:
    void browse();

protected:
    virtual QLayout *dialogParametersGroupLayout() Q_DECL_OVERRIDE;
    virtual QLabel *dialogDescriptionLabel() Q_DECL_OVERRIDE;
    bool loadSecondInput(QString fileName);

private:
    QString m_secondInputPath;
    cv::Mat m_secondInputImage;

    bool m_convertSecondInput;
    bool m_inputsSizesMatch;

    QLineEdit *m_pathLineEdit;
};

#endif // BINARYOPERATIONFILTER_H
