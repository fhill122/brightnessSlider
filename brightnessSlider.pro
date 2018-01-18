#-------------------------------------------------
#
# Project created by QtCreator 2017-02-10T14:13:19
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = brightnessSlider
TEMPLATE = app

INCLUDEPATH += $$PWD/ui

SOURCES += main.cpp\
    powermonitor.cpp \
    brightnessControl.cpp \
    singleinstance.cpp \
    mainapp.cpp \
    ui/aboutwindow.cpp \
    ui/popupWindow.cpp \
    ui/trayicon.cpp \
    ui/touchslider.cpp \
    ui/settingwindow.cpp

HEADERS  += \
    powermonitor.h \
    brightnessControl.h \
    singleinstance.h \
    mainapp.h \
    globalconfig.h \
    ui/aboutwindow.h \
    ui/popupWindow.h \
    ui/trayconfig.h \
    ui/settingwindow.h \
    ui/touchslider.h \
    ui/trayicon.h

FORMS    += \
    ui/aboutwindow.ui \
    ui/popupWindow.ui \
    ui/settingwindow.ui

DISTFILES +=

#LIBS += -luser32 -lshell32 -lgdi32

RESOURCES += \
    resources.qrc

# version
VERSION_MAJOR = 1
VERSION_MINOR = 0
VERSION_PATCH = 0
VERSION_BUILD = 0

DEFINES += "VERSION_MAJOR=$$VERSION_MAJOR"\
       "VERSION_MINOR=$$VERSION_MINOR"\
       "VERSION_PATCH=$$VERSION_PATCH"\
       "VERSION_BUILD=$$VERSION_BUILD"

VERSION = $${VERSION_MAJOR}.$${VERSION_MINOR}.$${VERSION_PATCH}.$${VERSION_BUILD}

# windows header Wbemidl.h violate strictStrings rules
win32: QMAKE_CXXFLAGS_RELEASE -= -Zc:strictStrings
win32: QMAKE_CFLAGS_RELEASE -= -Zc:strictStrings
win32: QMAKE_CFLAGS -= -Zc:strictStrings
win32: QMAKE_CXXFLAGS -= -Zc:strictStrings


