#ifndef POPUPWINDOW_H
#define POPUPWINDOW_H

#include <QMainWindow>
#include "brightnessControl.h"
#include <QSystemTrayIcon>
#include <QPropertyAnimation>
#include <QSettings>

namespace Ui {
class PopupWindow;
}

class PopupWindow : public QMainWindow
{
    Q_OBJECT

private:
    // window pixel size in 1.0 scale ratio
    const int WINDOW_W = 360;
    const int WINDOW_H = 60;
    const int ANIMATION_DURATION = 150;
    const QString BRIGHTNESS_ICON = ":/popupWindow/images/BrightnessIconWhite.png";
    const int GROOVE_HEIGHT = 10;

    Ui::PopupWindow *ui;
    BrightnessControl brightnessControl;
    int sliderRGB[3];
    QPropertyAnimation *animation;
    QString timeLabel;
    QString percentLabel;
    QPixmap pBrightnessIcon;
    QSettings setting;


private:
    bool nativeEvent(const QByteArray & eventType, void * message, long * result) Q_DECL_OVERRIDE;
    bool PopupWindow::TogglePressAndHold(bool enable);
    void SetGeometry();

public:
    explicit PopupWindow(QWidget *parent = 0);
    ~PopupWindow();
    void RefreshUi();
    void Popup(QSystemTrayIcon::ActivationReason reason);
    //reserved
    void UpdateBatteryInfo(_SYSTEM_POWER_STATUS powerStatus);

protected:
    void paintEvent(QPaintEvent *event) override;
};

#endif // POPUPWINDOW_H
