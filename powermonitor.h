/*
 * Periodically check battery level
 *
 * Listen to plugged in state change
 *
 * GetSystemPowerStatus function
 * https://msdn.microsoft.com/en-us/library/windows/desktop/aa372693(v=vs.85).aspx
 * Register power setting notification
 * https://msdn.microsoft.com/en-us/library/aa373196(VS.85).aspx
 */

#ifndef POWERMONITOR_H
#define POWERMONITOR_H

#include <QWidget>
#include <Windows.h>
#include "popupWindow.h"
#include "trayicon.h"
#include "powermonitor.h"
#include <QTimer>


class PowerMonitor: public QWidget
{
private:
    static _SYSTEM_POWER_STATUS powerStatus;
    QTimer *updateTimer; // for routineUpdate
    const int period = 60; // background checking period (seconds)
    bool updatedRecently = false;

    HPOWERNOTIFY hPowerSourceNotify;
    HPOWERNOTIFY hPowerPercentageNotify;
    HWND windowHandle;

    TrayIcon *tray = NULL;
    PopupWindow *window = NULL;


public:


private:
    bool nativeEvent(const QByteArray & eventType, void * message, long * result) Q_DECL_OVERRIDE;
    void RoutineUpdate();

public:
    PowerMonitor(QWidget *parent = Q_NULLPTR);
    ~PowerMonitor();
    bool UpdateOnce(); //update immediately. Usually not required
    void AddListeners(TrayIcon *t, PopupWindow *w);
    _SYSTEM_POWER_STATUS getPowerStatus();
    static bool isOnAC();
};

#endif // POWERMONITOR_H
