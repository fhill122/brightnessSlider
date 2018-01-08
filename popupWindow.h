#ifndef POPUPWINDOW_H
#define POPUPWINDOW_H

#include <QMainWindow>
#include "brightnessControl.h"
#include <QSystemTrayIcon>
#include <QPropertyAnimation>

namespace Ui {
class PopupWindow;
}

class PopupWindow : public QMainWindow
{
    Q_OBJECT

private:
    Ui::PopupWindow *ui;
    BrightnessControl brightnessControl;
    int sliderRGB[3];
    QPropertyAnimation *animation;
    QString timeLabel;
    QString percentLabel;

private:
    bool nativeEvent(const QByteArray & eventType, void * message, long * result) Q_DECL_OVERRIDE;
    bool PopupWindow::TogglePressAndHold(bool enable);
    void SetGeometry();
    void RefreshUi();

public:
    explicit PopupWindow(QWidget *parent = 0);
    ~PopupWindow();
    void Popup(QSystemTrayIcon::ActivationReason reason);
    void UpdateBatteryInfo(_SYSTEM_POWER_STATUS powerStatus);

protected:
    void paintEvent(QPaintEvent *event) override;
};

#endif // POPUPWINDOW_H
