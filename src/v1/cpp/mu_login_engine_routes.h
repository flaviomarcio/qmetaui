#pragma once

#include <QObject>
#include "./mu_global.h"
#include "./mu_routes.h"

//!
//! \brief The MULoginEngineRoutes class
//!
class Q_MU_EXPORT MULoginEngineRoutes:public MURoutes{
    Q_OBJECT
public:

    Q_PROPERTY(QString server           READ server           WRITE setServer           )
    Q_PROPERTY(QString protocol         READ protocol         WRITE setProtocol         )
    Q_PROPERTY(QString hostName         READ hostName         WRITE setHostName         )
    Q_PROPERTY(int     port             READ port             WRITE setPort             )
    Q_PROPERTY(QString account_salt     READ account_salt     WRITE setAccount_salt     )
    Q_PROPERTY(QString account_verify   READ account_verify   WRITE setAccount_verify   )
    Q_PROPERTY(QString account_register READ account_register WRITE setAccount_register )
    Q_PROPERTY(QString account_match    READ account_match    WRITE setAccount_match    )
    Q_PROPERTY(QString session_verify   READ session_verify   WRITE setSession_verify   )
    Q_PROPERTY(QString session_salt     READ session_salt     WRITE setSession_salt     )
    Q_PROPERTY(QString session_check    READ session_check    WRITE setSession_check    )
    Q_PROPERTY(QString account_login    READ account_login    WRITE setSession_login    )

    //!
    //! \brief MULoginEngineRoutes
    //! \param parent
    //!
    Q_INVOKABLE explicit MULoginEngineRoutes(QObject *parent = nullptr);
    ~MULoginEngineRoutes();

    //!
    //! \brief load
    //!
    Q_INVOKABLE virtual void load();
    Q_INVOKABLE virtual void load(const QString &fileName);

    //!
    //! \brief account_salt
    //! \return
    //!
    Q_INVOKABLE virtual QString account_salt() const;
    Q_INVOKABLE virtual void setAccount_salt(const QString &account_salt);

    //!
    //! \brief account_match
    //! \return
    //!
    Q_INVOKABLE virtual QString account_match() const;
    Q_INVOKABLE virtual void setAccount_match(const QString &account_match);

    //!
    //! \brief account_verify
    //! \return
    //!
    Q_INVOKABLE virtual QString account_verify() const;
    Q_INVOKABLE virtual void setAccount_verify(const QString &account_verify);

    //!
    //! \brief account_register
    //! \return
    //!
    Q_INVOKABLE virtual QString account_register() const;
    Q_INVOKABLE virtual void setAccount_register(const QString &account_register);

    //!
    //! \brief account_login
    //! \return
    //!
    Q_INVOKABLE virtual QString account_login() const;
    Q_INVOKABLE virtual void setSession_login(const QString &account_login);

    //!
    //! \brief session_verify
    //! \return
    //!
    Q_INVOKABLE virtual QString session_verify() const;
    Q_INVOKABLE virtual void setSession_verify(const QString &session_verify);

    //!
    //! \brief session_check
    //! \return
    //!
    Q_INVOKABLE virtual QString session_check() const;
    Q_INVOKABLE virtual void setSession_check(const QString &session_check);

    //!
    //! \brief session_salt
    //! \return
    //!
    Q_INVOKABLE virtual QString session_salt() const;
    Q_INVOKABLE virtual void setSession_salt(const QString &session_salt);


private:
    void*p=nullptr;
};
