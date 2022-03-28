#include "./mu_login_engine.h"
#include "./mu_object_util.h"
#include "./mu_string_util.h"
#include "./mu_request.h"
#include <QStm>

#define dPvt()\
    auto&p = *reinterpret_cast<MULoginEnginePvt*>(this->p)


struct MULoginEngineVar{
public:
    MUObjectUtil&objectUtil=MUObjectUtil::i();
    MUStringUtil&stringUtil=MUStringUtil::i();
    QByteArray dig_account;
    QByteArray dig_phone_number;
    QByteArray dig_password;
    QByteArray dig_code;
    QByteArray hsh_code;
    QByteArray hsh_salt;
    QByteArray hsh_md5;

    QVariantHash makeBodyAccount()
    {
        QVariantHash map;
        map.insert(qsl("hsh_account"), hsh_account());
        return map;
    }

    QVariantHash makeBodyAccountCode()
    {
        auto map=makeBodyAccount();
        auto hsh_salt_pwd=this->hsh_salt_pwd();
        auto hsh_salt_code=this->hsh_salt_code();
        auto pwd=(!hsh_salt_pwd.isEmpty())?hsh_salt_pwd:hsh_salt_code;
        map.insert(qsl("hsh_salt_pwd"),pwd);
        return map;
    }

    QVariantHash makeBodySession()
    {
        auto map=makeBodyAccount();
        map.insert(qsl("hsh_md5"), hsh_md5);
        return map;
    }

    QVariantHash makeBodySessionCode()
    {
        auto map=makeBodySession();
        auto hsh_salt_code=this->hsh_salt_code();
        map.insert(qsl("hsh_salt_code"), hsh_salt_code);
        return map;
    }

    void clear()
    {
        this->dig_account.clear();
        this->dig_phone_number.clear();
        this->dig_password.clear();
        this->dig_code.clear();
        this->hsh_code.clear();
        this->hsh_salt.clear();
    }

    QByteArray hsh_salt_calc()
    {
        auto hsh_account=this->hsh_account();
        auto hsh_code=this->hsh_code.trimmed();
        if(hsh_code.isEmpty())
            return hsh_salt;
        return stringUtil.toMd5(hsh_code+hsh_account);
    }
    QByteArray hsh_account()
    {
        return stringUtil.toMd5(this->dig_account);
    }

    QByteArray hsh_salt_pwd()
    {
        auto dig_password=this->stringUtil.toMd5(this->dig_password);
        auto hsh_salt=this->hsh_salt_calc();
        return stringUtil.toMd5(hsh_salt+dig_password);
    }

    QByteArray hsh_salt_code()
    {
        auto hsh_salt=this->hsh_salt_calc();
        return stringUtil.toMd5(hsh_salt+this->hsh_code);
    }
};

class MULoginEnginePvt:public QObject{
public:

    MULoginEngineVar var;

    MUObjectUtil&objectUtil=MUObjectUtil::i();
    MUStringUtil&stringUtil=MUStringUtil::i();
    MULoginEngineRoutes routes;
    MURequest _request;
    MULoginEngine*engine=nullptr;

    bool synchronousRequest=false;
    explicit MULoginEnginePvt(MULoginEngine*parent): QObject(parent), routes(parent), _request(parent)
    {
        this->engine=parent;
        this->routes.load();
    }

    virtual ~MULoginEnginePvt()
    {
    }

    auto&request()
    {
        if(this->synchronousRequest)
            this->_request.setModeSynchronous(MUEnumRequest::mdSync);
        else
            this->_request.setModeSynchronous(MUEnumRequest::mdASync);
        return this->_request;
    }


    void cancel()
    {
        if(!this->_request.isRunning())
            emit engine->loginCancel();
        this->_request.cancel();
    }
public slots:
    void notification(const QVariant&payload)
    {
        auto vHash=payload.toHash();
        auto type=vHash[qsl("type")];
        auto especification=vHash[qsl("especification")];
        auto message=vHash[qsl("message")];
        if(type==MUEnumNotification::nt_Security){
            switch (especification.toInt()){
            case MUEnumNotification::nse_LoginSuccessful:
                emit this->engine->loginSuccessful(message);
                break;
            case MUEnumNotification::nse_Unknow:
                emit this->engine->loginSuccessful(message);
                break;
            case MUEnumNotification::nse_Error:
                emit this->engine->loginError(payload);
                break;
            case MUEnumNotification::nse_Fail:
                emit this->engine->loginFail(payload);
                break;
            default:
                break;
            }
        }
    }
};

MULoginEngine::MULoginEngine(QObject *parent) : QObject{parent}
{
    this->p = new MULoginEnginePvt(this);
    connect(this, &MULoginEngine::loginStarted      ,this, &MULoginEngine::loginMessage);
    connect(this, &MULoginEngine::loginSuccessful   ,this, &MULoginEngine::loginMessage);
    connect(this, &MULoginEngine::loginUnsuccessful ,this, &MULoginEngine::loginMessage);
    connect(this, &MULoginEngine::loginMatch        ,this, &MULoginEngine::loginMessage);
    connect(this, &MULoginEngine::loginError        ,this, &MULoginEngine::loginMessage);
    connect(this, &MULoginEngine::loginFail         ,this, &MULoginEngine::loginMessage);
    connect(this, &MULoginEngine::loginCodeSent     ,this, &MULoginEngine::loginMessage);
}

MULoginEngine::~MULoginEngine()
{
    dPvt();
    delete&p;
}

MULoginEngine &MULoginEngine::i()
{
    static MULoginEngine __i;
    return __i;
}

MULoginSession &MULoginEngine::session()
{
    return MULoginSession::i();
}

bool MULoginEngine::account_match(const QVariant &account)
{
    dPvt();
    p.var.clear();
    p.var.dig_account=account.toByteArray();
    QVariantHash map;
    map.insert(qsl("hsh_account"), p.var.hsh_account());
    p.request().setBody(map);
    auto onOK=[this](const MURequest*){
        emit this->loginMatch(tr("Conta já existe"));
    };
    auto onErr=[this](const MURequest*){
        emit this->loginNotMatch("");
    };
    p.request().start(this->routes().account_match(), onOK, onErr);
    return true;
}

bool MULoginEngine::account_autenticate(const QVariant &account, const QVariant &phone_number)
{
    emit loginStarted(tr("Solicitando código"));
    dPvt();
    p.var.clear();
    p.var.dig_account=account.toByteArray();
    p.var.dig_phone_number=p.stringUtil.toStrPhone(phone_number).toUtf8();
    QVariantMap map;
    map.insert(qsl("hsh_account"), p.var.hsh_account());
    map.insert(qsl("phone_number"), p.var.dig_phone_number);
    p.request().setBody(map);
    auto onOk=[this](const MURequest*){
        emit this->loginCodeSent(tr("Código enviado para seu numero"));
    };
    auto onErr=[this](const MURequest*){
        emit this->loginUnsuccessful(tr("Erro ao enviar código para ativação"));
    };
    p.request().start(this->routes().account_verify(), onOk, onErr);
    return true;
}

bool MULoginEngine::account_autenticate_password(const QVariant &account, const QVariant &password)
{
    emit loginStarted(tr("Autenticando"));
    dPvt();
    p.var.clear();
    p.var.dig_account=account.toByteArray();
    p.var.dig_password=password.toByteArray();

    auto onErr=[this](const MURequest*){
        emit this->loginUnsuccessful(tr("Falha na autenticação"));
    };

    auto doAutho=[&onErr, this](){
        dPvt();
        QVariantHash hash;
        hash.insert(qsl("hsh_account"), p.var.hsh_account());
        hash.insert(qsl("hsh_salt_pwd"), p.var.hsh_salt_pwd());
        p.request().setBody(hash);
        auto onOk=[this](const MURequest*){
            emit this->loginSuccessful(tr("Autenticação concluída"));
        };
        p.request().start(this->routes().account_login(), onOk, onErr);
    };


    QVariantHash hash;
    hash.insert(qsl("hsh_account"), p.stringUtil.toMd5(p.var.hsh_account()));
    p.request().setBody(hash);
    auto onOk=[this, &doAutho](const MURequest*r){
        dPvt();
        auto vBody=r->responseBodyMap();
        p.var.hsh_salt=vBody[qsl("hsh_salt")].toByteArray();
        doAutho();
    };

    p.request().start(this->routes().account_salt(), onOk, onErr);
    return true;
}

bool MULoginEngine::account_autenticate_code(const QVariant &account, const QVariant &code)
{
    emit loginStarted(tr("Autenticando"));
    dPvt();


    p.var.clear();
    p.var.dig_account=account.toByteArray();
    p.var.dig_password=code.toByteArray();
    p.var.dig_code=code.toByteArray().trimmed();
    p.var.hsh_code=p.stringUtil.toMd5(p.var.dig_code);

    if(p.var.dig_code.isEmpty() || p.var.hsh_code.isEmpty())
        emit loginError(tr("Código informado não é valido"));
    else{
        auto hash=p.var.makeBodyAccountCode();
        hash.insert(qsl("hsh_account"), p.var.hsh_account());
        hash.insert(qsl("hsh_salt_pwd"), p.var.hsh_salt_code());
        p.request().setBody(hash);
        auto onOk=[this](const MURequest*r){
            QVariantHash hash;
            hash.insert(qsl("request"), r->body());
            hash.insert(qsl("response"), r->responseBodyMap());
            this->session().setData(hash);
            if(this->session().isLogged())
                emit this->loginSuccessful(tr("Autenticação concluída"));
            else
                emit this->loginUnsuccessful(tr("Dados invalidos"));
        };
        auto onErr=[this](const MURequest*){
            emit this->loginUnsuccessful(tr("Falha na autenticação"));
        };
        p.request().start(this->routes().account_login(), onOk, onErr);
        return true;
    }
    return false;
}

bool MULoginEngine::account_register(const QVariant &account)
{
    auto vBody=account.toHash();

    emit loginStarted(tr("Atualizando dados"));
    dPvt();
    p.var.clear();
    p.var.dig_account=vBody[qsl("account")].toByteArray();
    p.var.dig_password=vBody[qsl("password")].toByteArray();

    auto onErr=[this](const MURequest*){
        emit this->loginUnsuccessful(tr("Falha na atualização"));
    };

    auto doAutho=[&onErr, this](){
        dPvt();
        QVariantHash hash;
        hash.insert(qsl("hsh_account"), p.var.hsh_account());
        hash.insert(qsl("hsh_salt_pwd"), p.var.hsh_salt_pwd());
        p.request().setBody(hash);
        auto onOk=[this](const MURequest*){
            emit this->loginSuccessful(tr("Atualização concluída"));
        };
        p.request().start(this->routes().account_register(), onOk, onErr);
    };


    QVariantHash hash;
    hash.insert(qsl("hsh_account"), p.stringUtil.toMd5(p.var.hsh_account()));
    p.request().setBody(hash);
    auto onOk=[this, &doAutho](const MURequest*r){
        dPvt();
        auto vBody=r->responseBodyMap();
        p.var.hsh_salt=vBody[qsl("hsh_salt")].toByteArray();
        doAutho();
    };

    p.request().start(this->routes().account_salt(), onOk, onErr);
    return true;
}

bool MULoginEngine::account_session_verify()
{
    dPvt();
    auto&session=MULoginSession::i();
    if(!p.request().canStart())
        return false;
    if(!session.isLogged())
        return false;

    if(session.token()->isRecent())
        return false;

    emit loginStarted(tr("Verificando sessão"));
    auto onErr=[this, &session](const MURequest*r){
        if(r->isUnAuthorized()){
            emit this->loginSessionInvalid(tr("Sessão foi desconectada"));
            session.logoff();
        }
    };

    QVariantHash hash;
    hash.insert(qsl("hsh_md5"), session.hsh_md5());
    p.request().setBody(hash);
    p.request().setAuthoBearer(session.hsh_md5());
    auto onOk=[this](const MURequest*){
        emit this->loginSessionIsValid();
    };
    return p.request().start(this->routes().session_check(), onOk, onErr);
    return true;
}

MULoginEngineRoutes&MULoginEngine::routes()
{
    dPvt();
    return p.routes;
}

void MULoginEngine::cancel()
{
    dPvt();
    p.cancel();
}

bool MULoginEngine::isRunning()
{
    dPvt();
    return !p.request().isRunning();
}

bool MULoginEngine::synchronousRequest() const
{
    dPvt();
    return p.synchronousRequest;
}

void MULoginEngine::setSynchronousRequest(bool synchronousRequest)
{
    dPvt();
    p.synchronousRequest = synchronousRequest;
}
