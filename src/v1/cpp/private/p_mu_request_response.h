#ifndef MURequestResponse_H
#define MURequestResponse_H

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
    QVariantMap request_header;
    QByteArray request_body;
    QVariantMap response_header;
    int response_status_code = 0;
    QString response_status_reason_phrase;
    QVariant response_body;
    QNetworkReply::NetworkError response_qt_status_code = QNetworkReply::UnknownNetworkError;
public:
    QVariantMap toMap()
    {
        QVariantMap response;

        response.insert("timeout",this->timeout);
        response.insert("request_url",this->request_url);
        response.insert("request_header",this->request_header);
        response.insert("request_body",this->request_body);
        response.insert("response_header",this->response_header);
        response.insert("response_status_code",this->response_status_code);
        response.insert("response_status_reason_phrase",this->response_status_reason_phrase);
        response.insert("response_qt_status_code",this->response_qt_status_code);
        response.insert("response_body",this->response_body);

        return response;
    }
    void fromMap(const QVariantMap&response)
    {

        this->timeout=response.value("timeout").toLongLong();
        this->request_url=response.value("request_url").toUrl();
        this->request_header=response.value("request_header").toMap();
        this->request_body=response.value("request_body").toByteArray();
        this->response_header=response.value("response_header").toMap();
        this->response_status_code=response.value("response_status_code").toInt();
        this->response_status_reason_phrase=response.value("response_status_reason_phrase").toString();
        this->response_qt_status_code=QNetworkReply::NetworkError(response.value("response_qt_status_code").toInt());
        this->response_body=response.value("response_body").toByteArray();
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
        map.insert(QStringLiteral("url"), request_url);
        map.insert(QStringLiteral("method"), request_method);
        map.insert(QStringLiteral("header"), request_header);
        map.insert(QStringLiteral("body"), request_body);
        map.insert(QStringLiteral("start"), this->request_start);

        QStringList headers;
        QMapIterator<QString, QVariant> i(request_header);
        while (i.hasNext()) {
            i.next();
            auto k=i.key();
            auto v=i.value().toString();
            headers<<QStringLiteral("-H '%1: %2'").arg(k).arg(v);
        }
        request_body=response_body.trimmed().isEmpty()?"":QStringLiteral("-d '%1'").arg(QString(response_body));
        auto curl=QStringLiteral("curl -i -X %1 %2 %3 %4").arg(request_method).arg(request_url.toString()).arg(headers.join(' ')).arg(request_body).trimmed();

        map.insert(QStringLiteral("curl"), curl);

        return map;
    }

    QVariantMap toMapResponse()
    {
        auto&response=*this;
        QVariantMap map;
        map.insert(QStringLiteral("finish"), QDateTime::currentDateTime());
        map.insert(QStringLiteral("header"), response.response_header);
        map.insert(QStringLiteral("status_code"), response.response_status_code);
        map.insert(QStringLiteral("qt_status_code"), response.response_qt_status_code);
        map.insert(QStringLiteral("status_reason_phrase"), response.response_status_reason_phrase);
        map.insert(QStringLiteral("body"), QJsonDocument::fromJson(response.response_body.toByteArray()).toVariant());
        return map;
    }

    QVariantMap toMapLog()
    {
        QVariantMap map;
        map.insert(QStringLiteral("resquest"), this->toMapResquest());
        map.insert(QStringLiteral("response"), this->toMapResponse());
        return map;
    }

    QVariantList toList()
    {
        QVariantList list;
        QVariantMap map;

        map.clear();
        map.insert(QStringLiteral("resquest"), this->toMapResquest());
        list<<map;
        map.clear();
        map.insert(QStringLiteral("response"), this->toMapResponse());
        list<<map;
        return list;
    }

};





#endif // MURequestResponse_H
