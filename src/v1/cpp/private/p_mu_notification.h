#pragma once

#include <QTimer>
#include <QObject>
#include <QThread>
#include <QJsonDocument>
#include <QtWebSockets/QWebSocket>
#include "../mu_notification.h"
#include "../mu_register.h"

class Q_MU_EXPORT MUNotificationPool : public QThread
{
    Q_OBJECT
public:
    QString url;
    QWebSocket client;
    QTimer timerPing;
    QTimer timerPong;
    QByteArray payloadPing;
    QByteArray payloadPong;
    MUNotification*parent=nullptr;

    explicit MUNotificationPool(QString url, MUNotification *parent = nullptr);

    void run();

public slots:

    void makeNotification(const QByteArray &message);

    void connected();

    void disconnected();

    void socketTextMessageReceived(const QString &message);

    void socketBinaryMessageReceived(const QByteArray &message);

    void socketError(QAbstractSocket::SocketError socketError);

    void socketPing();

    void socketPong(quint64 elapsedTime, const QByteArray &payload);

    void socketPingTimeOut();

    bool initConnection();
};

class Q_MU_EXPORT MUNotificationPvt : public QObject
{
    Q_OBJECT
public:
    MUNotification*parent=nullptr;
    MUNotificationPool*pull=nullptr;
    QString url="localhost";
    explicit MUNotificationPvt(MUNotification *parent = nullptr);

    ~MUNotificationPvt();
};
