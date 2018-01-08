#-------------------------------------------------
#
# Project created by QtCreator 2017-02-10T14:13:19
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = brightnessSlider
TEMPLATE = app


SOURCES += main.cpp\
    trayicon.cpp \
    powermonitor.cpp \
    brightnessControl.cpp \
    popupWindow.cpp \
    touchslider.cpp \
    singleinstance.cpp \
    applicationsetting.cpp \
    mainapp.cpp

HEADERS  += \
    trayicon.h \
    trayconfig.h \
    powermonitor.h \
    brightnessControl.h \
    popupWindow.h \
    touchslider.h \
    popupconfig.h \
    singleinstance.h \
    applicationsetting.h \
    mainapp.h \
    globalconfig.h

FORMS    += \
    popupWindow.ui \
#    popupWindow_batteryLabel.ui

DISTFILES +=

#LIBS += -luser32 -lshell32 -lgdi32

RESOURCES += \
    resources.qrc

# windows header Wbemidl.h violate strictStrings rules
win32: QMAKE_CXXFLAGS_RELEASE -= -Zc:strictStrings
win32: QMAKE_CFLAGS_RELEASE -= -Zc:strictStrings
win32: QMAKE_CFLAGS -= -Zc:strictStrings
win32: QMAKE_CXXFLAGS -= -Zc:strictStrings


