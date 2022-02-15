#pragma once

#include "../mu_global.h"
#include <QObject>
#include <QThread>
#include <QTimer>
#include <QUrl>


class Q_MU_EXPORT MUNetworkActivity : public QThread
{
    Q_OBJECT
public:
    QTimer*timer=nullptr;
    QString hostName;
    int port=0;

    explicit MUNetworkActivity();

    ~MUNetworkActivity();

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
