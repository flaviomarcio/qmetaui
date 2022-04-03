#include "./p_mu_network_activity.h"

MUNetworkActivity::MUNetworkActivity() : QThread{nullptr}
{
    this->moveToThread(this);
}

MUNetworkActivity::~MUNetworkActivity()
{
}

void MUNetworkActivity::run(){

    auto doRun=[this](){
        {
            auto timer=new QTimer(nullptr);
            timer->setInterval(5000);
            QObject::connect(timer, &QTimer::timeout, this, &MUNetworkActivity::onCheckInterface);
            lst_timerInterface<<timer;
        }

        {
            auto timer=new QTimer(nullptr);
            timer->setInterval(10000);
            QObject::connect(timer, &QTimer::timeout, this, &MUNetworkActivity::onCheckService);
            lst_timerInterface<<timer;
        }

        {
            auto timer=new QTimer(nullptr);
            timer->setInterval(10000);
            QObject::connect(timer, &QTimer::timeout, this, &MUNetworkActivity::onCheckBackoffice);
            lst_timerInterface<<timer;
        }

        for(auto&timer:lst_timerInterface)
            timer->start();

    };
    QTimer::singleShot(1, this, doRun);
    this->exec();
    for(auto&timer:lst_timerInterface){
        timer->stop();
        timer->deleteLater();
    }
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
    auto interfaces = QNetworkInterface::allInterfaces();
    for (auto& i : interfaces){
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
