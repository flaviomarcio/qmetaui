#pragma once

#include "../mu_request.h"

#include <QObject>
#include <QThread>
#include <QCborMap>
#include <QtCborCommon>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QNetworkReply>
#include <QUuid>
#include <QDebug>
#include <QMutex>
#include <QEventLoop>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QTimer>
#include <QThread>
#include <QUrl>

struct MURequestResponse{
public:
    MUEnumRequest::Method request_method=MUEnumRequest::Method::rmGet;
    MURequest*request=nullptr;
    QDateTime request_start;
    QDateTime request_finish;
    qlonglong timeout=30000;
    QUrl request_url;
    QVariantHash request_header;
    QByteArray request_body;
    QVariantHash response_header;
    int response_status_code = 0;
    QString response_status_reason_phrase;
    QVariant response_body;
    QNetworkReply::NetworkError response_qt_status_code = QNetworkReply::UnknownNetworkError;

    explicit MURequestResponse();

    explicit MURequestResponse(MURequest&request);

    explicit MURequestResponse(const QVariantMap&response);

public:
    QVariantMap toMap();

    void fromMap(const QVariantMap&response);

    bool isOk();

    bool isUnAuthorized();

    bool isNetworkFail();

    bool isNetworkError();

    QVariantMap toMapResquest();

    QVariantMap toMapResponse();

    QVariantMap toMapLog();

    QVariantList toList();

};
