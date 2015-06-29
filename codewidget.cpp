#include "codewidget.h"
#include "pipelinewidget.h"

CodeWidget::CodeWidget(QWidget *parent) :
    QPlainTextEdit(parent)
{
}

void CodeWidget::update()
{
    if (!m_pipelineWidget) {
        return;
    }

    QStringList sourceCode;
    //TODO get codeSnippets from all filters in the pipeline

    setPlainText(sourceCode.join("\n"));
}

void CodeWidget::setPipelineWidget(PipelineWidget *pipelineWidget)
{
    //TODO disconnect old widget
    m_pipelineWidget = pipelineWidget;
    connect(m_pipelineWidget, SIGNAL(dataChanged()),
            this, SLOT(update()));
}
