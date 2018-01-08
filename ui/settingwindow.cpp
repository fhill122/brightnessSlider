#include "settingwindow.h"
#include "ui_settingwindow.h"

SettingWindow::SettingWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingWindow)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
}

SettingWindow::~SettingWindow()
{
    delete ui;
}
