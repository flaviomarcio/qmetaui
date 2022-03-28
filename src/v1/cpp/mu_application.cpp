#include "./mu_application.h"
#include "./mu_register.h"
#include "./mu_notification.h"
#include <QApplication>
#include <QStm>

Q_GLOBAL_STATIC(QList<MUApplicationMethodInit>, __methodInit);

static auto&methodInit=*__methodInit;

static QQmlApplicationEngine*static_engine=nullptr;

MUApplication::MUApplication(QObject *parent) : QObject{parent}
{
    QObject::connect(this, &MUApplication::notify, &MUNotification::i(), &MUNotification::notify);
}

MUApplication::MUApplication(const MUApplication &parent) : QObject{nullptr}{
    Q_FOREACH( const QByteArray & prop, parent.dynamicPropertyNames() )
        setProperty( prop.constData(), parent.property( prop.constData() ) );
}

MUApplication &MUApplication::i()
{
    static MUApplication*__MUApplication=nullptr;
    if(__MUApplication==nullptr){
        __MUApplication=new MUApplication(nullptr);
    }
    return*__MUApplication;
}

QQmlApplicationEngine &MUApplication::engine()
{
    return*static_engine;
}

QQmlApplicationEngine &MUApplication::engine(QQmlApplicationEngine &v)
{
    if(static_engine==nullptr){
        static_engine=&v;
        v.rootContext()->setContextProperty(qsl("qApp"), QApplication::instance());
        MURegister::init(v);
        for(auto&v:methodInit)
            v();
    }
    return*static_engine;
}

void MUApplication::initMethodOnLoadEngine(MUApplicationMethodInit method)
{
    methodInit.append(method);
}
