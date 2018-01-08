#ifndef SINGLEINSTANCE_H
#define SINGLEINSTANCE_H

#include <QObject>
#include <QDebug>
#include <QLocalServer>
#include <QLocalSocket>

class SingleInstance : public QObject
{
    Q_OBJECT

private:
    QLocalSocket* mSocket;
    QLocalServer mServer;

public:
    explicit SingleInstance(QObject *parent = 0);
    ~SingleInstance();
    void listen(QString name);
    bool hasPrevious(QString name, QStringList arg);

signals:
    void newInstance();

public slots:
    void newConnection();
    void readyRead();
};

#endif // SINGLEINSTANCE_H
