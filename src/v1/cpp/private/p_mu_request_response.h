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
#include <QStm>

struct MURequestResponse{
public:
    explicit MURequestResponse(){
    }
    explicit MURequestResponse(MURequest&request)
    {

        this->request=&request;
        this->request_method = request.method();
        this->request_header = request.header();
        this->request_body = request.body();
        this->request_url = request.url();
    }

    explicit MURequestResponse(const QVariantMap&response)
    {
        this->fromMap(response);
    }

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
public:
    QVariantMap toMap()
    {
        QVariantMap response;

        response.insert(qsl("timeout"),this->timeout);
        response.insert(qsl("request_url"),this->request_url);
        response.insert(qsl("request_header"),this->request_header);
        response.insert(qsl("request_body"),this->request_body);
        response.insert(qsl("response_header"),this->response_header);
        response.insert(qsl("response_status_code"),this->response_status_code);
        response.insert(qsl("response_status_reason_phrase"),this->response_status_reason_phrase);
        response.insert(qsl("response_qt_status_code"),this->response_qt_status_code);
        response.insert(qsl("response_body"),this->response_body);

        return response;
    }
    void fromMap(const QVariantMap&response)
    {

        this->timeout=response.value(qsl("timeout")).toLongLong();
        this->request_url=response.value(qsl("request_url")).toUrl();
        this->request_header=response.value(qsl("request_header")).toHash();
        this->request_body=response.value(qsl("request_body")).toByteArray();
        this->response_header=response.value(qsl("response_header")).toHash();
        this->response_status_code=response.value(qsl("response_status_code")).toInt();
        this->response_status_reason_phrase=response.value(qsl("response_status_reason_phrase")).toString();
        this->response_qt_status_code=QNetworkReply::NetworkError(response.value(qsl("response_qt_status_code")).toInt());
        this->response_body=response.value(qsl("response_body")).toByteArray();
    }

    bool isOk()
    {
        return this->response_qt_status_code==QNetworkReply::NoError;
    }

    bool isUnAuthorized()//https://developer.mozilla.org/pt-BR/docs/Web/HTTP/Status
    {
        auto q_network_error=this->response_qt_status_code;
        auto stateCode=this->response_status_code;
        if(stateCode==401)
            return true;

        if(q_network_error==QNetworkReply::ContentAccessDenied)
            return true;

        if(q_network_error==QNetworkReply::AuthenticationRequiredError)
            return true;

        if(q_network_error==201)// network layer errors [relating to the destination server] (1-99):
            return true;
        return false;
    }

    bool isNetworkFail()//https://developer.mozilla.org/pt-BR/docs/Web/HTTP/Status
    {
        auto q_network_error=this->response_qt_status_code;
        auto stateCode=this->response_status_code;
        if(stateCode>=500 && stateCode<=599)
            return true;

        if(q_network_error==QNetworkReply::ServiceUnavailableError || q_network_error==QNetworkReply::UnknownServerError)
            return true;

        if(q_network_error>=1 and q_network_error<=99)// network layer errors [relating to the destination server] (1-99):
            return true;

        if(q_network_error>=101 and q_network_error<=199)//proxy error
            return true;

        if(q_network_error>=301 and q_network_error<=399)//protocol error
            return true;

        return false;
    }

    bool isNetworkError()
    {
        auto q_network_error=this->response_qt_status_code;
        auto stateCode=this->response_status_code;
        if(stateCode>=400 && stateCode<=499)
            return true;

        if(q_network_error>=202 and q_network_error<=299)
            return true;

        return false;
    }

    QVariantMap toMapResquest()
    {
        auto&response=*this;
        QVariantMap map;
        auto request_method=MUEnumRequestMethodName.value(response.request_method).toUpper();
        auto request_url=response.request_url;
        auto request_body=QString(response.request_body);
        auto request_header=response.request_header;
        auto response_body=response.response_body.toString();
        map.insert(qsl("url"), request_url);
        map.insert(qsl("method"), request_method);
        map.insert(qsl("header"), request_header);
        map.insert(qsl("body"), request_body);
        map.insert(qsl("start"), this->request_start);

        QStringList headers;
        QHashIterator<QString, QVariant> i(request_header);
        while (i.hasNext()) {
            i.next();
            auto k=i.key();
            auto v=i.value().toString();
            headers<<qsl("-H '%1: %2'").arg(k).arg(v);
        }
        request_body=response_body.trimmed().isEmpty()?"":qsl("-d '%1'").arg(response_body);
        auto curl=qsl("curl -i -X %1 %2 %3 %4").arg(request_method, request_url.toString(), headers.join(' '), request_body);

        map.insert(qsl("curl"), curl);

        return map;
    }

    QVariantMap toMapResponse()
    {
        auto&response=*this;
        QVariantMap map;
        map.insert(qsl("finish"), QDateTime::currentDateTime());
        map.insert(qsl("header"), response.response_header);
        map.insert(qsl("status_code"), response.response_status_code);
        map.insert(qsl("qt_status_code"), response.response_qt_status_code);
        map.insert(qsl("status_reason_phrase"), response.response_status_reason_phrase);
        map.insert(qsl("body"), QJsonDocument::fromJson(response.response_body.toByteArray()).toVariant());
        return map;
    }

    QVariantMap toMapLog()
    {
        return {{qsl("resquest"), this->toMapResquest()}, {qsl("response"), this->toMapResponse()}};
    }

    QVariantList toList()
    {
        return QVariantList{qvh{{qsl("resquest"), this->toMapResquest()}, {qsl("response"), this->toMapResponse()}}};
    }

};
