#include "./mu_app_engine_routes.h"
#include "./mu_object_util.h"
#include "./mu_string_util.h"
#include "./mu_request.h"

#define dPvt()\
    auto&p = *reinterpret_cast<MUAppEngineRoutesPvt*>(this->p)

class MUAppEngineRoutesPvt:public QObject{
public:
    MUStringUtil&stringUtil=MUStringUtil::i();
    MUVariantUtil&variantUtil=MUVariantUtil::i();
    QString info;
    MUAppEngineRoutes*parent=nullptr;
    explicit MUAppEngineRoutesPvt(MUAppEngineRoutes*parent):QObject(parent)
    {
        this->parent=parent;      
    }

    virtual ~MUAppEngineRoutesPvt()
    {
    }

    void load(){
        auto appRoute=this->parent->route().value(QStringLiteral("magma/app")).toMap();
        auto route_info = appRoute.value(QStringLiteral("info"));
        route_info = stringUtil.isEmptySet(route_info, QStringLiteral("/v1/magma/app/info")).toString();
        auto server=this->parent->server();
        this->info = QStringLiteral("%1%2").arg(server, route_info.toString());
    }
};

MUAppEngineRoutes::MUAppEngineRoutes(QObject *parent):MURoutes(parent)
{
    this->p=new MUAppEngineRoutesPvt(this);
}

MUAppEngineRoutes::~MUAppEngineRoutes()
{
    dPvt();
    delete&p;
}

void MUAppEngineRoutes::load()
{
    MURoutes::load();
    dPvt();
    p.load();
}

void MUAppEngineRoutes::load(const QString &fileName)
{
    MURoutes::load(fileName);
    dPvt();
    p.load();
}

QString MUAppEngineRoutes::info() const
{
    dPvt();
    return p.info;
}

void MUAppEngineRoutes::setInfo(const QString &info)
{
    dPvt();
    p.info = info;
}
