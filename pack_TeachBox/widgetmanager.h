#ifndef WIDGETMANAGER_H
#define WIDGETMANAGER_H

#include <QObject>
#include "nextp.h"
#include <QPointer>
#include <QDebug>
#include "settingparawidget.h"
#include <QFont>

#define BUTTONSET tr("QPushButton{border-image: url(:/image/ButtonReturnNormal.png);color:rgb(255,255,255)}")
#define BUTTONSET1 tr("QPushButton:pressed{border-image: url(:/image/ButtonReturnDown.png);}")

class WidgetManager : public QObject
{
    Q_OBJECT
public:
    static QPointer<WidgetManager> getInstance();
    void initWidgetRelation();
    QString getSystemFont();
signals:
    void signal_closeSettingParaWidget();
public slots:
    void slot_openWidget();
    void slot_closeWidget();
    void slot_receiveMessage(const quint16 &command,const QByteArray &data);
    void slot_changemode(int mode);
private:
    explicit WidgetManager(QObject *parent = 0);
    static QPointer<WidgetManager> _pInstance;


};

#endif // WIDGETMANAGER_H
