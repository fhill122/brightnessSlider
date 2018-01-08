#include "mainapp.h"
#include <QProcess>
#include <QFile>

MainApp::MainApp(QApplication* a,QObject *parent) : QObject(parent), qapp(a)
{
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    a->setQuitOnLastWindowClosed(false);

    powerMonitor.AddListeners(&trayIcon, &w);

    QObject::connect(&trayIcon, &QSystemTrayIcon::activated, &w, &PopupWindow::Popup );
    QObject::connect(&appSetting, SIGNAL(restartRequired()), this, SLOT(restart()));
    QObject::connect(&appSetting, &ApplicationSetting::restartRequired, this, [=](){trayIcon.showMessage("New settings applied","");});
    QObject::connect(trayIcon.aboutAction,  &QAction::triggered, &aw, [=](){aw.show();});
    QObject::connect(trayIcon.settingAction,  &QAction::triggered, &sw, [=](){sw.show();});


}

int MainApp::run()
{
    // guard single instance
    if(instance.hasPrevious(name, QCoreApplication::arguments())){
        return 0;
    }
    instance.listen(name);

    trayIcon.show();


    return qapp->exec();
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
