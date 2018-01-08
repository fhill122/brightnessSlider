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
    applicationsetting.cpp \
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
    applicationsetting.h \
    mainapp.h \
    globalconfig.h \
    ui/aboutwindow.h \
    ui/popupWindow.h \
    ui/popupconfig.h \
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

# windows header Wbemidl.h violate strictStrings rules
win32: QMAKE_CXXFLAGS_RELEASE -= -Zc:strictStrings
win32: QMAKE_CFLAGS_RELEASE -= -Zc:strictStrings
win32: QMAKE_CFLAGS -= -Zc:strictStrings
win32: QMAKE_CXXFLAGS -= -Zc:strictStrings


