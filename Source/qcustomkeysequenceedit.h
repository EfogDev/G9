#ifndef QCUSTOMKEYSEQUENCEEDIT_H
#define QCUSTOMKEYSEQUENCEEDIT_H

#include <QKeySequenceEdit>

class QKeyEvent;

class QCustomKeySequenceEdit: public QKeySequenceEdit {
    Q_OBJECT

    public:
        explicit QCustomKeySequenceEdit(QWidget *parent = 0);
        ~QCustomKeySequenceEdit();

    protected:
        void keyPressEvent(QKeyEvent *pEvent);
};

#endif // QCUSTOMKEYSEQUENCEEDIT_H
