#include "./mu_login_profile.h"
#include "./mu_login_session.h"
#include <QMetaProperty>

#define dPvt()\
    auto&p = *reinterpret_cast<MULoginProfilePvt*>(this->p)

class MULoginProfilePvt:public QObject{
public:
    QUuid uuid;
    QString hsh_account;
    QString name;
    QString document;
    QDateTime dt_birth;
    QString email;
    QString phone_number;
    bool validated=false;
    MULoginProfile*parent=nullptr;
    explicit MULoginProfilePvt(MULoginProfile*parent):QObject{parent}{
        this->parent=parent;
    }

    virtual ~MULoginProfilePvt(){

    }
};

MULoginProfile::MULoginProfile(QObject *parent):MUObject(parent)
{
    this->p = new MULoginProfilePvt(this);
}

MULoginProfile::~MULoginProfile()
{
    dPvt();
    delete&p;
}

QUuid MULoginProfile::uuid() const
{
    dPvt();
    return p.uuid;
}

void MULoginProfile::set_uuid(const QUuid &value)
{
    dPvt();
    p.uuid=value;
}

QString MULoginProfile::hsh_account() const
{
    dPvt();
    return QString(p.hsh_account);
}

void MULoginProfile::set_hsh_account(const QString &value)
{
    dPvt();
    p.hsh_account = value;
}

QString MULoginProfile::name() const
{
    dPvt();
    return QString(p.name);
}

void MULoginProfile::set_name(const QString &value)
{
    dPvt();
    p.name=value;
}

QString MULoginProfile::document() const
{
    dPvt();
    return QString(p.document);
}

void MULoginProfile::set_document(const QString &value)
{
    dPvt();
    p.document = value;
}

QDateTime MULoginProfile::dt_birth() const
{
    dPvt();
    return p.dt_birth;
}

void MULoginProfile::set_dt_birth(const QDateTime &value)
{
    dPvt();
    p.dt_birth = value;
}

QString MULoginProfile::email() const
{
    dPvt();
    return QString(p.email);
}

void MULoginProfile::set_email(const QString &value)
{
    dPvt();
    p.email = value;
}

QString MULoginProfile::phone_number() const
{
    dPvt();
    return QString(p.phone_number);
}

void MULoginProfile::set_phone_number(const QString &value)
{
    dPvt();
    p.phone_number = value;
}

bool MULoginProfile::validated() const
{
    dPvt();
    return p.validated;
}

void MULoginProfile::set_validated(const bool &value)
{
    dPvt();
    p.validated = value;
}

MULoginProfile &MULoginProfile::operator=(const MULoginProfile &v)
{
    this->fromHash(v.toHash());
    return*this;
}

void MULoginProfile::clear()
{
    this->set_uuid        ({});
    this->set_hsh_account ({});
    this->set_name        ({});
    this->set_dt_birth    ({});
    this->set_email       ({});
    this->set_document    (0);
    this->set_phone_number(0);
    this->set_validated   (false);
}

MULoginProfile &MULoginProfile::operator=(const QVariant &v)
{
    this->fromMap(v.toMap());
    return*this;
}

bool MULoginProfile::loadCurrentSession()
{
    auto v=MULoginSession::i().profile()->toHash();
    auto r=this->fromHash(v);
    emit loaded();
    return r;
}

bool MULoginProfile::isValid()
{
    if(this->uuid().isNull()){
#ifdef Q_MU_LOG
        mWarning()<<QStringLiteral("session uuid is null");
#endif
        return false;
    }

    if(this->hsh_account().trimmed().isEmpty()){
#ifdef Q_MU_LOG
        mWarning()<<QStringLiteral("hsh_account is invalid");
#endif
        return false;
    }

    return true;
}
