#ifndef SETTINGWINDOW_H
#define SETTINGWINDOW_H

#include <QDialog>
#include <QIcon>

namespace Ui {
class SettingWindow;
}

class SettingWindow : public QDialog
{
    Q_OBJECT

private:
    const QString iconFile = ":/windowIcon/images/windowIcon.png";

public:
    explicit SettingWindow(QWidget *parent = 0);
    ~SettingWindow();

private:
    Ui::SettingWindow *ui;
};

#endif // SETTINGWINDOW_H
