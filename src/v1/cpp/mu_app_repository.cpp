#include "./mu_app_repository.h"
#include <QString>

#define dPvt()\
    auto&p = *reinterpret_cast<MUAppRepositoryPvt*>(this->p)

class MUAppRepositoryPvt:public QObject{
public:

    QVariantMap headers;
    QString     url;
    QString     hostName;
    QString     method;
    QVariant    protocol;
    int         port;
    QString     route;

    MUAppRepository*parent=nullptr;
    explicit MUAppRepositoryPvt(MUAppRepository*parent):QObject{parent}{
        this->parent=parent;
    }

    virtual ~MUAppRepositoryPvt(){

    }

    void setUrl()
    {
        QString localurl;
        hostName=hostName.trimmed();        
        if (!hostName.isEmpty()){
            localurl.append(hostName);
            route=route.trimmed();
            if (port>0){
                localurl.append(QStringLiteral(":%1").arg(port));
            }
            if (!route.isEmpty()){
                localurl.append(QStringLiteral("/%3").arg(route));
            }

            while(localurl.contains(QStringLiteral("//")))
                localurl=localurl.replace(QStringLiteral("//"), QStringLiteral("/"));

            protocol = protocol.toString().trimmed();
            if (!protocol.toString().isEmpty()){
                localurl.prepend(QStringLiteral("%1://").arg(protocol.toString()));
            }

            url = localurl;
        }
    }
};

MUAppRepository::MUAppRepository(QObject *parent) : MUObject(parent)
{
    this->p=new MUAppRepositoryPvt(this);
}

MUAppRepository::~MUAppRepository()
{
    dPvt();
    delete&p;
}

MUAppRepository &MUAppRepository::operator=(const MUAppRepository &v)
{
    this->fromHash(v.toHash());
    dPvt();
    p.setUrl();
    return*this;
}

MUAppRepository &MUAppRepository::operator=(const QVariant &v)
{
    this->fromHash(v.toHash());
    dPvt();
    p.setUrl();
    return*this;
}
bool MUAppRepository::isValid()
{
    return !this->url().isEmpty();
}

QVariantMap MUAppRepository::headers() const
{
    dPvt();
    return p.headers;
}

void MUAppRepository::setHeaders(const QVariantMap &v)
{
    dPvt();
    p.headers = v;
}

QString MUAppRepository::url() const
{
    dPvt();
    return p.url;
}


QVariant MUAppRepository::parserUrl(const QVariant &v)const
{
    dPvt();
    auto sss = v.toString().trimmed();
    if(sss.isEmpty())
        return "";

    QString url = p.url;
    if(url.contains(QStringLiteral("{md5}")))
        url = url.replace(QStringLiteral("{md5}"),sss);
    else
        url = QStringLiteral("%1/%2").arg(p.url,sss);
    return url;
}

QString MUAppRepository::hostName() const
{
    dPvt();
    return p.hostName;
}

void MUAppRepository::setHostName(const QString &hostName)
{
    dPvt();
    p.hostName = hostName;
}

QString MUAppRepository::method() const
{
    dPvt();
    return p.method;
}

void MUAppRepository::setMethod(const QString &method)
{
    dPvt();
    p.method = method;
}

QVariant MUAppRepository::protocol() const
{
    dPvt();
    return p.protocol;
}

void MUAppRepository::setProtocol(const QVariant &protocol)
{
    dPvt();
    p.protocol = protocol;
}

int MUAppRepository::port() const
{
    dPvt();
    return p.port;
}

void MUAppRepository::setPort(int port)
{
    dPvt();
    p.port = port;
}

QString MUAppRepository::route() const
{
    dPvt();
    return p.route;
}

void MUAppRepository::setRoute(const QString &route)
{
    dPvt();
    p.route = route;
}
