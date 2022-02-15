#pragma once

#include <QObject>
#include <QUuid>
#include <QVariant>
#include <QDate>
#include <QVariantList>
#include <QVariantMap>
#include "./mu_global.h"
#include "./mu_object.h"
#include "./mu_login_token.h"
#include "./mu_login_profile.h"

//!
//! \brief The MULoginSession class
//!
class Q_MU_EXPORT MULoginSession : public MUObject
{
    Q_OBJECT
    QML_ELEMENT
public:

    Q_PROPERTY(QUuid           uuid        READ uuid       WRITE set_uuid    NOTIFY loginChanged);
    Q_PROPERTY(QByteArray      hsh_md5     READ hsh_md5    WRITE set_hsh_md5 NOTIFY loginChanged);
    Q_PROPERTY(MULoginProfile* profile     READ profile    WRITE set_profile NOTIFY loginChanged);
    Q_PROPERTY(MULoginToken*   token       READ token      WRITE set_token   NOTIFY loginChanged);

    //!
    //! \brief MULoginSession
    //! \param parent
    //!
    Q_INVOKABLE explicit MULoginSession(QObject *parent = nullptr);
    ~MULoginSession();

    //!
    //! \brief operator =
    //! \param v
    //! \return
    //!
    MULoginSession&operator=(const QVariant&v);

    //!
    //! \brief i
    //! \return
    //!
    static Q_INVOKABLE MULoginSession&i();

    //!
    //! \brief value
    //! \param key
    //! \return
    //!
    Q_INVOKABLE virtual QVariant value(const QString&key) const;

    //!
    //! \brief clear
    //!
    void clear();


    //!
    //! \brief isLogged
    //! \return
    //!
    Q_INVOKABLE virtual bool isLogged() const;

    //!
    //! \brief uuid
    //! \return
    //!
    virtual QUuid uuid() const;
    virtual void set_uuid(const QUuid &value);

    //!
    //! \brief hsh_md5
    //! \return
    //!
    virtual QByteArray hsh_md5() const;
    virtual void set_hsh_md5(const QByteArray &value);

    //!
    //! \brief profile
    //! \return
    //!
    virtual MULoginProfile *profile();
    virtual bool set_profile(const MULoginProfile *v) const;

    //!
    //! \brief token
    //! \return
    //!
    virtual MULoginToken* token();
    virtual bool set_token(const MULoginToken *v) const;

    //!
    //! \brief data
    //! \return
    //!
    Q_INVOKABLE virtual QVariantHash data();
    Q_INVOKABLE virtual bool setData(const QVariant&v);

public slots:

    //!
    //! \brief load
    //! \return
    //!
    Q_INVOKABLE bool load();

    //!
    //! \brief save
    //! \return
    //!
    Q_INVOKABLE bool save();

    //!
    //! \brief logoff
    //! \return
    //!
    Q_INVOKABLE bool logoff();

    //!
    //! \brief verify
    //!
    Q_INVOKABLE void verify();

    //!
    //! \brief verifyData
    //! \return
    //!
    Q_INVOKABLE bool verifyData();


signals:

    //!
    //! \brief invalidData
    //! \param message
    //!
    void invalidData(const QVariant&message);

    //!
    //! \brief loginChanged
    //!
    //!
    void loginChanged();

    //!
    //! \brief loginSuccessful
    //! \param message
    //!
    void loginSuccessful(const QVariant&message);

    //!
    //! \brief loginUnSuccessful
    //! \param message
    //!
    void loginUnSuccessful(const QVariant&message);

    //!
    //! \brief sessionLogged
    //!
    void sessionLogged();

    //!
    //! \brief sessionUnLogged
    //!
    void sessionUnLogged();

    //!
    //! \brief sessionUnAuthorized
    //!
    void sessionUnAuthorized();

    //!
    //! \brief notifyError
    //! \param message
    //!
    void notifyError(const QVariant&message);

    //!
    //! \brief notifyFail
    //! \param message
    //!
    void notifyFail(const QVariant&message);

    //!
    //! \brief notify
    //! \param type
    //! \param especification
    //! \param payload
    //!
    void notify(int type, int especification, const QVariant&payload);

    //!
    //! \brief clientOnLine
    //! \param message
    //!
    void clientOnLine(const QVariant&message);

    //!
    //! \brief clientOffLine
    //! \param message
    //!
    void clientOffLine(const QVariant&message);
private:
    void*p=nullptr;
};
