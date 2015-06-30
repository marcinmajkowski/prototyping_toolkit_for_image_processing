#include <QDebug>

#include "codewidget.h"

CodeWidget::CodeWidget(QWidget *parent) :
    QPlainTextEdit(parent)
{
    // set monospace font
    QFont f = font();
    f.setFamily(QFontDatabase::systemFont(QFontDatabase::FixedFont).family());
    f.setStyleHint(QFont::Monospace);
    setFont(f);
}
