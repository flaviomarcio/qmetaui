#pragma once

#include "../mu_global.h"
#include <QtWebSockets/QWebSocket>
#include <QTcpSocket>
#include <QObject>
#include <QThread>
#include <QTimer>
#include <QUrl>
#if QT_VERSION >= QT_VERSION_CHECK(5, 15, 0)
#include <QNetworkInterface>
#else
#include <QNetworkConfigurationManager>
#endif

class Q_MU_EXPORT MUNetworkActivity : public QThread
{
    Q_OBJECT
public:

//    class Action{

//    };

    explicit MUNetworkActivity():QThread(nullptr){
        this->moveToThread(this);
    }
    ~MUNetworkActivity(){
    }

    QWebSocket m_socket;
    QString hostName;
    int port=0;

    void run(){
        QList<QTimer*> lst_timerInterface;
        auto doRun=[&lst_timerInterface, this](){
            {
                auto timer=new QTimer(nullptr);
                timer=new QTimer(nullptr);
                timer->setInterval(5000);
                QObject::connect(timer, &QTimer::timeout, this, &MUNetworkActivity::on_check_interface);
                lst_timerInterface<<timer;
            }

            {
                auto timer=new QTimer(nullptr);
                timer->setInterval(10000);
                QObject::connect(timer, &QTimer::timeout, this, &MUNetworkActivity::on_check_service);
                lst_timerInterface<<timer;
            }

            {
                auto timer=new QTimer(nullptr);
                timer->setInterval(10000);
                QObject::connect(timer, &QTimer::timeout, this, &MUNetworkActivity::on_check_backoffice);
                lst_timerInterface<<timer;
            }

            for(auto&timer:lst_timerInterface)
                timer->start();

        };
        QTimer::singleShot(1, doRun);
        this->exec();
        for(auto&timer:lst_timerInterface){
            timer->stop();
            timer->deleteLater();
        }
    }
public slots:
    virtual void on_check_interface()
    {
        if(port>0)
            emit localActivity(this->interfaceIsWorking());
    }

    virtual void on_check_service()
    {
        if(port>0)
            this->serviceActivity(this->serviceIsWorking());
    }

    virtual void on_check_backoffice()
    {
        if(port>0)
            this->backOfficeActivity(this->backOfficeIsWorking());
    }
private:
    bool interfaceIsWorking(){
#if QT_VERSION >= QT_VERSION_CHECK(5, 15, 0)
        QList<QNetworkInterface> interfaces = QNetworkInterface::allInterfaces();
        for (QNetworkInterface i : interfaces){
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

    bool serviceIsWorking()
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

    bool backOfficeIsWorking()
    {
        return this->interfaceIsWorking();
    }

signals:

    void localActivity(const bool isWorking);
    void serviceActivity(const bool isWorking);
    void backOfficeActivity(const bool isWorking);

};
