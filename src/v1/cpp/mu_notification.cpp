#include "./mu_notification.h"
#include "./private/p_mu_notification.h"

#define dPvt()\
    auto&p = *reinterpret_cast<MUNotificationPvt*>(this->p)

MUNotification::MUNotification(QObject *parent) : QObject(parent)
{
    this->p = new MUNotificationPvt(this);
}

MUNotification::~MUNotification()
{

}

MUNotification &MUNotification::i()
{
    static MUNotification __i;
    return __i;
}

QVariant MUNotification::notifyPayload(const QVariant &payload)
{
    return this->notifyPayload(0,0,payload);
}

QVariant MUNotification::notifyPayload(int type, const QVariant &payload)
{
    return this->notifyPayload(type,0,payload);
}

QVariant MUNotification::notifyPayload(int type, int especification, const QVariant &payload)
{
    emit notify(type, especification, payload);
    return QVariant();
}
