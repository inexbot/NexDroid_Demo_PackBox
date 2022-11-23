#include "widgetmanager.h"

QPointer<WidgetManager> WidgetManager::_pInstance = NULL;
QPointer<WidgetManager> WidgetManager::getInstance()
{
    if(_pInstance == NULL)
    {
        _pInstance = new WidgetManager;
    }
    return _pInstance;
}

WidgetManager::WidgetManager(QObject *parent) :
    QObject(parent)
{
    Nextp::getInstance();
//    Nextp::getInstance()->hideTechnologyToolbuttons();
    Nextp::getInstance()->renameUserButtonName(QString("冲压工艺"));

    Nextp::getInstance()->setHandle(SettingParaWidget::sendStartData);
    Nextp::getInstance()->setReserveButtonHandle(SettingParaWidget::pressReserveButton);
}

void WidgetManager::initWidgetRelation()
{
    connect(Nextp::getInstance(),SIGNAL(signal_openWidget()),this,SLOT(slot_openWidget()));
    connect(Nextp::getInstance(),SIGNAL(signal_closeWidget()),this,SLOT(slot_closeWidget()));
    connect(Nextp::getInstance(),SIGNAL(signal_receiveMessage(const quint16 &,const QByteArray &)),this,SLOT(slot_receiveMessage(const quint16 &,const QByteArray &)));
    connect(Nextp::getInstance(),SIGNAL(signal_robotMode(int)),this,SLOT(slot_changemode(int)));
}

QString WidgetManager::getSystemFont()
{
    return Nextp::getInstance()->getSystemFont();
}

void WidgetManager::slot_openWidget()
{
    Nextp::getInstance()->setWidgetParentLocation((QWidget *)SettingParaWidget::getInstance());
    SettingParaWidget::getInstance()->show();
    SettingParaWidget::getInstance()->raise();
    Nextp::getInstance()->widgetShowFinish();
}

void WidgetManager::slot_closeWidget()
{
     SettingParaWidget::getInstance()->hide();
}

void WidgetManager::slot_receiveMessage(const quint16 &command,const QByteArray &data)
{
//    QString datastr = QString("接收控制器指令-->>：[0x")+QString::number(command,16).toUpper()+QString("],")+QString(data);
//    qDebug()<<datastr;
    SettingParaWidget::getInstance()->slot_receiveMessage(command, data);
}

void WidgetManager::slot_changemode(int mode)
{
qDebug()<<"模式切换 = "<<mode;
}
