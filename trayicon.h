#ifndef TRAYICON_H
#define TRAYICON_H

#include <QSystemTrayIcon>
#include <QMenu>
#include <windows.h>

class TrayIcon : public QSystemTrayIcon
{
    Q_OBJECT

public:


private:
    QFont font;
    QMenu menu;
    QPixmap chargingBackground;
    BYTE percentage = 255;
    BYTE ACLineStatus;

public:
    TrayIcon(QObject *parent = Q_NULLPTR);
    ~TrayIcon();
    void UpdateIcon( _SYSTEM_POWER_STATUS powerStatus);

private:
    void UpdateIcon (int percentage, bool plugged);
    // refresh icon due to dpi change
    void RefreshIcon();
    QRect getBoundingRect(QString);
    void drawNumber(int percentage, bool plugged, QPainter& painter, QRect rect);
};

#endif // TRAYICON_H
