#ifndef CODEWIDGET_H
#define CODEWIDGET_H

#include <QPlainTextEdit>

class PipelineWidget;

class CodeWidget : public QPlainTextEdit
{
    Q_OBJECT
public:
    explicit CodeWidget(QWidget *parent = 0);

signals:

public slots:
    void update();
    void setPipelineWidget(PipelineWidget *pipelineWidget);

private:
    PipelineWidget *m_pipelineWidget;

};

#endif // CODEWIDGET_H
