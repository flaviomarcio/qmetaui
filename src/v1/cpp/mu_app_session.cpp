#include "./mu_app_session.h"
#include "./mu_app_engine_routes.h"
#include "./mu_cache_util.h"
#include "./mu_request.h"

#define dPvt()\
    auto&p = *reinterpret_cast<MUAppSessionPvt*>(this->p)

class MUAppSessionPvt: public QObject {
public:
    bool valid = false;
    int tryGet = 0;

    QVariantHash data;
    MUAppInfo app;
    MUAppSession*session=nullptr;
    MUAppRepository repository;
    MUAppEngineRoutes routes;
    MUCacheUtil&cacheUtil=MUCacheUtil::i();
    MURequest request;

    explicit MUAppSessionPvt(MUAppSession*parent):QObject{parent}, app(parent),repository(parent)
    {
        this->session=parent;
        connect(this->session, &MUAppSession::appRestart       , this, &MUAppSessionPvt::getData);
        connect(this->session, &MUAppSession::errorLoadingInfo , this, &MUAppSessionPvt::errorLoading);
        connect(this->session, &MUAppSession::finishLoadingInfo, this, &MUAppSessionPvt::finishLoading);
    }

    virtual ~MUAppSessionPvt()
    {

    }

    bool load(){
        this->tryGet=0;
#if Q_MU_LOG
        qInfo()<<"App file == "<<cacheUtil.appFileName();
#endif
        auto bytes=cacheUtil.appLoadFile();
        QJsonParseError*parser=nullptr;
        auto doc=QJsonDocument::fromJson(bytes, parser);
        auto map=(parser!=nullptr)?QVariantHash():doc.toVariant().toHash();
        this->setData(map);
        this->getData();
        return requestDataValid();
    }

    bool requestDataValid()
    {
        bool isValid = this->isDataValid();
        if (isValid)
            emit this->session->appStart();
        else
            emit this->session->appRestart();
        return isValid;
    }

    bool save()
    {
        QVariantMap data, response;
        response.insert(QStringLiteral("repository"),this->repository.toHash());
        response.insert(QStringLiteral("app"),this->app.toHash());
        data.insert(QStringLiteral("response"), response);
        return this->save(data);
    }

    void setData(const QVariantHash&v)
    {
        this->data=v;
        auto response=this->data.value(QStringLiteral("response")).toHash();
        this->repository=response.value(QStringLiteral("repository")).toHash();
        this->app=response.value(QStringLiteral("app")).toHash();
    }

    bool save(const QVariant&data)
    {
        auto vMap=data.toHash();
        if(data.canConvert(QVariant::Map) || data.canConvert(QVariant::Hash)){
            if(!vMap.contains(QStringLiteral("response"))){
                if(vMap.contains(QStringLiteral("repository")) && vMap.contains(QStringLiteral("app"))){
                    QVariantHash map;
                    map.insert(QStringLiteral("response"),vMap);
                    vMap=map;
                }
            }
            if(cacheUtil.appSaveFile(vMap)){
                this->setData(vMap);
                return true;
            }
        }
        return false;
    }

    bool isDataValid()
    {
        bool __return = true;
        if (this->app.version().toDouble()<=0)
            __return = false;
        if (this->repository.url().isEmpty())
            __return = false;
        this->valid = __return;
        return __return;
    }

    void cancel()
    {
        if (this->request.isRunning())
            this->request.cancel();
    }

    bool isRunning()
    {
        return this->request.isRunning();
    }

public slots:
    bool getData()
    {
        if (this->request.canStart()){
            emit this->session->startloadingInfo();

            auto onErr=[this](const MURequest*){
                emit this->session->errorLoadingInfo();
            };

            auto onOk=[this](const MURequest*r){
                auto vBody=r->responseBodyMap();
                this->save(vBody);
                emit this->session->finishLoadingInfo();
            };
            this->request.setHeader(this->routes.headers());
            this->request.setMethod(MUEnumRequest::Method::rmGet);
            return this->request.start(this->routes.info(), onOk, onErr);
        }
        return false;
    }

    void errorLoading()
    {
        if (!this->isDataValid()){
            if (this->tryGet<=3){
                this->tryGet++;
                this->getData();
            }
            return;
        }
        emit this->session->appStart();
    }

    void finishLoading()
    {
        if (this->isDataValid()){
            emit this->session->appStart();
        }
    }
};

MUAppSession::MUAppSession(QObject *parent) : MUObject(parent)
{
    auto p = new MUAppSessionPvt(this);
    if (p)
        p->routes.load();
    this->p = p;
}

MUAppSession::~MUAppSession()
{
    dPvt();
    delete&p;
}

MUAppSession &MUAppSession::i()
{
    static MUAppSession __i;
    return __i;
}

bool MUAppSession::load()
{
    dPvt();
    return p.load();
}

bool MUAppSession::save()
{
    dPvt();
    return p.save();
}

QVariantHash MUAppSession::data()
{
    dPvt();
    return p.data;
}

bool MUAppSession::setData(const QVariant &v)
{
    dPvt();
    return p.save(v);
}

bool MUAppSession::getData()
{
    dPvt();
    return p.getData();
}

MUAppRepository *MUAppSession::repository() const
{
    dPvt();
    return &p.repository;
}

bool MUAppSession::set_repository(MUAppRepository *v)
{
    Q_UNUSED(v)
    return false;
}

MUAppInfo *MUAppSession::app() const
{
    dPvt();
    return &p.app;
}

bool MUAppSession::set_app(MUAppInfo *v)
{
    Q_UNUSED(v)
    return false;
}

MUAppSession &MUAppSession::operator=(const QVariant &v)
{
    auto map=v.toMap();
    auto metaObject=this->metaObject();
    for(int i = 0; i < metaObject->propertyCount(); ++i) {
        auto property=metaObject->property(i);
        auto v=map.value(property.name());
        property.write(this,v);
    }
    return*this;
}
