#include "./mu_hosting.h"
#include "./mu_routes.h"

namespace QMetaUi{

Q_GLOBAL_STATIC_WITH_ARGS(QByteArray, __method, ("POST"))

#define dPvt()\
    auto&p = *reinterpret_cast<HostingPvt*>(this->p)

class HostingPvt:public QObject{
public:
    Hosting* host = nullptr;
    MUServerLink backendHost;
    MULoginEngineRoutes routes;
    explicit HostingPvt(Hosting*parent=nullptr) : backendHost(parent), routes(parent)
    {
        this->host = parent;
        QObject::connect(&MULoginSession::i(), &MULoginSession::sessionLogged, this, &HostingPvt::onLoginChanged);
        QObject::connect(&MULoginSession::i(), &MULoginSession::sessionUnLogged, this, &HostingPvt::onLoginChanged);
        this->reload();
    }
    virtual ~HostingPvt()
    {
        QObject::disconnect(&MULoginSession::i(), &MULoginSession::sessionLogged, this, &HostingPvt::onLoginChanged);
        QObject::disconnect(&MULoginSession::i(), &MULoginSession::sessionUnLogged, this, &HostingPvt::onLoginChanged);
    }
    void clear()
    {
    }
    void reload()
    {
        this->routes.load();
        auto&backendHost=this->backendHost;
        backendHost.setProtocol(routes.protocol());
        backendHost.setHost(routes.hostName());
        backendHost.setPort(routes.port());
        backendHost.setHeaders(routes.headers());
        backendHost.setMethod( *__method );
    }
public slots:
    void onLoginChanged()
    {
        if (this->host != nullptr)
            emit this->host->headersChanged(this->host->getHeaders());
    }
};

Hosting::Hosting(QObject *parent) : QObject{parent}
{
    this->p = new HostingPvt(this);
}

Hosting::~Hosting()
{
    dPvt();
    delete&p;
}

MUServerLink &Hosting::backendHost()
{
    return this->bh();
}

MUServerLink &Hosting::bh()
{
    dPvt();
    return p.backendHost;
}

MUServerLink &Hosting::bh(const QString &protocol, const QString &host, int port, const QString &route)
{
    return this->bh(protocol, host, port, route, *__method );
}

MUServerLink &Hosting::bh(const QString &protocol, const QString &host, int port, const QString &route, const QString &method)
{
    dPvt();
    if(p.backendHost.protocol().isEmpty())
        p.backendHost.setProtocol(protocol);
    if(p.backendHost.host().isEmpty())
        p.backendHost.setHost(host);
    if(p.backendHost.port()<=0)
        p.backendHost.setPort(port);
    if(p.backendHost.route().isEmpty())
        p.backendHost.setRoute(route);
    if(p.backendHost.method().isEmpty())
        p.backendHost.setMethod(method);
    return p.backendHost;
}

void Hosting::reload()
{
    dPvt();
    p.reload();
}

MUServerLink *Hosting::readReturn(Hosting *parent, MUServerLink *&vv, const QString &endpoint)
{
    return this->readReturn(parent, vv, endpoint, *__method );
}

MUServerLink *Hosting::readReturn(Hosting *parent, MUServerLink *&vv, const QString &endpoint, const QString &method)
{
    parent->reload();
    if(vv==nullptr){
        vv=new MUServerLink(this);
        QObject::connect(this, &Hosting::headersChanged, vv, &MUServerLink::changeHeaders);
        QObject::connect(vv  , &MUServerLink::destroyed, this, &Hosting::disconnectHeaders);
    }
    vv->read(parent->bh().toHash());
    vv->setEndpoint(endpoint);
    vv->setMethod(method);
    vv->setHeaders(this->getHeaders());
    return vv;
}

QVariantHash Hosting::getHeaders()
{
    QVariantHash headers;
    auto&session=MULoginSession::i();
    if (session.isLogged()){
        auto hsh_md5=session.token()->md5();
        headers.insert(QStringLiteral("Authorization"), QStringLiteral("Bearer %1").arg(hsh_md5));
    } else {
        dPvt();
        headers= p.routes.headers();
    }
    return headers;
}

void Hosting::disconnectHeaders(QObject *vv)
{
    if (vv == nullptr)
        return;
    MUServerLink * link = dynamic_cast<MUServerLink*>(vv);
    if (link!=nullptr){
        QObject::disconnect(this, &Hosting::headersChanged, link, &MUServerLink::changeHeaders);
        QObject::disconnect(link , &MUServerLink::destroyed, this, &Hosting::disconnectHeaders);
    }
}

}
