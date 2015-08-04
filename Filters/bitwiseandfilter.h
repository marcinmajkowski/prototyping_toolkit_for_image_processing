#ifndef BITWISEANDFILTER_H
#define BITWISEANDFILTER_H

#include <opencv2/core/core.hpp>

#include "filter.h"

class QLineEdit;

class BitwiseAndFilter : public Filter
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit BitwiseAndFilter(FilterObserver *observer = 0, QObject *parent = 0);
    QStringList codeSnippet() const Q_DECL_OVERRIDE;
    cv::Mat &process(cv::Mat &input) Q_DECL_OVERRIDE;

    void read(QDataStream &data) Q_DECL_OVERRIDE;
    void write(QDataStream &data) const Q_DECL_OVERRIDE;

public slots:
    void setAdjustSecondInput(int adjustSecondInput);
    void browse();

protected:
    QLayout *dialogParametersGroupLayout() Q_DECL_OVERRIDE;
    QLabel *dialogDescriptionLabel() Q_DECL_OVERRIDE;
    bool loadSecondInput(QString fileName);

private:
    QString m_secondInputPath;
    cv::Mat m_secondInputImage;

    enum AdjustSecondInput {
        NONE,
        SCALE,
        CROP
    };

    bool m_convertSecondInput;
    bool m_inputsSizesMatch;

    AdjustSecondInput m_adjustSecondInput;

    QLineEdit *m_pathLineEdit;
};

#endif // BITWISEANDFILTER_H