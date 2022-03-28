#include "mu_request.h"
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
        p.header.insert(qsl("Authorization"), qsl("Bearer %1").arg(credentials));
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

    auto body=p.body;

    switch(qTypeId(p.body)){
    case QMetaType_QString:
    case QMetaType_QByteArray:
    {
        auto s=body.toByteArray().trimmed();
        auto chrFirst=s.at(0);
        auto chrLast=s.at(s.length()-1);
        s.clear();
        static QList<QChar> key={'[',']','{','}'};
        if(key.contains(chrFirst) || key.contains(chrLast)){
            if(p.requestAppType==MUEnumRequest::AppType::atCBor)
                return QCborValue::fromVariant(body).toByteArray();

            if(p.requestAppType==MUEnumRequest::AppType::atJson)
                return QJsonDocument::fromVariant(body).toJson(QJsonDocument::Compact);

            if(p.requestAppType==MUEnumRequest::AppType::atXml)
                return QJsonDocument::fromVariant(body).toJson(QJsonDocument::Compact);

            if(p.requestAppType==MUEnumRequest::AppType::atBinary)
                return QCborValue::fromVariant(body).toByteArray();
        }
        return {};
    }
    case QMetaType_QVariantList:
    case QMetaType_QStringList:
    case QMetaType_QVariantHash:
    case QMetaType_QVariantMap:
    default:
        if(p.requestAppType==MUEnumRequest::AppType::atCBor)
            return QCborValue::fromVariant(body).toByteArray();

        //        if(p.requestAppType==MUEnumRequest::AppType::atJson)
        //            return QJsonDocument::fromVariant(body).toJson(QJsonDocument::Compact);

        return QJsonDocument::fromVariant(body).toJson(QJsonDocument::Compact);
    }
}

QVariantHash MURequest::bodyMap() const
{
    dPvt();
    switch(qTypeId(p.body)){
    case QMetaType_QVariantHash:
    case QMetaType_QVariantMap:
        return p.body.toHash();
    case QMetaType_QStringList:
    case QMetaType_QVariantList:
        return {};
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
    }
}

QVariantHash MURequest::bodyHash() const
{
    dPvt();
    switch(qTypeId(p.body)){
    case QMetaType_QVariantHash:
    case QMetaType_QVariantMap:
        return p.body.toHash();
    case QMetaType_QStringList:
    case QMetaType_QVariantList:
        return {};
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
    }
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
    switch(qTypeId(p.body)){
    case QMetaType_QVariantHash:
    case QMetaType_QVariantMap:
    case QMetaType_QStringList:
    case QMetaType_QVariantList:
        return v;
    default:
        switch (this->requestAppType()){
        case MUEnumRequest::AppType::atCBor:
        case MUEnumRequest::AppType::atBinary:
            return (v=QCborValue::fromCbor(v.toByteArray()).toVariant());
        case MUEnumRequest::AppType::atJson:
            return (v=QJsonDocument::fromJson(v.toByteArray()).toVariant());
        default:
            return {};
        }
    }
}

QVariantHash MURequest::responseBodyMap() const
{
    dPvt();

    auto&v=p.response.response_body;
    switch(qTypeId(p.body)){
    case QMetaType_QVariantHash:
    case QMetaType_QVariantMap:
        return v.toHash();
    case QMetaType_QStringList:
    case QMetaType_QVariantList:
        return {};
    default:
        switch (this->requestAppType()){
        case MUEnumRequest::AppType::atCBor:
        case MUEnumRequest::AppType::atBinary:
            return QCborValue::fromCbor(v.toByteArray()).toVariant().toHash();
        case MUEnumRequest::AppType::atJson:
            return QJsonDocument::fromJson(v.toByteArray()).toVariant().toHash();
        default:
            return {};
        }
    }
}

QVariantList MURequest::responseBodyList() const
{
    dPvt();
    auto&v=p.response.response_body;
    switch(qTypeId(p.body)){
    case QMetaType_QVariantHash:
    case QMetaType_QVariantMap:
        return {};
    case QMetaType_QStringList:
    case QMetaType_QVariantList:
        return v.toList();
    default:
        switch (this->requestAppType()){
        case MUEnumRequest::AppType::atCBor:
        case MUEnumRequest::AppType::atBinary:
            return QCborValue::fromVariant(p.response.response_body.toByteArray()).toVariant().toList();
        case MUEnumRequest::AppType::atJson:
            return QJsonDocument::fromVariant(p.response.response_body.toByteArray()).toVariant().toList();
        default:
            return {};
        }
    }
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

MURequest &MURequest::setMethod(const QVariant &value)
{
    dPvt();
    switch (qTypeId(value)) {
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
            return *this;
        }
        break;
    }
    default:
        p.method=MUEnumRequest::Method::rmPost;
    }
    return *this;

}

MURequest &MURequest::setMethodHead()
{
    dPvt();
    p.method=MUEnumRequest::Method::rmHead;
    return *this;
}

MURequest &MURequest::setMethodGET()
{
    dPvt();
    p.method=MUEnumRequest::Method::rmGet;
    return *this;
}

MURequest &MURequest::setMethodPOST()
{
    dPvt();
    p.method=MUEnumRequest::Method::rmPost;
    return *this;
}

MURequest &MURequest::setMethodPUT()
{
    dPvt();
    p.method=MUEnumRequest::Method::rmPut;
    return *this;
}

MURequest &MURequest::setMethodDELETE()
{
    dPvt();
    p.method=MUEnumRequest::Method::rmDelete;
    return *this;
}

MUEnumRequest::AppType MURequest::requestAppType() const
{
    dPvt();
    return p.requestAppType;
}

MURequest &MURequest::setRequestAppType(const MUEnumRequest::AppType&value)
{
    dPvt();
    p.requestAppType = value;
    return *this;
}

MUStringUtil &MURequest::u()
{
    return MUStringUtil::i();
}

MUVariantUtil &MURequest::v()
{
    return MUVariantUtil::i();
}
