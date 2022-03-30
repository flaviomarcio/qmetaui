#include "./mu_login_engine_routes.h"
#include "./mu_object_util.h"
#include "./mu_string_util.h"
#include "./mu_request.h"

#define dPvt()\
    auto&p = *reinterpret_cast<MULoginEngineRoutesPvt*>(this->p)

class MULoginEngineRoutesPvt:public QObject{
public:
    MUStringUtil&stringUtil=MUStringUtil::i();
    MUVariantUtil&variantUtil=MUVariantUtil::i();
    QString account_match   ;
    QString account_salt    ;
    QString account_verify  ;
    QString account_register;
    QString account_login   ;
    QString session_verify  ;
    QString session_check   ;
    QString session_salt    ;

    MULoginEngineRoutes*parent=nullptr;
    explicit MULoginEngineRoutesPvt(MULoginEngineRoutes*parent):QObject{parent}{
        this->parent=parent;
    }
    virtual ~MULoginEngineRoutesPvt(){
    }

    void load(){
        auto aclRoute=this->parent->route().value("acl").toMap();

        auto route_account_register = aclRoute.value(QStringLiteral("account_reg"     ));
        auto route_account_match    = aclRoute.value(QStringLiteral("account_match"   ));
        auto route_account_verify   = aclRoute.value(QStringLiteral("account_verify"  ));
        auto route_account_salt     = aclRoute.value(QStringLiteral("account_salt"    ));
        auto route_account_login    = aclRoute.value(QStringLiteral("account_login"   ));
        auto route_session_verify   = aclRoute.value(QStringLiteral("session_verify"  ));
        auto route_session_check    = aclRoute.value(QStringLiteral("session_check"   ));
        auto route_session_salt     = aclRoute.value(QStringLiteral("session_salt"    ));

        route_account_register = stringUtil.isEmptySet(route_account_register , QStringLiteral("/v1/acl/account/reg")).toString();
        route_account_match    = stringUtil.isEmptySet(route_account_match    , QStringLiteral("/v1/acl/account/match")).toString();
        route_account_verify   = stringUtil.isEmptySet(route_account_verify   , QStringLiteral("/v1/acl/account/verify")).toString();
        route_account_salt     = stringUtil.isEmptySet(route_account_salt     , QStringLiteral("/v1/acl/account/salt")).toString();
        route_account_login    = stringUtil.isEmptySet(route_account_login    , QStringLiteral("/v1/acl/account/login")).toString();
        route_session_verify   = stringUtil.isEmptySet(route_session_verify   , QStringLiteral("/v1/acl/session/verify")).toString();
        route_session_check    = stringUtil.isEmptySet(route_session_check    , QStringLiteral("/v1/acl/session/check")).toString();
        route_session_salt     = stringUtil.isEmptySet(route_session_salt     , QStringLiteral("/v1/acl/session/salt")).toString();

        auto server=this->parent->server();
        this->account_register = QStringLiteral("%1%2").arg(server, route_account_register.toString() );
        this->account_match    = QStringLiteral("%1%2").arg(server, route_account_match   .toString() );
        this->account_verify   = QStringLiteral("%1%2").arg(server, route_account_verify  .toString() );
        this->account_login    = QStringLiteral("%1%2").arg(server, route_account_login   .toString() );
        this->account_salt     = QStringLiteral("%1%2").arg(server, route_session_salt    .toString() );
        this->session_verify   = QStringLiteral("%1%2").arg(server, route_session_verify  .toString() );
        this->session_check    = QStringLiteral("%1%2").arg(server, route_session_check   .toString() );
        this->session_salt     = QStringLiteral("%1%2").arg(server, route_session_salt    .toString() );
    }

};

MULoginEngineRoutes::MULoginEngineRoutes(QObject *parent):MURoutes(parent)
{
    this->p=new MULoginEngineRoutesPvt(this);
}

MULoginEngineRoutes::~MULoginEngineRoutes()
{
    dPvt();
    delete&p;
}

void MULoginEngineRoutes::load()
{
    MURoutes::load();
    dPvt();
    p.load();
}

void MULoginEngineRoutes::load(const QString &fileName)
{
    MURoutes::load(fileName);
    dPvt();
    p.load();
}

QString MULoginEngineRoutes::account_salt() const
{
    dPvt();
    return p.account_salt;
}

void MULoginEngineRoutes::setAccount_salt(const QString &account_salt)
{
    dPvt();
    p.account_salt = account_salt;
}

QString MULoginEngineRoutes::account_match() const
{
    dPvt();
    return p.account_match;
}

void MULoginEngineRoutes::setAccount_match(const QString &account_match)
{
    dPvt();
    p.account_match=account_match;
}

QString MULoginEngineRoutes::account_verify() const
{
    dPvt();
    return p.account_verify;
}

void MULoginEngineRoutes::setAccount_verify(const QString &account_verify)
{
    dPvt();
    p.account_verify = account_verify;
}

QString MULoginEngineRoutes::account_register() const
{
    dPvt();
    return p.account_register;
}

void MULoginEngineRoutes::setAccount_register(const QString &account_register)
{
    dPvt();
    p.account_register = account_register;
}

QString MULoginEngineRoutes::session_verify() const
{
    dPvt();
    return p.session_verify;
}

void MULoginEngineRoutes::setSession_verify(const QString &session_verify)
{
    dPvt();
    p.session_verify = session_verify;
}

QString MULoginEngineRoutes::session_check() const
{
    dPvt();
    return p.session_check;
}

void MULoginEngineRoutes::setSession_check(const QString &session_check)
{
    dPvt();
    p.session_check = session_check;
}

QString MULoginEngineRoutes::session_salt() const
{
    dPvt();
    return p.session_salt;
}

void MULoginEngineRoutes::setSession_salt(const QString &session_salt)
{
    dPvt();
    p.session_salt = session_salt;
}

QString MULoginEngineRoutes::account_login() const
{
    dPvt();
    return p.account_login;
}

void MULoginEngineRoutes::setSession_login(const QString &account_login)
{
    dPvt();
    p.account_login = account_login;
}
