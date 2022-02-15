#include "./mu_login_token.h"
#include <QMetaProperty>

#define dPvt()\
    auto&p = *reinterpret_cast<MULoginTokenPvt*>(this->p)

class MULoginTokenPvt{
public:
    QDateTime iat ;
    QDateTime exp ;
    QString md5 ;
    QByteArray payload;
    QByteArray token ;
    MULoginToken*parent=nullptr;

    explicit MULoginTokenPvt(MULoginToken*parent)
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

        int typeIdP=property.type();
        int typeIdV=vv.type();

        if(typeIdV==typeIdP){
            property.write(this, vv);
            continue;
        }

        switch (typeIdP) {
        case QMetaType_QDate:
            property.write(this, vv.toDate());
            break;
        case QMetaType_QTime:
            property.write(this, vv.toTime());
            break;
        case QMetaType_QDateTime:
            property.write(this, vv.toDateTime());
            break;
        case QMetaType_QUuid:
            property.write(this, vv.toUuid());
            break;
        case QMetaType_QUrl:
            property.write(this, vv.toUrl());
            break;
        case QMetaType_Int:
            property.write(this, vv.toInt());
            break;
        case QMetaType_LongLong:
            property.write(this, vv.toLongLong());
            break;
        case QMetaType_Double:
            property.write(this, vv.toDouble());
            break;
        case QMetaType_ULongLong:
            property.write(this, vv.toULongLong());
            break;
        case QMetaType_UInt:
            property.write(this, vv.toUInt());
            break;
        case QMetaType_Bool:
            property.write(this, vv.toBool());
            break;
        default:
            property.write(this, vv);
            break;
        }
    }
    return*this;
}

void MULoginToken::clear()
{
    this->setIat({});
    this->setExp({});
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

