#include "./mu_routes.h"
#include "./mu_object_util.h"
#include "./mu_string_util.h"
#include "./mu_request.h"
#include <QFile>
#include <QStm>
#include <QBitArray>

#define dPvt()\
    auto&p = *reinterpret_cast<MURoutesPvt*>(this->p)

class MURoutesPvt:public QObject{
public:
    QString fileNameLoaded;
    QVariantHash settingsMap;
    MUObjectUtil&objectUtil=MUObjectUtil::i();
    MUStringUtil&stringUtil=MUStringUtil::i();
    QString server;
    QVariantHash server_headers;
    QString server_protocol=qsl("http");
    QString server_hostname=qsl("localhost");
    int server_port=80;
    QVariantMap server_route;
    MURoutes*parent=nullptr;
    explicit MURoutesPvt(MURoutes*parent):QObject(parent){
        this->parent=parent;
    }
    virtual ~MURoutesPvt(){
    }

    void clear(){
        fileNameLoaded="";
        auto metaObject=this->parent->metaObject();
        for(int i = 0; i < metaObject->propertyCount(); ++i) {
            auto property=metaObject->property(i);
            switch (qTypeId(property)){
            case QMetaType_QString:
                property.write(this->parent, QString{});
                break;
            case QMetaType_QByteArray:
                property.write(this->parent, QByteArray{});
                break;
            case QMetaType_QChar:
                property.write(this->parent, QChar{});
                break;
            case QMetaType_QBitArray:
                property.write(this->parent, QBitArray{});
                break;
            case QMetaType_Double:
            case QMetaType_Int:
            case QMetaType_UInt:
            case QMetaType_LongLong:
            case QMetaType_ULongLong:
                property.write(this->parent,0);
                break;
            case QMetaType_QDate:
                property.write(this->parent,QDate{});
                break;
            case QMetaType_QTime:
                property.write(this->parent,QTime{});
                break;
            case QMetaType_QDateTime:
                property.write(this->parent,QDateTime{});
                break;
            case QMetaType_Bool:
                property.write(this->parent,false);
                break;
            case QMetaType_QUuid:
                property.write(this->parent,QUuid{});
                break;
            case QMetaType_QUrl:
                property.write(this->parent,QUrl{});
                break;
            default:
                property.write(this->parent,QVariant{});
            }
        }
    }

    void load(const QString&fileName){
        QFile file(fileName.trimmed());
        if(!file.exists()){
            file.setFileName(qsl(":/qmetaui.json"));
            if(file.exists() && file.open(QFile::ReadOnly)){
#ifdef QT_DEBUG
                QString enviroment=qsl("debug");
#else
                QString enviroment="release";
#endif
                auto vMap=QJsonDocument::fromJson(file.readAll()).toVariant().toHash();
                file.close();
                auto setting=vMap.value(qsl("settings")).toHash();
                if(!vMap.isEmpty()){
                    auto envMap=setting.value(enviroment).toHash();
                    file.setFileName(envMap.value(qsl("filename")).toString());
                }

#if Q_MU_LOG_SUPER_VERBOSE
        qInfo()<<"Routes file == "<<file.fileName();
#endif
            }
        }
        settingsMap.clear();
        if(file.exists()){
            this->fileNameLoaded=file.fileName();
            this->settingsMap=stringUtil.loadFileMap(file.fileName()).toHash();

            auto metaUiV1=settingsMap.value(qsl("v1")).toHash();
            if(!metaUiV1.isEmpty()){
                auto settings=metaUiV1.value(qsl("settings")).toHash();
                if(!settings.isEmpty()){
                    this->server_headers = settings.value(qsl("headers")).toHash();
                    this->server_protocol = settings.value(qsl("protocol")).toString().trimmed();
                    this->server_hostname = settings.value(qsl("hostName")).toString().trimmed();
                    if(this->server_hostname.isEmpty())
                        this->server_hostname = settings.value(qsl("hostname")).toString();
                    this->server_port = settings.value(qsl("port")).toInt();
                    auto _server_route=settings.value(qsl("route")).toHash();
                    this->server = qsl("%1://%2:%3").arg(server_protocol, server_hostname).arg(server_port);

                    this->server_route.clear();
                    QHashIterator<QString, QVariant> i(_server_route);
                    while (i.hasNext()) {
                        i.next();
                        auto key=i.key();
                        auto&value=i.value();
                        if(key.toLower().trimmed()==qsl("authorization"))
                            key=qsl("Authorization");
                        this->server_route.insert(key, value);
                    }
                }
            }

            this->server_protocol = stringUtil.isEmptySet(this->server_protocol          , qsl("http")).toString();
            this->server_hostname = stringUtil.isEmptySet(this->server_hostname          , qsl("localhost")).toString();
            this->server_port     = this->server_port>0?this->server_port:80;
        }
    }
};


MURoutes::MURoutes(QObject *parent):QObject(parent)
{
    this->p=new MURoutesPvt(this);
}

MURoutes::~MURoutes()
{
    dPvt();
    delete&p;
}

QString MURoutes::fileNameLoaded()
{
    dPvt();
    return p.fileNameLoaded;
}

void MURoutes::load()
{
    dPvt();
    p.load("");
}

void MURoutes::load(const QString&fileName)
{
    dPvt();
    p.load(fileName);
}

QVariantHash &MURoutes::settingsMap()
{
    dPvt();
    return p.settingsMap;
}

void MURoutes::clear()
{
    dPvt();
    p.clear();
}

QString MURoutes::server() const
{
    dPvt();
    return p.server;
}

void MURoutes::setServer(const QString &value)
{
    dPvt();
    p.server = value;
}

QVariantHash MURoutes::headers() const
{
    dPvt();
    return p.server_headers;
}

void MURoutes::setHeaders(const QVariantHash &value)
{
    dPvt();
    p.server_headers=value;
}

QString MURoutes::protocol() const
{
    dPvt();
    return p.server_protocol;
}

void MURoutes::setProtocol(const QString &value)
{
    dPvt();
    p.server_protocol=value;
}

QString MURoutes::hostName() const
{
    dPvt();
    return p.server_hostname;
}

void MURoutes::setHostName(const QString &value)
{
    dPvt();
    p.server_hostname=value;
}

int MURoutes::port() const
{
    dPvt();
    return p.server_port;
}

void MURoutes::setPort(const QVariant &value)
{
    dPvt();
    p.server_port=value.toInt();
}

QVariantMap MURoutes::route() const
{
    dPvt();
    return p.server_route;
}

void MURoutes::setRoute(const QVariantMap &value)
{
    dPvt();
    p.server_route=value;
}
