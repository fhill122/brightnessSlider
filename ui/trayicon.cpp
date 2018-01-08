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
    if (TrayConfig::chargingBackground == TrayConfig::C_BACKGROUND_IMAGE) {
        chargingBackground = QPixmap(TrayConfig::chargingBackgroundImage);
        if(chargingBackground.isNull()){
            qDebug() << "Tray charging background image not found!";
        }
    }

    font = QFont( TrayConfig::fontFamily,  TrayConfig::fontSize);

    // link signals
    QObject::connect(QApplication::primaryScreen(), &QScreen::logicalDotsPerInchChanged, this, &TrayIcon::RefreshIcon);

}


QRect TrayIcon:: getBoundingRect(QString textToDraw){
    QPixmap temp(1,1);
    QPainter tempPainter(&temp);
    tempPainter.setFont( font );
    return tempPainter.boundingRect(QRect(),  Qt::AlignCenter, textToDraw);

}

void TrayIcon:: drawNumber(int percentage, bool plugged, QPainter& painter, QRect rect){
    if (percentage < TrayConfig::warnPercentage && !plugged) {
        painter.setPen( QColor(TrayConfig::textW_r, TrayConfig::textW_g, TrayConfig::textW_b, TrayConfig::textW_a));
    }
    else {
        painter.setPen( QColor(TrayConfig::text_r, TrayConfig::text_g, TrayConfig::text_b, TrayConfig::text_a));
    }
    painter.setFont( font );
    painter.drawText( rect, Qt::AlignCenter, QString::number(percentage) );

}

/*
 * Generate and set icon from a percentage number (0-100)
*/
void TrayIcon:: UpdateIcon (int percentage, bool plugged){
    // check
    if (percentage > 100 || percentage < 0)
        return;

    // draw background
    QRect boundingRect = getBoundingRect("00");
    QPixmap pixmap(boundingRect.height()/TrayConfig::scale, boundingRect.height()/TrayConfig::scale);
    pixmap.fill(QColor(TrayConfig::background_r, TrayConfig::background_g, TrayConfig::background_b, TrayConfig::background_a));
    QPainter painter(&pixmap);

    // Testing the following
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform | QPainter::HighQualityAntialiasing);

    // case: full
    if(percentage == 100 && plugged){
        painter.drawPixmap(pixmap.rect(), QPixmap(TrayConfig::chargingFullImage));
    }
    else if (percentage == 100 && !plugged)
        painter.drawPixmap(pixmap.rect(), QPixmap(TrayConfig::batteryFullImage));
    // case: not full
    else{
        if (plugged)
            painter.drawPixmap(pixmap.rect(), chargingBackground);
        drawNumber(percentage, plugged, painter, pixmap.rect());
    }

    // set icon
    setIcon(QIcon(pixmap));

    qDebug() << "tray updated";
}


void TrayIcon::UpdateIcon(_SYSTEM_POWER_STATUS powerStatus){
    // no change required
    if(powerStatus.ACLineStatus == ACLineStatus && powerStatus.BatteryLifePercent == percentage){
        return;
    }

    ACLineStatus = powerStatus.ACLineStatus;
    percentage = powerStatus.BatteryLifePercent;
    UpdateIcon(percentage, ACLineStatus);

}

void TrayIcon::RefreshIcon(){
    QTimer::singleShot(2000, this, [=](){UpdateIcon(percentage,ACLineStatus);});
}

TrayIcon::~TrayIcon(){
}
