#include "./p_mu_notification.h"

static const int intervalPing=10000;
static const int intervalPong=5000;

MUNotificationPool::MUNotificationPool(QString url, MUNotification *parent):QThread(nullptr), client(), timerPing()
{
    this->url=url;
    this->parent=parent;

    QObject::connect(&this->client, &QWebSocket::disconnected, &this->client, &QWebSocket::deleteLater);
    QObject::connect(&this->client, &QWebSocket::textMessageReceived, this, &MUNotificationPool::socketTextMessageReceived);
    QObject::connect(&this->client, &QWebSocket::binaryMessageReceived, this, &MUNotificationPool::socketTextMessageReceived);
    QObject::connect(&this->client, &QWebSocket::pong, this, &MUNotificationPool::socketPong);
    QObject::connect(&this->client, QOverload<QAbstractSocket::SocketError>::of(&QWebSocket::error), this, &MUNotificationPool::socketError);

    connect(&this->timerPing, &QTimer::timeout, this, &MUNotificationPool::socketPing);
    connect(&this->timerPong, &QTimer::timeout, this, &MUNotificationPool::socketPingTimeOut);
    this->timerPing.setInterval(intervalPing);
    this->timerPong.setInterval(intervalPong);


}

void MUNotificationPool::run()
{
    if(this->parent!=&MUNotification::i())
        return;
    QTimer::singleShot(10, this, [this](){ this->timerPing.start(0); });
    this->exec();
    this->client.disconnect();
}

void MUNotificationPool::makeNotification(const QByteArray &message)
{
    auto payload=QJsonDocument::fromJson(message).toVariant().toHash();
    //auto vPayload=payload.isEmpty()?QVariant(message):QVariant(payload);
    auto type=payload[qsl("type")];
    auto especification=payload[qsl("especification")];
    type=(type.canConvert(QMetaType_Int)?type.toInt():int(MUNotificationType::nt_Unknow));
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

void MUNotificationPool::connected()
{
    this->timerPing.start();
    this->timerPong.stop();
}

void MUNotificationPool::disconnected()
{
    this->timerPing.stop();
    this->timerPong.stop();

}

void MUNotificationPool::socketTextMessageReceived(const QString &message)
{
    this->makeNotification(message.toUtf8());
}

void MUNotificationPool::socketBinaryMessageReceived(const QByteArray &message)
{
    this->makeNotification(message);
}

void MUNotificationPool::socketError(QAbstractSocket::SocketError socketError)
{
    mWarning()<<qsl("websocket error== %1, %2").arg(qv(socketError).toString(), this->client.errorString());
    QTimer::singleShot(5000, this, &MUNotificationPool::initConnection);
}

void MUNotificationPool::socketPing()
{
    this->timerPing.stop();
    this->timerPong.start();
    payloadPing=QDateTime::currentDateTime().toString().left(4).toUtf8();
    payloadPong="";
    this->client.ping(payloadPing);
}

void MUNotificationPool::socketPong(quint64 elapsedTime, const QByteArray &payload)
{
    Q_UNUSED(elapsedTime)
    this->timerPong.stop();
    this->timerPing.setInterval(intervalPing);
    this->timerPing.start();
    this->payloadPong=payload;
}

void MUNotificationPool::socketPingTimeOut()
{
    this->timerPing.setInterval(intervalPing);
    this->timerPong.stop();
    this->timerPing.stop();
    if(payloadPing==payloadPong)
        this->timerPing.start();
    else
        QTimer::singleShot(1000, this, &MUNotificationPool::initConnection);
}

bool MUNotificationPool::initConnection()
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

MUNotificationPvt::MUNotificationPvt(MUNotification *parent) : QObject(parent)
{
    this->parent=parent;
    this->pull = new MUNotificationPool(this->url,parent);
    this->pull->start();
}

MUNotificationPvt::~MUNotificationPvt()
{
    this->pull->quit();
    if(this->pull->wait(1000))
        delete this->pull;
    else
        this->pull->deleteLater();
    this->pull=nullptr;
}
