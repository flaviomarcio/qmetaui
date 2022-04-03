#pragma once

#include <QCoreApplication>
#include <QDir>
#include <QStm>
#include "./p_mu_request_response.h"

class Q_MU_EXPORT MURequestJob : public QThread
{
    Q_OBJECT
public:
    QString fileLog;
    QNetworkReply *reply = nullptr;
    QNetworkAccessManager*networkAccessManager=nullptr;
    MURequestResponse response;

    explicit MURequestJob();

    ~MURequestJob();

    QUrl url()const;

    void writeLog(MURequestResponse&response, const QVariantList&request);

    void connectDinit();

    void networkInit();

    void networkDInit();

    void run();

    MURequestJob &start();

    void quit();

public slots:

    void onReplyFinish(QNetworkReply*r);

    void onReplyError(QNetworkReply::NetworkError e);

    void onReplyTimeout();

    void onReplyCancel();

    void onRequestFinish();

    void onRequestSend(MURequest*muRequest);

signals:
    void requestSend(MURequest*muRequest);
    void finishRequest(MURequest*request, const QVariantHash&vResponse);
    void finishThread(MURequestJob*job);

};
