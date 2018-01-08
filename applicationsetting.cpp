#include "applicationsetting.h"
#include <QDebug>
#include <QApplication>
#include <QTimer>
#include "globalconfig.h"


ApplicationSetting::ApplicationSetting(QObject *parent) : QObject(parent)
{
    clipboard = QApplication::clipboard();
    qDebug()<< "Setting file location:" << GlobalConfig::settingFile;
    iniSettings = new QSettings(GlobalConfig::settingFile, QSettings::IniFormat, this);
    iniSettings->setValue("popup/background_a",0.8);
    iniSettings->sync();

    connect(clipboard, SIGNAL(dataChanged()), this, SLOT(onClipboardChange()));

}

void ApplicationSetting::onClipboardChange()
{
    QString clipboardContent = clipboard->text();

    if(!textIsSetting(clipboardContent)){
        return;
    }

    //valid setting detected
    clipboard->blockSignals(true);
    processSetting(clipboardContent);
    QTimer::singleShot(100, [=](){clipboard->blockSignals(false);} );

}


bool ApplicationSetting::textIsSetting(QString &content)
{
    if (content.startsWith(code) && content.endsWith(code)){
        return true;
    }
    return false;
}

void ApplicationSetting::processSetting(QString &content)
{
    QStringList setting = content.split('\n');
    setting.removeFirst();
    setting.removeLast();
    qDebug()<<setting;

    //empty clipboard
    clipboard->clear();

    // restart program
    emit restartRequired();

}

void ApplicationSetting::loadSetting()
{


}


