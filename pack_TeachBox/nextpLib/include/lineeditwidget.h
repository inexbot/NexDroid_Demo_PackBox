#ifndef __LINEEDITWIDGET_INCLUDE_LINEEDITWIDGET_H__
#define __LINEEDITWIDGET_INCLUDE_LINEEDITWIDGET_H__

// C++ lib import
#include <functional>

// Qt lib improt
#include <QLineEdit>

class LineEditWidget: public QLineEdit
{
    Q_OBJECT

public:
    explicit LineEditWidget(QWidget *parent = 0);

    ~LineEditWidget();

    void mousePressEvent(QMouseEvent *e);

    void setforbidEdit(bool forbid);
public:
    bool event(QEvent *);
protected:
    void keyPressEvent(QKeyEvent *event);
    bool eventFilter(QObject *, QEvent *);
private Q_SLOTS:

private:
    bool m_forbid;
    static LineEditWidget *m_pFocesedItem;
};

// inc import
#include "lineeditwidget.inc"

#endif//__LINEEDITWIDGET_INCLUDE_LINEEDITWIDGET_H__
