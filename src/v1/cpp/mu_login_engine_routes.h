#pragma once

#include <QObject>
#include "./mu_global.h"
#include "./mu_routes.h"

class Q_MU_EXPORT MULoginEngineRoutes:public MURoutes{
    Q_OBJECT
public:

    Q_PROPERTY(QString server READ server WRITE setServer NOTIFY serverChanged)
    Q_PROPERTY(QString protocol READ protocol WRITE setProtocol NOTIFY protocolChanged)
    Q_PROPERTY(QString hostName READ hostName WRITE setHostName NOTIFY hostNameChanged)
    Q_PROPERTY(int port READ port WRITE setPort NOTIFY portChanged)
    Q_PROPERTY(QString account_salt READ account_salt WRITE setAccount_salt NOTIFY account_saltChanged)
    Q_PROPERTY(QString account_verify READ account_verify WRITE setAccount_verify NOTIFY account_verifyChanged)
    Q_PROPERTY(QString account_register READ account_register WRITE setAccount_register NOTIFY account_registerChanged)
    Q_PROPERTY(QString account_match READ account_match WRITE setAccount_match NOTIFY account_matchChanged)
    Q_PROPERTY(QString session_verify READ session_verify WRITE setSession_verify NOTIFY session_verifyChanged)
    Q_PROPERTY(QString session_salt READ session_salt WRITE setSession_salt NOTIFY session_saltChanged)
    Q_PROPERTY(QString session_check READ session_check WRITE setSession_check NOTIFY session_checkChanged)
    Q_PROPERTY(QString account_login READ account_login WRITE setSession_login NOTIFY account_loginChanged)


    Q_INVOKABLE explicit MULoginEngineRoutes(QObject *parent = nullptr);
    ~MULoginEngineRoutes();

    Q_INVOKABLE virtual void load();
    Q_INVOKABLE virtual void load(const QString &fileName);

    /**
     * @brief account_salt
     * @return
     */
    Q_INVOKABLE virtual QString account_salt() const;
    Q_INVOKABLE virtual void setAccount_salt(const QString &account_salt);

    /**
     * @brief account_match
     * @return
     */
    Q_INVOKABLE virtual QString account_match() const;
    Q_INVOKABLE virtual void setAccount_match(const QString &account_match);

    /**
     * @brief account_verify
     * @return
     */
    Q_INVOKABLE virtual QString account_verify() const;
    Q_INVOKABLE virtual void setAccount_verify(const QString &account_verify);

    /**
     * @brief account_register
     * @return
     */
    Q_INVOKABLE virtual QString account_register() const;
    Q_INVOKABLE virtual void setAccount_register(const QString &account_register);

    /**
     * @brief account_login
     * @return
     */
    Q_INVOKABLE virtual QString account_login() const;
    Q_INVOKABLE virtual void setSession_login(const QString &account_login);

    /**
     * @brief session_verify
     * @return
     */
    Q_INVOKABLE virtual QString session_verify() const;
    Q_INVOKABLE virtual void setSession_verify(const QString &session_verify);

    /**
     * @brief session_ping
     * @return
     */
    Q_INVOKABLE virtual QString session_check() const;
    Q_INVOKABLE virtual void setSession_check(const QString &session_check);

    /**
     * @brief session_salt
     * @return
     */
    Q_INVOKABLE virtual QString session_salt() const;
    Q_INVOKABLE virtual void setSession_salt(const QString &session_salt);


private:
    void*p=nullptr;

signals:
    void serverChanged();
    void protocolChanged();
    void hostNameChanged();
    void portChanged();
    void account_saltChanged();
    void account_verifyChanged();
    void account_registerChanged();
    void account_matchChanged();
    void session_verifyChanged();
    void session_saltChanged();
    void session_checkChanged();
    void account_loginChanged();

};
