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

    explicit MUNetworkActivity();

    ~MUNetworkActivity();

    QWebSocket m_socket;
    QString hostName;
    int port=0;
    QList<QTimer*> lst_timerInterface;

    void run();
public slots:
    virtual void onCheckInterface();

    virtual void onCheckService();

    virtual void onCheckBackoffice();
private:
    bool interfaceIsWorking();

    bool serviceIsWorking();

    bool backOfficeIsWorking();

signals:

    void localActivity(const bool isWorking);
    void serviceActivity(const bool isWorking);
    void backOfficeActivity(const bool isWorking);

};
