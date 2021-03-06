#include "./mu_server_link.h"
#include <QNetworkAccessManager>
#include <QMetaProperty>

#define dPvt()\
    auto&p = *reinterpret_cast<MUServerLinkPvt*>(this->p)

class MUServerLinkPvt
{
public:
    QVariantHash headers;
    QString protocol="";
    QString method="";
    QString host="";
    int port=-1;
    QString route="";
    QString endpoint="";

    explicit MUServerLinkPvt(){
    }

    virtual ~MUServerLinkPvt(){
    }
};


MUServerLink::MUServerLink(QObject *parent) : QObject{parent}
{
    this->p = new MUServerLinkPvt();
}

//MUServerLink::MUServerLink(MUServerLink &link, QObject *parent) : QObject{parent}
//{
//    this->p = new MUServerLinkPvt();
//    this->read(link.toMap());
//}

MUServerLink::~MUServerLink(){
    dPvt();
    delete&p;
}

QVariant MUServerLink::toMap()const
{
    QVariantHash map;
    for(int i = 0; i < this->metaObject()->propertyCount(); ++i) {
        auto property=this->metaObject()->property(i);
        map.insert(property.name(), property.read(this));
    }
    return map;
}

QString MUServerLink::url() const
{
    auto sprot=this->protocol().trimmed();
    auto shost=this->host().trimmed();
    auto sport=this->port()<=0?"":QString::number(this->port());
    auto sroute=this->route().trimmed();
    auto sendpoint=this->endpoint().trimmed();

    if(sprot.isEmpty() || shost.isEmpty())
        return QString();

    auto url = QStringLiteral("%1:||%2:%3/%4/%5").arg(sprot).arg(shost, sport, sroute, sendpoint);
    while(url.contains(QStringLiteral("//")))
        url=url.replace(QStringLiteral("//"), QStringLiteral("/"));
    return url.replace(QStringLiteral(":||"), QStringLiteral("://"));

}

bool MUServerLink::read(const QVariant &link)
{
    if(link.canConvert(QVariant::Map)){
        auto map=link.toMap();
        for(int i = 0; i < this->metaObject()->propertyCount(); ++i) {
            auto property=this->metaObject()->property(i);
            property.write(this, map.value(property.name()));
        }
        return true;
    }
    return false;
}

QVariantHash&MUServerLink::headers()
{
    dPvt();
    return p.headers;
}

void MUServerLink::setHeaders(const QVariantHash &value)
{
    dPvt();
    p.headers = value;
}

QString MUServerLink::hash()
{
    return QCryptographicHash::hash(this->url().toUtf8(), QCryptographicHash::Md5).toHex();
}

QString MUServerLink::protocol() const
{
    dPvt();
    return p.protocol;
}

void MUServerLink::setProtocol(const QString &value)
{
    dPvt();
    p.protocol = QString(value).replace("\"","");
}

QString MUServerLink::host() const
{
    dPvt();
    return p.host;
}

void MUServerLink::setHost(const QString &value)
{
    dPvt();
    p.host = QString(value).replace("\"","");
}

int MUServerLink::port() const
{
    dPvt();
    return p.port;
}

void MUServerLink::setPort(const QVariant &value)
{
    dPvt();
    p.port = value.toInt();
}

QString MUServerLink::route() const
{
    dPvt();
    return p.route;
}

void MUServerLink::setRoute(const QString &value)
{
    dPvt();
    p.route = QString(value).replace("\"","");
}

QString MUServerLink::endpoint() const
{
    dPvt();
    auto endpoint=p.endpoint.trimmed();
    endpoint = endpoint.isEmpty()?"":QStringLiteral("/%1").arg(endpoint).replace("//","/");
    return endpoint;
}

void MUServerLink::setEndpoint(const QString &value)
{
    dPvt();
    auto endpoint=QString(value).replace("\"","").trimmed();
    p.endpoint = endpoint;
}

MUServerLink &MUServerLink::setValues(const QVariant &protocol, const QVariant &host, const QVariant &port, const QVariant &route, const QVariant &method)
{
    this->setProtocol(protocol.toString());
    this->setHost(host.toString());
    this->setPort(port.toInt());
    this->setRoute(route.toString());
    this->setMethod(method.toString());
    return*this;
}

MUServerLink &MUServerLink::setValues(MUServerLink *value)
{
    this->setProtocol(value->protocol());
    this->setHost(value->host());
    this->setPort(value->port());
    this->setRoute(value->route());
    this->setMethod(value->method());
    return*this;
}

MUServerLink &MUServerLink::operator=(const MUServerLink &link)
{
    auto&_link=*this;
    if(&link!=&_link){
        auto metaObject=link.metaObject();
        for(int i = 0; i < metaObject->propertyCount(); ++i) {
            auto property=metaObject->property(i);
            auto v=property.read(&link);
            property.write(&_link,v);
        }
    }
    return*this;
}

void MUServerLink::changeHeaders(const QVariantHash &value)
{
    this->setHeaders(value);
    emit this->changedHeaders();
}

QString MUServerLink::method() const
{
    dPvt();
    return p.method;
}

void MUServerLink::setMethod(const QString &method)
{
    dPvt();
    p.method = method;
}
