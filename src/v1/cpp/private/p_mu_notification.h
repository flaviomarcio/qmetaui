#pragma once

#include <QTimer>
#include <QObject>
#include <QThread>
#include <QJsonDocument>
#include <QtWebSockets/QWebSocket>
#include <QStm>
#include "../mu_notification.h"
#include "../mu_register.h"


static const int intervalPing=10000;
static const int intervalPong=5000;

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

    explicit MUNotificationPool(QString url, MUNotification *parent = nullptr):QThread(nullptr), client(), timerPing()
    {
        this->url=url;
        this->parent=parent;

        connect(this, &MUNotificationPool::startTimer, this, &MUNotificationPool::onStartTimer);
        connect(&this->client, &QWebSocket::disconnected, &this->client, &QWebSocket::deleteLater);
        connect(&this->client, &QWebSocket::textMessageReceived, this, &MUNotificationPool::socketTextMessageReceived);
        connect(&this->client, &QWebSocket::binaryMessageReceived, this, &MUNotificationPool::socketTextMessageReceived);
        connect(&this->client, &QWebSocket::pong, this, &MUNotificationPool::socketPong);
        connect(&this->client, QOverload<QAbstractSocket::SocketError>::of(&QWebSocket::error), this, &MUNotificationPool::socketError);

        connect(&this->timerPing, &QTimer::timeout, this, &MUNotificationPool::socketPing);
        connect(&this->timerPong, &QTimer::timeout, this, &MUNotificationPool::socketPingTimeOut);
        this->timerPing.setInterval(intervalPing);
        this->timerPong.setInterval(intervalPong);


    }

    void run() {
        if(this->parent==&MUNotification::i()){
// emit this->startTimer(); //NOTE FLAVIO COMENTADO PARA DEPOIS ENTENDER O FUNCIONAMENTO DISSO.
// TÁ CAUSANDO FREEZE NA MAIN GUI
            this->exec();
            this->client.disconnect();
        }
    }

signals:
    void startTimer();

public slots:
    void onStartTimer(){
        this->timerPing.start(0);
    }

    void makeNotification(const QByteArray &message){
        auto payload=QJsonDocument::fromJson(message).toVariant().toMap();
        //auto vPayload=payload.isEmpty()?QVariant(message):QVariant(payload);
        auto type=payload[QStringLiteral("type")];
        auto especification=payload[QStringLiteral("especification")];
        switch (qTypeId(type)){
        case QMetaType_Int:
        case QMetaType_UInt:
        case QMetaType_Double:
        case QMetaType_LongLong:
        case QMetaType_ULongLong:
            type=type.toInt();
            break;
        default:
            if(type.toInt()==0)
                type=int(MUNotificationType::nt_Unknow);
        }
        especification = especification.isValid()?especification:-1;

        emit this->parent->notify(type.toInt(), especification.toInt(), payload);

        switch (type.toInt()) {
        case MUNotificationType::nt_Error:
            emit this->parent->notifyError(especification.toInt(), payload);
            break;
        case MUNotificationType::nt_Fail:
            emit this->parent->notifyFail(especification.toInt(), payload);
            break;
        case MUNotificationType::nt_Network:
            switch (especification.toInt()) {
            case MUNotificationEspecificationNetwork::nsn_OnLine:
                emit this->parent->notifyOnLine(especification.toInt(), payload);
                break;
            case MUNotificationEspecificationNetwork::nsn_OffLine:
                emit this->parent->notifyOffLine(especification.toInt(), payload);
                break;
            case MUNotificationEspecificationNetwork::nsn_ServerOnLine:
                emit this->parent->notifyServerOnLine(especification.toInt(), payload);
                break;
            case MUNotificationEspecificationNetwork::nsn_ServerOffLine:
                emit this->parent->notifyServerOffLine(especification.toInt(), payload);
                break;
            default:
                break;
            }
            emit this->parent->notifyNetwork(especification.toInt(), payload);
            break;
        case MUNotificationType::nt_Security:
            emit this->parent->notifySecurity(especification.toInt(), payload);
            break;
        default:
            break;
        }

        switch (especification.toInt()) {
        case MUNotificationType::nt_Error:
            emit this->parent->notifyError(especification.toInt(), payload);
            break;
        case MUNotificationType::nt_Fail:
            emit this->parent->notifyFail(especification.toInt(), payload);
            break;
        default:
            break;
        }
    }

    void connected()
    {
        this->timerPing.start();
        this->timerPong.stop();
    }

    void disconnected()
    {
        this->timerPing.stop();
        this->timerPong.stop();

    }

    void socketTextMessageReceived(const QString &message)
    {
        this->makeNotification(message.toUtf8());
    }

    void socketBinaryMessageReceived(const QByteArray &message)
    {
        this->makeNotification(message);
    }

    void socketError(QAbstractSocket::SocketError socketError)
    {
        mWarning()<<qsl("websocket error==")<<socketError<<qsl(", ")<<this->client.errorString();
        QThread::sleep(5);
        QTimer::singleShot(1, this, &MUNotificationPool::initConnection);
    }

    void socketPing()
    {
        this->timerPing.stop();
        this->timerPong.start();
        payloadPing=QDateTime::currentDateTime().toString().left(4).toUtf8();
        payloadPong="";
        this->client.ping(payloadPing);
    }

    void socketPong(quint64 elapsedTime, const QByteArray &payload)
    {
        Q_UNUSED(elapsedTime)
        this->timerPong.stop();
        this->timerPing.setInterval(intervalPing);
        this->timerPing.start();
        this->payloadPong=payload;
    }

    void socketPingTimeOut()
    {
        this->timerPing.setInterval(intervalPing);
        this->timerPong.stop();
        this->timerPing.stop();
        if(payloadPing==payloadPong)
            this->timerPing.start();
        else
            this->initConnection();
    }

    bool initConnection()
    {
        if(this->client.isValid())
            this->client.close(QWebSocketProtocol::CloseCodeNormal);
        this->client.open(url);
        this->timerPing.start();

        if(this->client.isValid())
            this->timerPing.setInterval(intervalPing);
        else
            this->timerPing.setInterval(100);

        return this->client.isValid();
    }
};

class Q_MU_EXPORT MUNotificationPvt : public QObject
{
    Q_OBJECT
public:
    MUNotification*parent=nullptr;
    MUNotificationPool*pull=nullptr;
    QString url="localhost";
    Q_INVOKABLE explicit MUNotificationPvt(MUNotification *parent = nullptr) : QObject(parent)
    {
        this->parent=parent;
        this->pull = new MUNotificationPool(this->url,parent);
        this->pull->start();
    }

    ~MUNotificationPvt()
    {
        this->pull->quit();
        if(this->pull->wait(1000))
            delete this->pull;
        else
            this->pull->deleteLater();
    }
};
