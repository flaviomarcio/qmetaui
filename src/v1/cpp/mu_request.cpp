#include "mu_request.h"
#include "./mu_register.h"
#include "./private/p_mu_request.h"

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
        p.header[key]=value;
        return true;
    }
    return false;
}

void MURequest::setHeader(const QVariant &header)
{
    dPvt();
    p.header=header.toHash();
}

bool MURequest::setAuthBearer(const QString &credentials) const
{
    dPvt();
    if(!credentials.trimmed().isEmpty()){
        p.header.insert(qsl("Authorization"), qsl("Bearer %1").arg(credentials));
        return true;
    }
    return false;
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

MURequest::MURequest(QObject *parent) : QObject(parent)
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

QUuid MURequest::uuid() const
{
    dPvt();
    return p.uuid;
}

QByteArray MURequest::body() const
{
    dPvt();

    auto body=p.body;

    int typeId=body.type();
    switch (typeId) {
    case QMetaType_QVariantList:
    case QMetaType_QStringList:
    case QMetaType_QVariantHash:
    case QMetaType_QVariantMap:
    {
        switch (this->requestAppType()) {
        case MUEnumRequest::AppType::atJson:
            return QCborValue::fromVariant(body).toByteArray();
        case MUEnumRequest::AppType::atCBor:
        case MUEnumRequest::AppType::atBinary:
            return QJsonDocument::fromVariant(body).toJson(QJsonDocument::Compact);
        default:
            return QJsonDocument::fromVariant(body).toJson(QJsonDocument::Compact);
        }
        break;
    }
    case QMetaType_QString:
    case QMetaType_QByteArray:
    {
        auto s=body.toByteArray().trimmed();
        auto chrFirst=s.at(0);
        auto chrLast=s.at(s.length()-1);
        s.clear();
        auto key=QVector<QChar>{'[',']','{','}'};
        if(key.contains(chrFirst) || key.contains(chrLast)){
            switch (p.requestAppType) {
            case MUEnumRequest::AppType::atCBor:
                return (QCborValue::fromVariant(body).toByteArray());
            case MUEnumRequest::AppType::atJson:
                return (QJsonDocument::fromJson(body.toByteArray()).toJson(QJsonDocument::Compact));
            case MUEnumRequest::AppType::atXml:
                return (QJsonDocument::fromVariant(body.toByteArray()).toJson(QJsonDocument::Compact));
            case MUEnumRequest::AppType::atBinary:
                return (QCborValue::fromVariant(body).toByteArray());
            default:
                return {};
            }
        }
        break;
    }
    default:
        break;
    }
    return {};
}

QVariantMap MURequest::bodyMap() const
{
    dPvt();
    auto&v=p.body;
    int typeId=p.body.type();
    switch (typeId) {
    case QMetaType_QVariantHash:
    case QMetaType_QVariantMap:
        return v.toMap();
    case QMetaType_QString:
    case QMetaType_QByteArray:
        switch (this->requestAppType()) {
        case MUEnumRequest::AppType::atJson:
            return QJsonDocument::fromJson(v.toByteArray()).toVariant().toMap();
        case MUEnumRequest::AppType::atCBor:
        case MUEnumRequest::AppType::atBinary:
            return QCborValue::fromCbor(v.toByteArray()).toVariant().toMap();
        default:
            return {};
        }
        break;
    default:
        break;
    }
    return {};
}

QVariantHash MURequest::bodyHash() const
{
    dPvt();
    auto&v=p.body;
    int typeId=p.body.type();
    switch (typeId) {
    case QMetaType_QVariantHash:
    case QMetaType_QVariantMap:
        return v.toHash();
    case QMetaType_QString:
    case QMetaType_QByteArray:
        switch (this->requestAppType()) {
        case MUEnumRequest::AppType::atJson:
            return QJsonDocument::fromJson(v.toByteArray()).toVariant().toHash();
        case MUEnumRequest::AppType::atCBor:
        case MUEnumRequest::AppType::atBinary:
            return QCborValue::fromCbor(v.toByteArray()).toVariant().toHash();
        default:
            return {};
        }
        break;
    default:
        break;
    }
    return {};
}

QVariantList MURequest::bodyList() const
{
    dPvt();
    auto&v=p.body;
    int typeId=p.body.type();
    switch (typeId) {
    case QMetaType_QVariantList:
    case QMetaType_QStringList:
        return v.toList();
    case QMetaType_QString:
    case QMetaType_QByteArray:
        switch (this->requestAppType()) {
        case MUEnumRequest::AppType::atJson:
            return QJsonDocument::fromJson(v.toByteArray()).toVariant().toList();
        case MUEnumRequest::AppType::atCBor:
        case MUEnumRequest::AppType::atBinary:
            return QCborValue::fromCbor(v.toByteArray()).toVariant().toList();
        default:
            return {};
        }
        break;
    default:
        break;
    }
    return {};
}

QStringList MURequest::bodyStringList() const
{
    dPvt();
    auto&v=p.body;
    int typeId=p.body.type();
    switch (typeId) {
    case QMetaType_QVariantList:
    case QMetaType_QStringList:
        return v.toStringList();
    case QMetaType_QString:
    case QMetaType_QByteArray:
        switch (this->requestAppType()) {
        case MUEnumRequest::AppType::atJson:
            return QJsonDocument::fromJson(v.toByteArray()).toVariant().toStringList();
        case MUEnumRequest::AppType::atCBor:
        case MUEnumRequest::AppType::atBinary:
            return QCborValue::fromCbor(v.toByteArray()).toVariant().toStringList();
        default:
            return {};
        }
        break;
    default:
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
    QVariant convert;
    auto&v=p.response.response_body;
    int typeId=p.body.type();
    switch (typeId) {
    case QMetaType_QVariantList:
    case QMetaType_QStringList:
    case QMetaType_QVariantHash:
    case QMetaType_QVariantMap:
        return v;
    case QMetaType_QString:
    case QMetaType_QByteArray:
        switch (this->requestAppType()) {
        case MUEnumRequest::AppType::atJson:
            convert=QJsonDocument::fromJson(v.toByteArray()).toVariant();
            break;
        case MUEnumRequest::AppType::atCBor:
        case MUEnumRequest::AppType::atBinary:
            convert=QCborValue::fromCbor(v.toByteArray()).toVariant();
            break;
        default:
            break;
        }
        break;
    default:
        break;
    }
    typeId=convert.type();
    switch (typeId) {
    case QMetaType_QVariantList:
    case QMetaType_QStringList:
    case QMetaType_QVariantHash:
    case QMetaType_QVariantMap:
        return v=convert;
    default:
        return v;
    }
}

QVariantHash MURequest::responseBodyMap() const
{
    dPvt();
    auto&v=p.response.response_body;
    int typeId=v.type();
    switch (typeId) {
    case QMetaType_QVariantHash:
    case QMetaType_QVariantMap:
        return v.toHash();
    case QMetaType_QString:
    case QMetaType_QByteArray:
        switch (this->requestAppType()) {
        case MUEnumRequest::AppType::atJson:
            return QJsonDocument::fromJson(v.toByteArray()).toVariant().toHash();
        case MUEnumRequest::AppType::atCBor:
        case MUEnumRequest::AppType::atBinary:
            return QCborValue::fromCbor(v.toByteArray()).toVariant().toHash();
        default:
            break;
        }
        break;
    default:
        break;
    }
    return {};
}

QVariantHash MURequest::responseBodyHash() const
{
    dPvt();
    auto&v=p.response.response_body;
    int typeId=v.type();
    switch (typeId) {
    case QMetaType_QVariantHash:
    case QMetaType_QVariantMap:
        return v.toHash();
    case QMetaType_QString:
    case QMetaType_QByteArray:
        switch (this->requestAppType()) {
        case MUEnumRequest::AppType::atJson:
            return QJsonDocument::fromJson(v.toByteArray()).toVariant().toHash();
        case MUEnumRequest::AppType::atCBor:
        case MUEnumRequest::AppType::atBinary:
            return QCborValue::fromCbor(v.toByteArray()).toVariant().toHash();
        default:
            break;
        }
        break;
    default:
        break;
    }
    return {};
}

QVariantList MURequest::responseBodyList() const
{
    dPvt();
    auto&v=p.response.response_body;
    int typeId=p.body.type();
    switch (typeId) {
    case QMetaType_QVariantList:
    case QMetaType_QStringList:
        return v.toList();
    case QMetaType_QString:
    case QMetaType_QByteArray:
        switch (this->requestAppType()) {
        case MUEnumRequest::AppType::atJson:
            return QJsonDocument::fromJson(v.toByteArray()).toVariant().toList();
        case MUEnumRequest::AppType::atCBor:
        case MUEnumRequest::AppType::atBinary:
            return QCborValue::fromCbor(v.toByteArray()).toVariant().toList();
        default:
            break;
        }
        break;
    default:
        break;
    }
    return {};
}

QStringList MURequest::responseBodyStringList() const
{
    dPvt();
    auto&v=p.response.response_body;
    int typeId=p.body.type();
    switch (typeId) {
    case QMetaType_QVariantList:
    case QMetaType_QStringList:
        return v.toStringList();
    case QMetaType_QString:
    case QMetaType_QByteArray:
        switch (this->requestAppType()) {
        case MUEnumRequest::AppType::atJson:
            return QJsonDocument::fromJson(v.toByteArray()).toVariant().toStringList();
        case MUEnumRequest::AppType::atCBor:
        case MUEnumRequest::AppType::atBinary:
            return QCborValue::fromCbor(v.toByteArray()).toVariant().toStringList();
        default:
            break;
        }
        break;
    default:
        break;
    }
    return {};
}

QString MURequest::responseBodyString() const
{
    dPvt();
    auto&v=p.response.response_body;
    int typeId=p.body.type();
    switch (typeId) {
    case QMetaType_QVariantHash:
    case QMetaType_QVariantMap:
    case QMetaType_QVariantList:
    case QMetaType_QStringList:
        return QJsonDocument::fromVariant(v).toJson(QJsonDocument::Compact);
    case QMetaType_QString:
    case QMetaType_QByteArray:
        return v.toString();
    default:
        return {};
    }
}

QByteArray MURequest::responseBodyByteArray() const
{
    dPvt();
    auto&v=p.response.response_body;
    int typeId=p.body.type();
    switch (typeId) {
    case QMetaType_QVariantHash:
    case QMetaType_QVariantMap:
    case QMetaType_QVariantList:
    case QMetaType_QStringList:
        return QJsonDocument::fromVariant(v).toJson(QJsonDocument::Compact);
    case QMetaType_QString:
    case QMetaType_QByteArray:
        return v.toByteArray();
    default:
        return {};
    }
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
    case QMetaType_Int:
    case QMetaType_UInt:
    case QMetaType_LongLong:
    case QMetaType_ULongLong:
        p.method=MUEnumRequest::Method(value.toInt());
        break;
    case QMetaType_QString:
    case QMetaType_QByteArray:
    case QMetaType_QChar:
    case QMetaType_QBitArray:
    {
        auto vv=value.toString().trimmed().toLower();
        for (int i = 0; i < MUEnumRequestMethodName.count(); ++i) {
            auto v=MUEnumRequestMethodName.value(i);
            if(v.trimmed().toLower()!=vv)
                continue;
            p.method=MUEnumRequest::Method(i);
            return;
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
