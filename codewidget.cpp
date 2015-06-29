#include "codewidget.h"
#include "pipelinewidget.h"
#include "Filters/filter.h"

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

    for (int i = 0; i < m_pipelineWidget->count(); ++i) {
        Filter *filter = m_pipelineWidget->filter(i);
        if (filter) {
            sourceCode.append(filter->codeSnippet());
        }
    }

    setPlainText(sourceCode.join("\n"));
}

void CodeWidget::setPipelineWidget(PipelineWidget *pipelineWidget)
{
    //TODO disconnect old widget
    m_pipelineWidget = pipelineWidget;
    connect(m_pipelineWidget, SIGNAL(dataChanged()),
            this, SLOT(update()));
}
