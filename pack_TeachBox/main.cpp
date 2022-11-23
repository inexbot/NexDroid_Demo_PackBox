#include <QApplication>
#include "widgetmanager.h"
#include <QString>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFont font(WidgetManager::getInstance()->getSystemFont(),18,QFont::Normal,false);
    a.setFont(font);
    WidgetManager::getInstance()->initWidgetRelation();
    return a.exec();
}
