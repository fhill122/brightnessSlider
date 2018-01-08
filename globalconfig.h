#ifndef GLOBALCONFIG_H
#define GLOBALCONFIG_H
#include <QDir>

namespace GlobalConfig {
    const QString settingFile = QDir::currentPath()+"/bsconfig.ini";
}

#endif // GLOBALCONFIG_H
