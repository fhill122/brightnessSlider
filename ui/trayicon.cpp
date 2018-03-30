#include "trayicon.h"
#include "trayconfig.h"
#include <QMenu>
#include <QAction>
#include <QApplication>
#include <QPainter>
#include <QDebug>
#include <Windows.h>
#include <QScreen>
#include <QTimer>


TrayIcon::TrayIcon(QObject *parent):
    QSystemTrayIcon(parent)
{
    // Set menu
    settingAction = menu.addAction("Setting");

    aboutAction = menu.addAction("About");

    exitAction = menu.addAction("Exit");
    QObject::connect(exitAction, &QAction::triggered, this, &QApplication::quit);

    setContextMenu(&menu);

    // Set tray icon
    setIcon(QIcon(QPixmap(staticIconFile)));
    chargingBackground = QPixmap(TrayConfig::chargingBackgroundImage);
    if(chargingBackground.isNull()){
        qDebug() << "Tray charging background image not found!";
    }


    font = QFont( TrayConfig::fontFamily,  TrayConfig::fontSize);

    // link signals
    QObject::connect(QApplication::primaryScreen(), &QScreen::logicalDotsPerInchChanged, this, &TrayIcon::RefreshIcon);

}


QRect TrayIcon:: GetBoundingRect(QString textToDraw){
    QPixmap temp(1,1);
    QPainter tempPainter(&temp);
    tempPainter.setFont( font );
    return tempPainter.boundingRect(QRect(),  Qt::AlignCenter, textToDraw);

}

void TrayIcon:: DrawNumber(int percentage, bool plugged, QPainter& painter, QRect rect){
    if (setting.value("tray/warnLowBattery").toBool() && percentage < setting.value("tray/lowBatteryPercent").toInt() && !plugged) {
        painter.setPen( QColor(setting.value("tray/lowBatteryColor_r").toInt(), setting.value("tray/lowBatteryColor_g").toInt(), setting.value("tray/lowBatteryColor_b").toInt() ));
    }
    else {
        painter.setPen( QColor(setting.value("tray/batteryColor_r").toInt(), setting.value("tray/batteryColor_g").toInt(), setting.value("tray/batteryColor_b").toInt() ));
    }
    painter.setFont( font );
    painter.drawText( rect, Qt::AlignCenter, QString::number(percentage) );

}

/*
 * Generate and set icon from a percentage number (0-100)
*/
void TrayIcon:: UpdateBatteryIcon (int percentage, bool plugged){
    // check
    if (percentage > 100 || percentage < 0)
        return;

    // draw background
    QRect boundingRect = GetBoundingRect("00");
    QPixmap pixmap(boundingRect.height()/TrayConfig::scale, boundingRect.height()/TrayConfig::scale);
    pixmap.fill(QColor(TrayConfig::background_r, TrayConfig::background_g, TrayConfig::background_b, TrayConfig::background_a));
    QPainter painter(&pixmap);

    // Testing the following
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform | QPainter::HighQualityAntialiasing);

    // case: full
    if(percentage ==100){
        if(plugged && setting.value("tray/pluggedInBackground").toBool()){
            painter.drawPixmap(pixmap.rect(), QPixmap(TrayConfig::chargingFullImage));
        }
        else
            painter.drawPixmap(pixmap.rect(), QPixmap(TrayConfig::batteryFullImage));
    }
    // case: not full
    else{
        if (plugged && setting.value("tray/pluggedInBackground").toBool() ){
            painter.drawPixmap(pixmap.rect(), chargingBackground);
            qDebug()<<"charging background";
        }
        DrawNumber(percentage, plugged, painter, pixmap.rect());
    }

    // set icon
    setIcon(QIcon(pixmap));

    qDebug() << "tray updated";
}


void TrayIcon::OnPsChange(_SYSTEM_POWER_STATUS powerStatus){
    // no change required
    if(powerStatus.ACLineStatus == ACLineStatus && powerStatus.BatteryLifePercent == percentage){
        return;
    }

    ACLineStatus = powerStatus.ACLineStatus;
    percentage = powerStatus.BatteryLifePercent;
    if(setting.value("tray/showBattery").toBool()){
        UpdateBatteryIcon(percentage, ACLineStatus);
    }
}

void TrayIcon::OnNewSetting(){
    if(setting.value("tray/showBattery").toBool()){
        qDebug()<<"tray setting updated";
        UpdateBatteryIcon(percentage,ACLineStatus);
    }
    else{
        setIcon(QIcon(QPixmap(staticIconFile)));
    }

}

void TrayIcon::RefreshIcon(){
//    QTimer::singleShot(5000, this, [=](){UpdateBatteryIcon(percentage,ACLineStatus);});
}

TrayIcon::~TrayIcon(){
}
