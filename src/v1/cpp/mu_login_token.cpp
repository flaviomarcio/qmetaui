#include "./mu_login_token.h"
#include <QMetaProperty>
#include <QStm>

#define dPvt()\
    auto&p = *reinterpret_cast<MULoginTokenPvt*>(this->p)

class MULoginTokenPvt:public QObject{
public:
    QDateTime iat ;
    QDateTime exp ;
    QString md5 ;
    QByteArray payload;
    QByteArray token ;
    MULoginToken*parent=nullptr;

    explicit MULoginTokenPvt(MULoginToken*parent):QObject{parent}
    {
        this->parent=parent;
    }

    virtual ~MULoginTokenPvt()
    {

    }
};

MULoginToken::MULoginToken(QObject *parent):MUObject(parent)
{
    this->p= new MULoginTokenPvt(this);
}

MULoginToken::~MULoginToken()
{
    dPvt();
    delete&p;
}

MULoginToken &MULoginToken::operator=(const QVariantHash &v)
{
    auto metaObject=this->metaObject();
    for(int i = 0; i < metaObject->propertyCount(); ++i) {
        auto property=metaObject->property(i);
        auto vv=v.value(property.name());
        if(qTypeId(vv)!=qTypeId(property) && qTypeId(property)==QMetaType_QDateTime)
            vv=vv.toDateTime();
        property.write(this,vv);
    }
    return*this;
}

QDateTime MULoginToken::exp() const
{
    dPvt();
    return p.exp;
}

void MULoginToken::setExp(const QDateTime &value)
{
    dPvt();
    p.exp = value;
}

QDateTime MULoginToken::iat() const
{
    dPvt();
    return p.iat;
}

void MULoginToken::setIat(const QDateTime &value)
{
    dPvt();
    p.iat=value;
}

QString MULoginToken::md5() const
{
    dPvt();
    return p.md5;
}

void MULoginToken::setMd5(const QString &value)
{
    dPvt();
    p.md5 = value;
}

QByteArray MULoginToken::payload() const
{
    dPvt();
    return p.payload;
}

void MULoginToken::setPayload(const QByteArray &value)
{
    dPvt();
    p.payload = value;
}

QByteArray MULoginToken::token() const
{
    dPvt();
    return p.token;
}

void MULoginToken::setToken(const QByteArray &value)
{
    dPvt();
    p.token = value;
}

void MULoginToken::clear()
{
    this->setIat(QDateTime());
    this->setExp(QDateTime());
    this->setMd5({});
    this->setPayload({});
    this->setToken({});
}

bool MULoginToken::isRecent()
{
    auto dt=QDateTime::currentDateTime().addSecs(30);
    dPvt();
    return p.iat.isValid() && (p.iat<dt);
}
