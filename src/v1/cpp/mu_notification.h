#pragma once

#include "./mu_global.h"
#include <QObject>
#include <QVariant>

//!
//! \brief The MUNotification class
//!
class Q_MU_EXPORT MUNotification : public QObject
{
    Q_OBJECT
public:

    //!
    //! \brief MUNotification
    //! \param parent
    //!
    Q_INVOKABLE explicit MUNotification(QObject *parent = nullptr);
    ~MUNotification();

    //!
    //! \brief i
    //! \return
    //!
    static Q_INVOKABLE MUNotification&i();

    //!
    //! \brief notifyPayload
    //! \param payload
    //! \return
    //!
    Q_INVOKABLE QVariant notifyPayload(const QVariant &payload);
    Q_INVOKABLE QVariant notifyPayload(int type, const QVariant &payload);
    Q_INVOKABLE QVariant notifyPayload(int type, int especification, const QVariant &payload);

signals:

    //!
    //! \brief notify
    //! \param type
    //! \param especification
    //! \param payload
    //! all notify
    void notify(int type, int especification, const QVariant&payload);

    //notify by type

    //!
    //! \brief notifySecurity
    //! \param especification
    //! \param payload
    //!
    void notifySecurity(int especification, const QVariant&payload);

    //!
    //! \brief notifySales
    //! \param especification
    //! \param payload
    //!
    void notifySales(int especification, const QVariant&payload);

    //!
    //! \brief notifyPromotion
    //! \param especification
    //! \param payload
    //!
    void notifyPromotion(int especification, const QVariant&payload);

    //!
    //! \brief notifyError
    //! \param especification
    //! \param payload
    //!
    void notifyError(int especification, const QVariant&payload);

    //!
    //! \brief notifyFail
    //! \param especification
    //! \param payload
    //!
    void notifyFail(int especification, const QVariant&payload);

    //!
    //! \brief notifyNetwork
    //! \param especification
    //! \param payload
    //!
    void notifyNetwork(int especification, const QVariant&payload);

    //notify by especification

    //!
    //! \brief notifyServerOnLine
    //! \param especification
    //! \param payload
    //!
    void notifyServerOnLine(int especification, const QVariant&payload);

    //!
    //! \brief notifyServerOffLine
    //! \param especification
    //! \param payload
    //!
    void notifyServerOffLine(int especification, const QVariant&payload);

    //!
    //! \brief notifyOnLine
    //! \param especification
    //! \param payload
    //!
    void notifyOnLine(int especification, const QVariant&payload);

    //!
    //! \brief notifyOffLine
    //! \param especification
    //! \param payload
    //!
    void notifyOffLine(int especification, const QVariant&payload);

private:
    void*p=nullptr;
};
