#include "./mu_application.h"
#include "./mu_register.h"
#include "./mu_notification.h"
#include <QApplication>

Q_GLOBAL_STATIC(QList<MUApplicationMethodInit>, methodInit);
Q_GLOBAL_STATIC(MUApplication, muApplication);


static QQmlApplicationEngine*static_engine=nullptr;

MUApplication::MUApplication(QObject *parent) : QObject(parent)
{
    QObject::connect(this, &MUApplication::notify, &MUNotification::i(), &MUNotification::notify);
}

MUApplication::MUApplication(const MUApplication &parent) : QObject(nullptr)
{
    foreach( const auto &prop, parent.dynamicPropertyNames() )
        setProperty( prop.constData(), parent.property( prop.constData() ) );
}

MUApplication &MUApplication::i()
{
    return*muApplication;
}

QQmlApplicationEngine &MUApplication::engine()
{
    return*static_engine;
}

QQmlApplicationEngine &MUApplication::engine(QQmlApplicationEngine &v)
{
    if(static_engine!=nullptr)
        return*static_engine;
    static_engine=&v;
    v.rootContext()->setContextProperty(qsl("qApp"), QApplication::instance());
    MURegister::init(v);
    for(auto&method:*methodInit)
        method();
    return*(static_engine=&v);
}

void MUApplication::initMethodOnLoadEngine(MUApplicationMethodInit method)
{
    methodInit->append(method);
}
