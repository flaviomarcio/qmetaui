#pragma once

#include <QObject>
#include "./mu_login_session.h"
#include "./mu_login_engine_routes.h"
#include "./mu_global.h"

class Q_MU_EXPORT MULoginEngine : public QObject
{
    Q_OBJECT
public:

    Q_INVOKABLE explicit MULoginEngine(QObject *parent = nullptr);
    ~MULoginEngine();

    static Q_INVOKABLE MULoginEngine&i();
    Q_INVOKABLE static MULoginSession&session();

    Q_INVOKABLE virtual bool account_match(const QVariant &account);
    Q_INVOKABLE virtual bool account_autenticate(const QVariant &account, const QVariant &phone_number);
    Q_INVOKABLE virtual bool account_autenticate_password(const QVariant &account, const QVariant &password);
    Q_INVOKABLE virtual bool account_autenticate_code(const QVariant &account, const QVariant &code);
    Q_INVOKABLE virtual bool account_register(const QVariant&account);

    Q_INVOKABLE virtual bool account_session_verify();

    Q_INVOKABLE virtual MULoginEngineRoutes &routes();

    Q_INVOKABLE virtual void cancel();

    Q_INVOKABLE virtual bool isRunning();

    bool synchronousRequest() const;
    void setSynchronousRequest(bool synchronousRequest);

signals:
    /**
     * @brief loginClear
     */
    void loginClear();

    /**
     * @brief loginStarted
     * @param message
     * toda acao de request vai disparar aqui
     */
    void loginStarted(const QVariant&message);

    /**
     * @brief loginSuccessful
     * @param message
     * se a acao de autenticacao do usuário for bem feita vai disparar aqui
     */
    void loginSuccessful(const QVariant&message);

    /**
     * @brief loginUnsuccessful
     * @param message
     * se a acao de autenticacao do usuário falhar vai disparar aqui
     */
    void loginUnsuccessful(const QVariant&message);

    /**
     * @brief loginSessionIsValid
     *
     * informa que a sessao verificada é valida
     */
    void loginSessionIsValid();

    /**
     * @brief loginSessionInvalid
     *
     * informa que a sessao nao foi valida remotamente
     */
    void loginSessionInvalid(QString message);

    /**
     * @brief loginMatch
     * @param message
     * se verificar existencia de uma conta e encontrar vai disparar aqui
     */
    void loginMatch(QString message);

    /**
     * @brief loginNotMatch
     * @param message
     * se verificar existencia de uma conta e nao encontrar vai disparar aqui
     */
    void loginNotMatch(const QVariant&message);

    /**
     * @brief loginError
     * @param message
     * mensagem especifica de erro
     */
    void loginError(const QVariant&message);

    /**
     * @brief loginFail
     * @param message
     * mensagem especifica de fail
     */
    void loginFail(const QVariant&message);

    /**
     * @brief loginMessage
     * @param message
     * qualquer mensagem enviada vai disparar aqui
     */
    void loginMessage(const QVariant&message);

    /**
     * @brief loginCancel
     * informa quando a operacao foi cancelada
     */
    void loginCancel();

    /**
     * @brief loginCodeSent
     * @param message
     * informa quando codigo foi enviado
     */
    void loginCodeSent(const QVariant&message);
private:
    void*p=nullptr;
};
