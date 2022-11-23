#ifndef __DIGITALLINEEDIT_INCLUDE_DIGITALLINEEDIT_H__
#define __DIGITALLINEEDIT_INCLUDE_DIGITALLINEEDIT_H__

// C++ lib import
#include <functional>

// Qt lib improt
#include <QLineEdit>

class DigitalLineEdit: public QLineEdit
{
    Q_OBJECT

public:
    explicit DigitalLineEdit(QWidget *parent = 0);

    ~DigitalLineEdit();

    void mousePressEvent(QMouseEvent *e);
    void setforbidEdit(bool forbid1);
    void finishTyping();

signals:
    void finishType();

public:
    bool event(QEvent *);

protected:
    void keyPressEvent(QKeyEvent *event);
    bool eventFilter(QObject *, QEvent *);
private Q_SLOTS:
    void onTextEdited();

private:
    bool m_forbid;
    static DigitalLineEdit *m_pFocesedItem;
};

// inc import
#include "digitallineedit.inc"

#endif//__DIGITALLINEEDIT_INCLUDE_DIGITALLINEEDIT_H__
