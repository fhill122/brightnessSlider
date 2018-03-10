#include "mainapp.h"
#include <QProcess>
#include <QFile>

MainApp::MainApp(QApplication* a,QObject *parent) : QObject(parent), qapp(a)
{
    a->setQuitOnLastWindowClosed(false);

    QObject::connect(&trayIcon, &QSystemTrayIcon::activated, &w, &PopupWindow::Popup );
    QObject::connect(trayIcon.aboutAction,  &QAction::triggered, &aw, [=](){aw.show();});
    QObject::connect(trayIcon.settingAction,  &QAction::triggered, &sw, [=](){sw.show();});
    QObject::connect(&sw, &SettingWindow::newSetting, &w, &PopupWindow::RefreshUi );
    QObject::connect(&sw, &SettingWindow::newSetting, &trayIcon, &TrayIcon::OnNewSetting);
    QObject::connect(&powerMonitor, &PowerMonitor::powerStatusUpdated, &trayIcon, &TrayIcon::OnPsChange );
    //reserved
    QObject::connect(&powerMonitor, &PowerMonitor::powerStatusUpdated, &w, &PopupWindow::UpdateBatteryInfo );

}

int MainApp::run()
{
    // guard single instance
    if(instance.hasPrevious(name, QCoreApplication::arguments())){
        return 0;
    }
    instance.listen(name);

    initSetting();

    trayIcon.show();

    return qapp->exec();
}

void MainApp::initSetting()
{
    QSettings s;
    if(s.contains("popup/background_a")){
        return;
    }
    else{
        qDebug()<<"No setting file! Default setting applied";
        sw.resetToDefault();
    }
}

void MainApp::restart()
{
    qDebug()<<"restart!";
    qapp->quit();
    QProcess::startDetached(qapp->arguments()[0], qapp->arguments());
}

MainApp::~MainApp()
{

}
