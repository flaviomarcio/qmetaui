#include "./mu_request.h"
#include "./mu_register.h"
#include "./private/p_mu_request.h"
#include <QStm>

#define dPvt()\
    auto&p = *reinterpret_cast<MURequestPvt*>(this->p)

QVariantHash MURequest::header()const
{
    dPvt();
    return p.header;
}

bool MURequest::setHeader(const QString &key, const QVariant &value) const
{
    dPvt();
    if(!key.trimmed().isEmpty()){
        p.header.insert(key,value);
        return true;
    }
    return false;
}

void MURequest::setHeader(const QVariant &header)
{
    dPvt();
    p.header=header.toHash();
}

bool MURequest::setAuthoBearer(const QString &credentials) const
{
    dPvt();
    if(!credentials.trimmed().isEmpty()){
        p.header.insert(QByteArrayLiteral("Authorization"), QStringLiteral("Bearer %1").arg(credentials));
        return true;
    }
    return false;
}

QVariant MURequest::uuid() const
{
    dPvt();
    return p.uuid;
}

MUServerLink *MURequest::link()
{
    dPvt();
    return&p.link;
}

void MURequest::setLink(const MUServerLink *link)
{
    dPvt();
    p.link=*link;
    this->setUrl(p.link.url());
    this->setHeader(p.link.headers());
    this->setMethod(p.link.method());
}

MURequest::MURequest(QObject *parent) : QObject{parent}
{
    this->p=new MURequestPvt(this);
}

MURequest::~MURequest()
{
    dPvt();
    p.finish();
    p.deleteLater();
}

void MURequest::clear()
{
    dPvt();
    p.response=MURequestResponse();
    p.body.clear();
}

bool MURequest::start()
{
    dPvt();
    return p.start(QString(),[](const MURequest*){},[](const MURequest*){});
}

bool MURequest::start(const QUrl&url, MURequestCallback response, MURequestCallback fail)
{
    dPvt();
    return p.start(url, response, fail);
}

bool MURequest::canStart()
{
    dPvt();
    return p.uuid.isNull();
}

void MURequest::finish()
{
    dPvt();
    p.finish();
}

void MURequest::cancel()
{
    dPvt();
    p.cancel();
}

bool MURequest::isRunning()
{
    dPvt();
    return !p.uuid.isNull();
}

QByteArray MURequest::body() const
{
    dPvt();

    if(p.body.isNull() || !p.body.isValid())
        return {};

    auto&body=p.body;


    switch (qTypeId(body)){
    case QMetaType_QByteArray:
    case QMetaType_QString:
    {
        auto s=body.toByteArray().trimmed();
        if(s.isEmpty())
            break;

        auto chrFirst=s.at(0);
        auto chrLast=s.at(s.length()-1);
        s.clear();
        static const QList<QChar> key={'[',']','{','}'};
        if(!key.contains(chrFirst) || key.contains(chrLast))
            break;

        if(p.requestAppType==MUEnumRequest::AppType::atCBor)
            body=QCborValue::fromVariant(body).toByteArray();

        if(p.requestAppType==MUEnumRequest::AppType::atJson)
            body=QJsonDocument::fromVariant(body).toJson(QJsonDocument::Compact);

        if(p.requestAppType==MUEnumRequest::AppType::atXml)
            body=QJsonDocument::fromVariant(body).toJson(QJsonDocument::Compact);

        if(p.requestAppType==MUEnumRequest::AppType::atBinary)
            body=QCborValue::fromVariant(body).toByteArray();

        break;
    }
    case QMetaType_QVariantList:
    case QMetaType_QVariantMap:
    case QMetaType_QVariantHash:
    case QMetaType_QStringList:
    {
        if(p.requestAppType==MUEnumRequest::AppType::atCBor)
            body=(QCborValue::fromVariant(body).toByteArray());

        if(p.requestAppType==MUEnumRequest::AppType::atJson)
            body=QJsonDocument::fromVariant(body).toJson(QJsonDocument::Compact);

        body=QJsonDocument::fromVariant(body).toJson(QJsonDocument::Compact);
        break;
    }
    default:
        break;
    }
    return body.toByteArray();
}

QVariantMap MURequest::bodyMap() const
{
    dPvt();
    switch (qTypeId(p.body)){
    case QMetaType_QVariantMap:
    case QMetaType_QVariantHash:
        return p.body.toMap();
    default:
        switch (this->requestAppType()){
        case MUEnumRequest::AppType::atJson:
            return QJsonDocument::fromJson(p.body.toByteArray()).toVariant().toMap();
        case MUEnumRequest::AppType::atCBor:
        case MUEnumRequest::AppType::atBinary:
            return QCborValue::fromCbor(p.body.toByteArray()).toVariant().toMap();
        default:
            return {};
        }
        break;
    }
    return {};
}

QVariantHash MURequest::bodyHash() const
{
    dPvt();
    switch (qTypeId(p.body)){
    case QMetaType_QVariantMap:
    case QMetaType_QVariantHash:
        return p.body.toHash();
    default:
        switch (this->requestAppType()){
        case MUEnumRequest::AppType::atJson:
            return QJsonDocument::fromJson(p.body.toByteArray()).toVariant().toHash();
        case MUEnumRequest::AppType::atCBor:
        case MUEnumRequest::AppType::atBinary:
            return QCborValue::fromCbor(p.body.toByteArray()).toVariant().toHash();
        default:
            return {};
        }
        break;
    }
    return {};
}

QVariantList MURequest::bodyList() const
{
    dPvt();
    switch (qTypeId(p.body)){
    case QMetaType_QVariantList:
    case QMetaType_QStringList:
        return p.body.toList();
    default:
        switch (this->requestAppType()){
        case MUEnumRequest::AppType::atJson:
            return QJsonDocument::fromJson(p.body.toByteArray()).toVariant().toList();
        case MUEnumRequest::AppType::atCBor:
        case MUEnumRequest::AppType::atBinary:
            return QCborValue::fromCbor(p.body.toByteArray()).toVariant().toList();
        default:
            return {};
        }
        break;
    }
    return {};
}

void MURequest::setBody(const QVariant &body)
{
    dPvt();
    p.body=this->u().toVar(body);
}

QVariant MURequest::stateCode()const
{
    dPvt();
    return p.response.response_status_code;
}

QNetworkReply::NetworkError MURequest::stateCodeQt()const
{
    dPvt();
    return p.response.response_qt_status_code;
}

QVariant MURequest::statePhrase()const
{
    dPvt();
    return p.response.response_status_reason_phrase;
}

QVariant MURequest::responseBody() const
{
    dPvt();
    auto&v=p.response.response_body;
    auto type=p.response.response_body.type();
    if(type==QVariant::Hash || type==QVariant::Map || type==QVariant::List || type==QVariant::StringList)
        return v;
    else{
        QVariant vv;
        if(this->requestAppType()==MUEnumRequest::AppType::atJson)
            vv=QJsonDocument::fromJson(v.toByteArray()).toVariant();
        else if(this->requestAppType()==MUEnumRequest::AppType::atCBor || this->requestAppType()==MUEnumRequest::AppType::atBinary)
            vv=QCborValue::fromCbor(v.toByteArray()).toVariant();

        type=vv.type();
        if(type==QVariant::Hash || type==QVariant::Map || type==QVariant::List || type==QVariant::StringList)
            v=vv;
        return v;

    }
}

QVariantHash MURequest::responseBodyMap() const
{
    dPvt();
    QVariantHash bodyMap;
    auto&v=p.response.response_body;
    auto type=p.response.response_body.type();
    if(type==QVariant::Hash || type==QVariant::Map)
        bodyMap=v.toHash();
    else if(this->requestAppType()==MUEnumRequest::AppType::atJson)
        bodyMap=QJsonDocument::fromJson(v.toByteArray()).toVariant().toHash();
    else if(this->requestAppType()==MUEnumRequest::AppType::atCBor || this->requestAppType()==MUEnumRequest::AppType::atBinary)
        bodyMap=QCborValue::fromCbor(v.toByteArray()).toVariant().toHash();
    else
        bodyMap.clear();
    return bodyMap.isEmpty()?QVariantHash():bodyMap;
}

QVariantList MURequest::responseBodyList() const
{
    dPvt();
    QVariantList bodyList;
    auto type=p.response.response_body.type();
    if(type==QVariant::List || type==QVariant::StringList)
        bodyList=p.response.response_body.toList();
    else if(this->requestAppType()==MUEnumRequest::AppType::atJson)
        bodyList=QJsonDocument::fromVariant(p.response.response_body.toByteArray()).toVariant().toList();
    else if(this->requestAppType()==MUEnumRequest::AppType::atCBor || this->requestAppType()==MUEnumRequest::AppType::atBinary)
        bodyList=QCborValue::fromVariant(p.response.response_body.toByteArray()).toVariant().toList();
    return bodyList;
}

QString MURequest::responseBodyString() const
{
    dPvt();
    return (p.response.response_body.toByteArray());
}

bool MURequest::isOk()const
{
    dPvt();
    return p.response.isOk();
}

bool MURequest::isUnAuthorized() const
{
    dPvt();
    return p.response.isUnAuthorized();
}

bool MURequest::isNetworkFail() const
{
    dPvt();
    return p.response.isNetworkFail();
}

bool MURequest::isNetworkError() const
{
    dPvt();
    return p.response.isNetworkError();
}

MUEnumRequest::Mode MURequest::modeSynchronous() const
{
    dPvt();
    return p.modeSynchronous;
}

void MURequest::setModeSynchronous(const MUEnumRequest::Mode &mode)
{
    dPvt();
    p.modeSynchronous = mode;
}

QUrl MURequest::url() const
{
    dPvt();
    return p.url;
}

void MURequest::setUrl(const QString &url)
{
    dPvt();
    p.url = url;
}

MUEnumRequest::Method MURequest::method() const
{
    dPvt();
    return p.method;
}

void MURequest::setMethod(const QVariant &value)
{
    dPvt();
    int typeId=value.type();
    switch (typeId) {
    case QMetaType::Int:
    case QMetaType::UInt:
    case QMetaType::LongLong:
    case QMetaType::ULongLong:
        p.method=MUEnumRequest::Method(value.toInt());
        break;
    case QMetaType::QString:
    case QMetaType::QByteArray:
    case QMetaType::QChar:
    case QMetaType::QBitArray:
    {
        auto vv=value.toString().trimmed().toLower();
        for (int i = 0; i < MUEnumRequestMethodName.count(); ++i) {
            auto v=MUEnumRequestMethodName.value(i);
            if(v.trimmed().toLower()==vv){
                p.method=MUEnumRequest::Method(i);
                return;
            }
        }
        break;
    }
    default:
        p.method=MUEnumRequest::Method::rmPost;
    }

}

void MURequest::setMethodHead()
{
    dPvt();
    p.method=MUEnumRequest::Method::rmHead;
}

void MURequest::setMethodGET()
{
    dPvt();
    p.method=MUEnumRequest::Method::rmGet;
}

void MURequest::setMethodPOST()
{
    dPvt();
    p.method=MUEnumRequest::Method::rmPost;
}

void MURequest::setMethodPUT()
{
    dPvt();
    p.method=MUEnumRequest::Method::rmPut;
}

void MURequest::setMethodDELETE()
{
    dPvt();
    p.method=MUEnumRequest::Method::rmDelete;
}

MUEnumRequest::AppType MURequest::requestAppType() const
{
    dPvt();
    return p.requestAppType;
}

void MURequest::setRequestAppType(const MUEnumRequest::AppType&value)
{
    dPvt();
    p.requestAppType = value;
}

MUStringUtil &MURequest::u()
{
    return MUStringUtil::i();
}

MUVariantUtil &MURequest::v()
{
    return MUVariantUtil::i();
}
