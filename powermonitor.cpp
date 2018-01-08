#include "powermonitor.h"
#include <Windows.h>
#include <QMessageBox>
#include <QDebug>

#pragma comment(lib, "user32.lib")

_SYSTEM_POWER_STATUS PowerMonitor::powerStatus;

PowerMonitor::PowerMonitor(QWidget *parent ):QWidget(parent)
{
    hPowerSourceNotify = RegisterPowerSettingNotification((HWND)this->winId(), &GUID_ACDC_POWER_SOURCE, DEVICE_NOTIFY_WINDOW_HANDLE);
    hPowerPercentageNotify = RegisterPowerSettingNotification((HWND)this->winId(), &GUID_BATTERY_PERCENTAGE_REMAINING, DEVICE_NOTIFY_WINDOW_HANDLE);

    if (!GetSystemPowerStatus(&powerStatus)){
        QMessageBox msgBox(QMessageBox::Critical, "Error", "Error get system power status.");
        msgBox.exec();
    }

    updateTimer = new QTimer(this);
    QObject::connect(updateTimer, &QTimer::timeout, this, &PowerMonitor::RoutineUpdate );
    updateTimer -> start(period*1000);

}

// used in update timer
void PowerMonitor::RoutineUpdate(){
    if (!updatedRecently){
        UpdateOnce();
    }

    updatedRecently = false;
    return;
}

bool PowerMonitor::nativeEvent(const QByteArray & , void * message, long * result) {

    MSG *msg = static_cast<MSG*>(message);

    if (msg->message == WM_POWERBROADCAST) {

        if (msg->wParam == PBT_POWERSETTINGCHANGE) {
            POWERBROADCAST_SETTING *p = (POWERBROADCAST_SETTING *)msg->lParam;
            GUID guid = p->PowerSetting;
            if (guid == GUID_ACDC_POWER_SOURCE) {
                //qDebug() << "Power source change!";
                UpdateOnce();
            }
            else if (guid == GUID_BATTERY_PERCENTAGE_REMAINING){
                //qDebug() << "Remaining percentage change!";
                UpdateOnce();
            }
        }

        *result = true;
        return true;
    }

    return false;
}

bool PowerMonitor::UpdateOnce(){
    updatedRecently = true;
    bool result =  GetSystemPowerStatus(&powerStatus);

    qDebug() << "Power monitor updated";

    if(tray!=NULL)
        tray->UpdateIcon(powerStatus);

    if(window!=NULL)
        window->UpdateBatteryInfo(powerStatus);

    return result;
}

void PowerMonitor:: AddListeners(TrayIcon *t, PopupWindow *w){
    tray = t;
    window = w;
}

_SYSTEM_POWER_STATUS PowerMonitor::getPowerStatus(){return powerStatus;}

bool PowerMonitor::isOnAC(){
    return (bool)powerStatus.ACLineStatus;
}

PowerMonitor::~PowerMonitor(){
    delete updateTimer;
    UnregisterPowerSettingNotification(hPowerSourceNotify);
    UnregisterPowerSettingNotification(hPowerPercentageNotify);
}
