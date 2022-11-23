#-------------------------------------------------
#
# Project created by QtCreator 2020-04-27T16:30:39
#
#-------------------------------------------------

QT       += core gui sql network xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Qt-tp
TEMPLATE = app
MOC_DIR   = temp/moc
RCC_DIR     = temp/rcc
UI_DIR        = temp/ui
OBJECTS_DIR   = temp/obj
DESTDIR       = bin

equals( QT_MAJOR_VERSION, 5 ) CONFIG += c++11
equals( QT_MAJOR_VERSION, 4 ) QMAKE_CXXFLAGS += -std=c++0x

SOURCES += main.cpp\
    settingparawidget.cpp \
    widgetmanager.cpp

HEADERS  += \
    settingparawidget.h \
    widgetmanager.h \
    nextpLib/commonLibrary/include/nextp.h \
    nextpLib/commonLibrary/include/digitallineedit.h \
    nextpLib/commonLibrary/include/lineeditwidget.h \
    nextpLib/include/nextp.h \
    nextpLib/include/lineeditwidget.h \
    nextpLib/include/digitallineedit.h

FORMS    += \
    settingparawidget.ui

equals( QT_MAJOR_VERSION, 5 ){
    equals( QT_MINOR_VERSION, 2 ){
           equals( QT_PATCH_VERSION, 1 ){

            unix: LIBS += -L$$PWD/nextpLib/Library/linuxlib/ -linextp

            INCLUDEPATH += $$PWD/nextpLib/include
            DEPENDPATH += $$PWD/nextpLib/include
            unix: PRE_TARGETDEPS += $$PWD/nextpLib/Library/linuxlib/libinextp.a
            }
    }
}

equals( QT_MAJOR_VERSION, 4 ){
    equals( QT_MINOR_VERSION,8 ){
           equals( QT_PATCH_VERSION, 5 ){

            unix: LIBS += -L$$PWD/nextpLib/Library/T30lib/ -linextp

            INCLUDEPATH += $$PWD/nextpLib/include
            DEPENDPATH += $$PWD/nextpLib/include

            unix: PRE_TARGETDEPS += $$PWD/nextpLib/Library/T30lib/libinextp.a
            }
    }
}

RESOURCES += \
    image.qrc
