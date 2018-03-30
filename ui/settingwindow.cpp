#include "settingwindow.h"
#include "ui_settingwindow.h"
#include <QDebug>
#include <QColorDialog>

SettingWindow::SettingWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingWindow)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    setWindowIcon(QIcon(iconFile));
}

void SettingWindow::show(){
    //load setting
    //popup/background
    ui->s_transparency->setValue(s.value("popup/background_a").toFloat()*100 + 0.5);

    popup_backgroundColor.setRgb(s.value("popup/background_r").toInt(), s.value("popup/background_g").toInt(), s.value("popup/background_b").toInt());
    setButtonColor(ui->b_bColor,popup_backgroundColor);

    //popup/slider
    ui->cb_matchSystem->setChecked(s.value("popup/sliderMatchSysColor").toBool());

    popup_sliderColor.setRgb(s.value("popup/sliderColor_r").toInt(), s.value("popup/sliderColor_g").toInt(), s.value("popup/sliderColor_b").toInt());
    setButtonColor(ui->b_customColor,popup_sliderColor);

    //tray/showBattery
    ui->cb_showPencentage->setChecked(s.value("tray/showBattery").toBool());

    tray_batteryColor.setRgb(s.value("tray/batteryColor_r").toInt(), s.value("tray/batteryColor_g").toInt(), s.value("tray/batteryColor_b").toInt());
    setButtonColor(ui->b_batteryColor,tray_batteryColor);

    ui->cb_lowBattery->setChecked(s.value("tray/warnLowBattery").toBool());

    ui->s_lowBattery->setValue(s.value("tray/lowBatteryPercent").toInt());

    tray_lBatteryColor.setRgb(s.value("tray/lowBatteryColor_r").toInt(), s.value("tray/lowBatteryColor_g").toInt(), s.value("tray/lowBatteryColor_b").toInt());
    setButtonColor(ui->b_lowBatteryColor,tray_lBatteryColor);

    ui->cb_pluggedInBackground->setChecked(s.value("tray/pluggedInBackground").toBool());

    QDialog::show();
}

void SettingWindow::resetToDefault(bool forceAll){
    if (forceAll || !s.contains("popup/background_a") ){ s.setValue("popup/background_a", 0.8);}
    if (forceAll || !s.contains("popup/background_r") ){ s.setValue("popup/background_r", 0);}
    if (forceAll || !s.contains("popup/background_g") ){ s.setValue("popup/background_g", 0);}
    if (forceAll || !s.contains("popup/background_b") ){ s.setValue("popup/background_b", 0);}
    if (forceAll || !s.contains("popup/sliderMatchSysColor") ){ s.setValue("popup/sliderMatchSysColor", true);}
    if (forceAll || !s.contains("popup/sliderColor_r") ){ s.setValue("popup/sliderColor_r", 0);}
    if (forceAll || !s.contains("popup/sliderColor_g") ){ s.setValue("popup/sliderColor_g", 85);}
    if (forceAll || !s.contains("popup/sliderColor_b") ){ s.setValue("popup/sliderColor_b", 255);}
    if (forceAll || !s.contains("tray/showBattery") ){ s.setValue("tray/showBattery", true);}
    if (forceAll || !s.contains("tray/batteryColor_r") ){ s.setValue("tray/batteryColor_r", 255);}
    if (forceAll || !s.contains("tray/batteryColor_g") ){ s.setValue("tray/batteryColor_g", 255);}
    if (forceAll || !s.contains("tray/batteryColor_b") ){ s.setValue("tray/batteryColor_b", 255);}
    if (forceAll || !s.contains("tray/warnLowBattery") ){ s.setValue("tray/warnLowBattery", true);}
    if (forceAll || !s.contains("tray/lowBatteryPercent") ){ s.setValue("tray/lowBatteryPercent", 30);}
    if (forceAll || !s.contains("tray/lowBatteryColor_r") ){ s.setValue("tray/lowBatteryColor_r", 255);}
    if (forceAll || !s.contains("tray/lowBatteryColor_g") ){ s.setValue("tray/lowBatteryColor_g", 50);}
    if (forceAll || !s.contains("tray/lowBatteryColor_b") ){ s.setValue("tray/lowBatteryColor_b", 0);}
    if (forceAll || !s.contains("tray/pluggedInBackground") ){ s.setValue("tray/pluggedInBackground", true);}

    s.sync();
    emit newSetting();
}

void SettingWindow::accept(){
    //popup/background
    s.setValue("popup/background_a", 0.01*ui->s_transparency->value());
    s.setValue("popup/background_r", popup_backgroundColor.red());
    s.setValue("popup/background_g", popup_backgroundColor.green());
    s.setValue("popup/background_b", popup_backgroundColor.blue());
    //popup/slider
    s.setValue("popup/sliderMatchSysColor", ui->cb_matchSystem->isChecked());
    s.setValue("popup/sliderColor_r", popup_sliderColor.red());
    s.setValue("popup/sliderColor_g", popup_sliderColor.green());
    s.setValue("popup/sliderColor_b", popup_sliderColor.blue());
    //tray/showBattery
    s.setValue("tray/showBattery",ui->cb_showPencentage->isChecked());
    s.setValue("tray/batteryColor_r", tray_batteryColor.red());
    s.setValue("tray/batteryColor_g", tray_batteryColor.green());
    s.setValue("tray/batteryColor_b", tray_batteryColor.blue());
    s.setValue("tray/warnLowBattery",ui->cb_lowBattery->isChecked());
    s.setValue("tray/lowBatteryPercent", ui->s_lowBattery->value());
    s.setValue("tray/lowBatteryColor_r", tray_lBatteryColor.red());
    s.setValue("tray/lowBatteryColor_g", tray_lBatteryColor.green());
    s.setValue("tray/lowBatteryColor_b", tray_lBatteryColor.blue());
    s.setValue("tray/pluggedInBackground", ui->cb_pluggedInBackground->isChecked());
    s.sync();

    emit newSetting();
    QDialog::accept();
}

void SettingWindow::reject(){
    QDialog::reject();
}

void SettingWindow::on_b_bColor_clicked(){
    selectButtonColor(ui->b_bColor,popup_backgroundColor);
}

void SettingWindow::on_b_customColor_clicked(){
    selectButtonColor(ui->b_customColor,popup_sliderColor);
}

void SettingWindow::on_b_batteryColor_clicked(){
    selectButtonColor(ui->b_batteryColor,tray_batteryColor);
}

void SettingWindow::on_b_lowBatteryColor_clicked(){
    selectButtonColor(ui->b_lowBatteryColor,tray_lBatteryColor);
}

void SettingWindow::setButtonColor(QPushButton *button, QColor c){
    button->setStyleSheet(QString("background-color: rgb(%1, %2, %3);").arg(c.red()).arg(c.green()).arg(c.blue()));
}

void SettingWindow::selectButtonColor(QPushButton *button, QColor &buttonColor){
    QColor color=QColorDialog::getColor(buttonColor,this);
    if(color.isValid()){
        buttonColor = color;
        setButtonColor(button,buttonColor);
    }
}

SettingWindow::~SettingWindow()
{
    delete ui;
}
