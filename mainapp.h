#ifndef MAINAPP_H
#define MAINAPP_H

#include <QObject>
#include <QApplication>
#include "singleinstance.h"
#include "popupWindow.h"
#include "trayicon.h"
#include "powermonitor.h"
#include "applicationsetting.h"

class MainApp : public QObject
{
    Q_OBJECT

    QApplication *qapp;
    ApplicationSetting appSetting;
    PopupWindow w;
    PowerMonitor powerMonitor;
    TrayIcon trayIcon;
    SingleInstance instance;

    QString name = "YoYoQpKeNc";

private:

public:
    explicit MainApp(QApplication* a, QObject *parent = 0);
    ~MainApp();
    int run();

signals:

public slots:
    void restart();
};

#endif // MAINAPP_H
