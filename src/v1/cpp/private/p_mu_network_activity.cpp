#include "./p_mu_network_activity.h"
#include <QTcpSocket>

#if QT_VERSION >= QT_VERSION_CHECK(5, 15, 0)
#include <QNetworkInterface>
#else
#include <QNetworkConfigurationManager>
#endif

MUNetworkActivity::MUNetworkActivity():QThread(nullptr)
{
    this->moveToThread(this);
}

MUNetworkActivity::~MUNetworkActivity()
{
}

void MUNetworkActivity::run()
{
    auto doRun=[this](){
        this->timer=new QTimer(nullptr);
        this->timer->setInterval(10000);
        QObject::connect(this->timer, &QTimer::timeout, this, &MUNetworkActivity::onCheckInterface);
        QObject::connect(this->timer, &QTimer::timeout, this, &MUNetworkActivity::onCheckService);
        QObject::connect(this->timer, &QTimer::timeout, this, &MUNetworkActivity::onCheckBackoffice);
        this->timer->start();

    };
    QTimer::singleShot(1, this, doRun);
    this->exec();
    this->timer->stop();
    this->timer->deleteLater();
    this->timer=nullptr;
}

void MUNetworkActivity::onCheckInterface()
{
    if(port>0)
        emit localActivity(this->interfaceIsWorking());
}

void MUNetworkActivity::onCheckService()
{
    if(port>0)
        emit this->serviceActivity(this->serviceIsWorking());
}

void MUNetworkActivity::onCheckBackoffice()
{
    if(port>0)
        emit this->backOfficeActivity(this->backOfficeIsWorking());
}

bool MUNetworkActivity::interfaceIsWorking(){
#if QT_VERSION >= QT_VERSION_CHECK(5, 15, 0)
    QList<QNetworkInterface> interfaces = QNetworkInterface::allInterfaces();
    for (auto&i:interfaces){
        if(i.flags().testFlag(i.IsUp))
            return true;
    }
#else
    QNetworkConfigurationManager mgr;
    if(mgr.isOnline()){
        auto activeConfigs = mgr.allConfigurations(QNetworkConfiguration::Active);
        for(auto&cnn:activeConfigs){
            if(cnn.type()==cnn.InternetAccessPoint)
                return true;
        }
    }
#endif

    return false;
}

bool MUNetworkActivity::serviceIsWorking()
{
    if(this->interfaceIsWorking())
        return false;

    QTcpSocket m_socket(this);
    m_socket.connectToHost(hostName, port);
    if(!m_socket.waitForConnected(2000))
        return false;

    m_socket.close();
    return true;
}

bool MUNetworkActivity::backOfficeIsWorking()
{
    return this->interfaceIsWorking();
}
