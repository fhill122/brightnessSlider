#include <QApplication>
#include <QSettings>
#include "globalconfig.h"
#include <QDebug>
#include "mainapp.h"
#include <QFile>
#include <QDir>

#define LOG_TO_FILE 0

namespace global {
    QFile outFile(QDir::currentPath()+"/abclog.txt");
}

void myMessageOutput(QtMsgType type, const QMessageLogContext &, const QString &msg)
{
    QString txt;
    switch (type) {
    case QtDebugMsg:
        txt = QString("Debug: %1").arg(msg);
        break;
    case QtWarningMsg:
        txt = QString("Warning: %1").arg(msg);
        break;
    case QtCriticalMsg:
        txt = QString("Critical: %1").arg(msg);
        break;
    case QtFatalMsg:
        txt = QString("Fatal: %1").arg(msg);
        break;
    }
    QTextStream ts(&global::outFile);
    ts << txt << endl;
}


int main(int argc, char *argv[])
{
    // must set before QApplication object created
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    global::outFile.remove();
    global::outFile.open(QIODevice::WriteOnly | QIODevice::Append);
    if(LOG_TO_FILE){
        qInstallMessageHandler(myMessageOutput);
    }

    QSettings::setDefaultFormat(QSettings::IniFormat);
    QApplication::setOrganizationName(GlobalConfig::OrganizationName);
//    QApplication::setApplicationName(GlobalConfig::ApplicationName);

    QApplication a(argc, argv);
    MainApp app(&a);
    return app.run();
}

