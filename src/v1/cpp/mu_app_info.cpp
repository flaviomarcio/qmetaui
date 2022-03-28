#include "./mu_app_info.h"
#include <QString>
#include <QStm>

#define dPvt()\
    auto&p = *reinterpret_cast<MUAppInfoPvt*>(this->p)

class MUAppInfoPvt:public QObject{
public:

    bool    strong  = false;
    bool    show    = false;
    QString display = qsl("Magma Tecnologia");
    QString version = qsl("ws1.0");
    MUAppInfo*parent=nullptr;
    explicit MUAppInfoPvt(MUAppInfo*parent):QObject(parent){
        this->parent=parent;
    }
    virtual ~MUAppInfoPvt(){

    }
};

MUAppInfo::MUAppInfo(QObject *parent) : MUObject(parent)
{
    this->p=new MUAppInfoPvt(this);
}

MUAppInfo::~MUAppInfo(){
    dPvt();
    delete&p;
}

MUAppInfo &MUAppInfo::operator=(const MUAppInfo &v)
{
    this->fromHash(v.toHash());
    return*this;
}

MUAppInfo &MUAppInfo::operator=(const QVariant &v)
{
    this->fromHash(v.toHash());
    return*this;
}


bool MUAppInfo::strong() const
{
    dPvt();
    return p.strong;
}

void MUAppInfo::setStrong(bool strong)
{
    dPvt();
    p.strong = strong;
}

bool MUAppInfo::show() const
{
    dPvt();
    return p.show;
}

void MUAppInfo::setShow(bool show)
{
    dPvt();
    p.show = show;
}

QString MUAppInfo::display() const
{
    dPvt();
    return p.display;
}

void MUAppInfo::setDisplay(const QString &display)
{
    dPvt();
    p.display = display;
}

QString MUAppInfo::version() const
{
    dPvt();
    return p.version;
}

void MUAppInfo::setVersion(const QString &version)
{
    dPvt();
    p.version = version;
}
