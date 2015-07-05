#include "qcustomkeysequenceedit.h"
#include <QKeyEvent>

QCustomKeySequenceEdit::QCustomKeySequenceEdit(QWidget *parent): QKeySequenceEdit(parent) { }
QCustomKeySequenceEdit::~QCustomKeySequenceEdit() { }

void QCustomKeySequenceEdit::keyPressEvent(QKeyEvent *pEvent) {
    QKeySequenceEdit::keyPressEvent(pEvent);

    QKeySequence seq(QKeySequence::fromString(keySequence().toString().split(", ").first()));
    setKeySequence(seq);
}
