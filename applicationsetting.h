#ifndef APPLICATIONSETTING_H
#define APPLICATIONSETTING_H

#include <QObject>
#include <QClipboard>
#include <QSettings>

class ApplicationSetting : public QObject
{
    Q_OBJECT

private:
    QClipboard *clipboard;
    QString settingString;
    const QString code = "[g*lvj$q$&s]";
    QSettings *iniSettings;

private:
    bool textIsSetting(QString &content);
    void processSetting(QString &content);
    //load setting from file
    void loadSetting();
    //save setting to file
    void saveSetting();

public:
    explicit ApplicationSetting(QObject *parent = 0);

signals:
    void restartRequired();

public slots:
    void onClipboardChange();
};

#endif // APPLICATIONSETTING_H
