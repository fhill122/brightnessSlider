#ifndef SETTINGWINDOW_H
#define SETTINGWINDOW_H

#include <QDialog>
#include <QIcon>
#include <QSettings>
#include <QPushButton>

namespace Ui {
class SettingWindow;
}

class SettingWindow : public QDialog
{
    Q_OBJECT

private:
    Ui::SettingWindow *ui;
    const QString iconFile = ":/windowIcon/images/windowIcon.png";
    QSettings s;
    QColor popup_backgroundColor, popup_sliderColor, tray_batteryColor, tray_lBatteryColor;


public:
    explicit SettingWindow(QWidget *parent = 0);
    void show();
    // forceAll = true to force all setting to default no matter it exists or not;
    // forceAll = false to only reset settings that not exist
    void resetToDefault(bool forceAll = false);
    ~SettingWindow();

private:
    void setButtonColor(QPushButton *button, QColor c);
    void selectButtonColor(QPushButton *button, QColor &buttonColor);
    void accept();
    void reject();

private slots:
    void on_b_bColor_clicked();
    void on_b_customColor_clicked();
    void on_b_batteryColor_clicked();
    void on_b_lowBatteryColor_clicked();

signals:
    void newSetting();
};

#endif // SETTINGWINDOW_H
