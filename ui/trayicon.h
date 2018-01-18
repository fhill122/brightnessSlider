#ifndef TRAYICON_H
#define TRAYICON_H

#include <QSystemTrayIcon>
#include <QMenu>
#include <windows.h>
#include <QSettings>

class TrayIcon : public QSystemTrayIcon
{
    Q_OBJECT

public:
    QAction *settingAction, *aboutAction, *exitAction;

private:
    const QString staticIconFile = ":/tray/images/staticTray.png";

    QFont font;
    QMenu menu;
    QPixmap chargingBackground;
    BYTE percentage = 255;
    BYTE ACLineStatus;
    QSettings setting;

public:
    TrayIcon(QObject *parent = Q_NULLPTR);
    ~TrayIcon();
    // for receiving power status signal
    void OnPsChange( _SYSTEM_POWER_STATUS powerStatus);
    void OnNewSetting();

private:
    void UpdateBatteryIcon (int percentage, bool plugged);
    // refresh icon due to dpi change
    void RefreshIcon();
    QRect GetBoundingRect(QString);
    void DrawNumber(int percentage, bool plugged, QPainter& painter, QRect rect);
};

#endif // TRAYICON_H
