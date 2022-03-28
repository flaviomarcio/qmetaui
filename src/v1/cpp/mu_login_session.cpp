#include "./mu_login_session.h"
#include "./mu_object_util.h"
#include "./mu_variant_util.h"
#include "./mu_string_util.h"
#include "./mu_cache_util.h"

#include "./mu_validation_util_public.h"
#include "./mu_validation_util_ptb.h"

#include "./mu_notification.h"
#include "./mu_register.h"
#include "./mu_application.h"
#include <QStm>

#define dPvt()\
    auto&p = *reinterpret_cast<MULoginSessionPvt*>(this->p)

class MULoginSessionPvt:public QObject{
public:
    QUuid uuid;
    QByteArray hsh_md5;
    QVariantHash data;
    MULoginProfile profile;
    MULoginToken token;
    MULoginSession*session=nullptr;
    MUObjectUtil&objectUtil=MUObjectUtil::i();
    MUVariantUtil&variantUtil=MUVariantUtil::i();
    MUStringUtil&stringUtil=MUStringUtil::i();
    MUCacheUtil&cacheUtil=MUCacheUtil::i();
    bool initialized=false;
    explicit MULoginSessionPvt(MULoginSession*parent):QObject(parent), profile(parent), token(parent)
    {
        this->session=parent;
        connect(&MUNotification::i(), &MUNotification::notify, this, &MULoginSessionPvt::notification);
        connect(parent, &MULoginSession::sessionUnAuthorized, this, &MULoginSessionPvt::onSessionUnAuthorized);
    }

    virtual ~MULoginSessionPvt()
    {

    }

    bool load(){
#if Q_MU_LOG
        qInfo()<<"Session file == " << cacheUtil.sessionFileName();
#endif
        if(uuid.isNull()){
            auto bytes=cacheUtil.sessionLoadFile();
            QJsonParseError*parser=nullptr;
            auto doc=QJsonDocument::fromJson(bytes, parser);
            auto map=(parser!=nullptr)?QVariantHash():doc.toVariant().toHash();
            this->setData(map);
        }

#if Q_MU_LOG
      qInfo()<<"Session hsh_md5 == " << this->session->hsh_md5();
#endif
        return this->isLogged();
    }

    bool save()
    {
        QVariantHash data, response;
        response.insert(qsl("profile"), this->profile.toHash());
        response.insert(qsl("token"), this->token.toHash());
        response.insert(qsl("session"), this->session->toHash());
        data.insert(qsl("response"), response);
        return this->save(data);
    }

    void setData(const QVariantHash&v)
    {
        this->data=v;

        if (v.isEmpty()){
            this->session->clear();
        }
        else {
            auto response=this->data.value(qsl("response")).toHash();
            this->profile=response.value(qsl("profile")).toHash();
            this->token=response.value(qsl("token")).toHash();
            *this->session=response.value(qsl("session")).toHash();
        }
#if Q_MU_LOG_VERBOSE
        mWarning()<<QString("Session token %1").arg(QString(this->session->hsh_md5()));
#endif
        this->verify();
        initialized=true;
    }

    bool save(const QVariant&data)
    {
        switch (qTypeId(data)){
        case QMetaType_QVariantMap:
        case QMetaType_QVariantHash:
            break;
        default:
            return false;
        }

        auto vMap=data.toHash();
        if(!vMap.contains(qsl("response"))){
            if(vMap.contains(qsl("profile")) && vMap.contains(qsl("token")) && vMap.contains(qsl("session")))
                vMap=QVariantHash{{qsl("response"), vMap}};
        }

        if(!cacheUtil.sessionSaveFile(vMap))
            return false;

        this->setData(vMap);
        return true;
    }

    bool verify()
    {
        if(this->isLogged()){
            emit session->sessionLogged();
            return true;
        }
        emit session->sessionUnLogged();
        return false;
    }

    bool verifyData()
    {
        if(profile.validated())
            return true;

        if ( !MUValidationUtilPTB::i().isCPF(profile.document())){
            emit this->session->invalidData(tr("Necessário informar o CPF válido."));
            return false;
        }

        if ( !MUValidationUtilPublic::i().isEmail(profile.email())){
            emit this->session->invalidData(tr("Necessário informar email válido."));
            return false;
        }

        if ( !MUValidationUtilPublic::i().isPhoneNumber(profile.phone_number())){
            emit this->session->invalidData(tr("Necessário informar telefone válido."));
            return false;
        }

        if ( !MUValidationUtilPTB::i().isName(profile.name())){
            emit this->session->invalidData(tr("Necessário informar nome completo."));
            return false;
        }

        return true;
    }

    bool logoff()
    {
        this->setData({});
        cacheUtil.dirClear();
        return cacheUtil.sessionRemoveFile();
    }

    bool isLogged()const
    {
        if(this->data.isEmpty())
            return false;

        if(!this->data.contains(qsl("response")))
            return false;

        auto response=this->data.value(qsl("response")).toHash();

        if(!response.contains(qsl("token")))
            return false;

        auto token=response.value(qsl("token"));
        if(!token.isValid())
            return false;
        return true;
    }
public slots:
    void notification(int type, int especification, const QVariant &payload)
    {
        if(type==MUEnumNotification::nt_Security){
            switch (especification) {
            case MUEnumNotification::nse_LoginSuccessful:
                emit this->session->loginSuccessful(payload);
                break;
            case MUEnumNotification::nse_Unknow:
                emit this->session->loginSuccessful(payload);
                break;
            case MUEnumNotification::nse_Error:
                emit this->session->notifyError(payload);
                break;
            case MUEnumNotification::nse_Fail:
                emit this->session->notifyFail(payload);
                break;
            case MUEnumNotification::nse_SessionUnauthorized:
                emit this->session->sessionUnAuthorized();
                break;
            default:
                break;
            }
        }
    }
private slots:
    void onSessionUnAuthorized()
    {
        this->logoff();
    }
};



MULoginSession::MULoginSession(QObject *parent) : MUObject(parent)
{
    this->p = new MULoginSessionPvt(this);
    QObject::connect(this, &MULoginSession::sessionLogged, this, &MULoginSession::loginChanged);
    QObject::connect(this, &MULoginSession::sessionUnLogged, this, &MULoginSession::loginChanged);
}

MULoginSession::~MULoginSession()
{
    QObject::disconnect(this, &MULoginSession::sessionLogged, this, &MULoginSession::loginChanged);
    QObject::disconnect(this, &MULoginSession::sessionUnLogged, this, &MULoginSession::loginChanged);
    dPvt();
    delete&p;
}

MULoginSession &MULoginSession::i()
{
    static MULoginSession __i;
    return __i;
}

QUuid MULoginSession::uuid() const
{
    dPvt();
    return p.uuid;
}

void MULoginSession::set_uuid(const QUuid &value)
{
    Q_UNUSED(value)
    dPvt();
    p.uuid = value;
}

QByteArray MULoginSession::hsh_md5() const
{
    dPvt();
    return p.hsh_md5;
}

void MULoginSession::set_hsh_md5(const QByteArray &value)
{
    Q_UNUSED(value)
    dPvt();
    p.hsh_md5 = value;
}

MULoginProfile*MULoginSession::profile()
{
    dPvt();
    return&p.profile;
}

MULoginToken *MULoginSession::token()
{
    dPvt();
    return&p.token;
}

bool MULoginSession::set_token(const MULoginToken *v) const
{
    Q_UNUSED(v)
    return false;
}

bool MULoginSession::set_profile(const MULoginProfile *v) const
{
    Q_UNUSED(v)
    return false;
}

QVariant MULoginSession::value(const QString &key)const
{
    dPvt();
    if(p.data.contains(key))
        return p.data.value(key);

    if(p.data.contains(key.toUpper()))
        return p.data.value(key.toUpper());

    if(p.data.contains(key.toLower()))
        return p.data.value(key.toLower());

    auto skey=key.toLower();
    QHashIterator<QString, QVariant> i(p.data);
    while (i.hasNext()) {
        i.next();
        if(skey==i.key())
            return i.value();
    }
    return QVariant();
}

bool MULoginSession::load()
{
    dPvt();
    return p.load();
}

bool MULoginSession::save()
{
    dPvt();
    return p.save();
}

QVariantHash MULoginSession::data()
{
    dPvt();
    return p.data;
}

bool MULoginSession::setData(const QVariant &v)
{
    dPvt();
    return p.save(v);
}

bool MULoginSession::isLogged()const
{
    dPvt();
    return p.isLogged();
}

void MULoginSession::clear()
{
    this->token()->clear();
    this->profile()->clear();
    this->set_uuid(QUuid());
    this->set_hsh_md5("");
}

bool MULoginSession::logoff()
{
    dPvt();
    return p.logoff();
}

void MULoginSession::verify()
{
    dPvt();
    p.verify();
}

bool MULoginSession::verifyData()
{
    dPvt();
    return p.verifyData();
}

MULoginSession &MULoginSession::operator=(const QVariant &v)
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


