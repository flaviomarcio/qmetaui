#ifndef MUNotification_H
#define MUNotification_H

#include "./mu_global.h"
#include <QObject>
#include <QVariant>

class Q_MU_EXPORT MUNotification : public QObject
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit MUNotification(QObject *parent = nullptr);

    ~MUNotification();

    static Q_INVOKABLE MUNotification&i();

    Q_INVOKABLE QVariant notifyPayload(const QVariant &payload);
    Q_INVOKABLE QVariant notifyPayload(int type, const QVariant &payload);
    Q_INVOKABLE QVariant notifyPayload(int type, int especification, const QVariant &payload);

signals:
    //full notify
    void notify(int type, int especification, const QVariant&payload);

    //notify by type
    void notifySecurity(int especification, const QVariant&payload);
    void notifySales(int especification, const QVariant&payload);
    void notifyPromotion(int especification, const QVariant&payload);
    void notifyError(int especification, const QVariant&payload);
    void notifyFail(int especification, const QVariant&payload);
    void notifyNetwork(int especification, const QVariant&payload);

    //notify by especification
    void notifyServerOnLine(int especification, const QVariant&payload);
    void notifyServerOffLine(int especification, const QVariant&payload);
    void notifyOnLine(int especification, const QVariant&payload);
    void notifyOffLine(int especification, const QVariant&payload);

private:
    void*p=nullptr;
};

#endif // MUNotification_H
