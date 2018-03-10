#ifndef MAINAPP_H
#define MAINAPP_H

#include <QObject>
#include <QApplication>
#include "singleinstance.h"
#include "popupWindow.h"
#include "trayicon.h"
#include "powermonitor.h"
#include "settingwindow.h"
#include "aboutwindow.h"

class MainApp : public QObject
{
    Q_OBJECT

    QApplication *qapp;
    PopupWindow w;
    SettingWindow sw;
    AboutWindow aw;
    PowerMonitor powerMonitor;
    TrayIcon trayIcon;
    SingleInstance instance;

    QString name = "YoYoQpKeNc";

private:
    void initSetting();

public:
    explicit MainApp(QApplication* a, QObject *parent = 0);
    ~MainApp();
    int run();

signals:

public slots:
    void restart();
};

#endif // MAINAPP_H
