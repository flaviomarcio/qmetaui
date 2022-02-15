#include "./p_mu_request_response.h"

MURequestResponse::MURequestResponse()
{
}

MURequestResponse::MURequestResponse(MURequest &request)
{
    this->request=&request;
    this->request_method = request.method();
    this->request_header = request.header();
    this->request_body = request.body();
    this->request_url = request.url();
}

MURequestResponse::MURequestResponse(const QVariantMap &response)
{
    this->fromMap(response);
}

QVariantMap MURequestResponse::toMap()
{
    return qvm{
        {qsl("timeout"), this->timeout},
        {qsl("request_url"), this->request_url},
        {qsl("request_header"), this->request_header},
        {qsl("request_body"), this->request_body},
        {qsl("response_header"), this->response_header},
        {qsl("response_status_code"), this->response_status_code},
        {qsl("response_status_reason_phrase"), this->response_status_reason_phrase},
        {qsl("response_qt_status_code"), this->response_qt_status_code},
        {qsl("response_body"), this->response_body}
    };
}

void MURequestResponse::fromMap(const QVariantMap &response)
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

bool MURequestResponse::isOk()
{
    return this->response_qt_status_code==QNetworkReply::NoError;
}

bool MURequestResponse::isUnAuthorized()//https://developer.mozilla.org/pt-BR/docs/Web/HTTP/Status
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

bool MURequestResponse::isNetworkFail()//https://developer.mozilla.org/pt-BR/docs/Web/HTTP/Status
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

bool MURequestResponse::isNetworkError()
{
    auto q_network_error=this->response_qt_status_code;
    auto stateCode=this->response_status_code;
    if(stateCode>=400 && stateCode<=499)
        return true;

    if(q_network_error>=202 and q_network_error<=299)
        return true;

    return false;
}

QVariantMap MURequestResponse::toMapResquest()
{
    auto&response=*this;
    auto request_method=MUEnumRequestMethodName.value(response.request_method).toUpper();
    auto request_url=response.request_url;
    auto request_body=QString(response.request_body);
    auto request_header=response.request_header;
    auto response_body=response.response_body.toString();
    auto map=qvm{
        {qsl("url"), request_url},
        {qsl("method"), request_method},
        {qsl("header"), request_header},
        {qsl("body"), request_body},
        {qsl("start"), this->request_start}
    };

    QStringList headers;
    QHashIterator<QString, QVariant> i(request_header);
    while (i.hasNext()) {
        i.next();
        auto k=i.key();
        auto v=i.value().toString();
        headers<<qsl("-H '%1: %2'").arg(k).arg(v);
    }
    request_body=response_body.trimmed().isEmpty()?qsl_null:qsl("-d '%1'").arg(response_body);
    auto curl=qsl("curl -i -X %1 %2 %3 %4").arg(request_method).arg(request_url.toString()).arg(headers.join(' ')).arg(request_body).trimmed();

    map.insert(qsl("curl"), curl);

    return map;
}

QVariantMap MURequestResponse::toMapResponse()
{
    auto&response=*this;
    return qvm{
        {qsl("finish"), QDateTime::currentDateTime()},
        {qsl("header"), response.response_header},
        {qsl("status_code"), response.response_status_code},
        {qsl("qt_status_code"), response.response_qt_status_code},
        {qsl("status_reason_phrase"), response.response_status_reason_phrase},
        {qsl("body"), QJsonDocument::fromJson(response.response_body.toByteArray()).toVariant()}
    };
}

QVariantMap MURequestResponse::toMapLog()
{
    return qvm{{qsl("resquest"), this->toMapResquest()}, {qsl("response"), this->toMapResponse()}};
}

QVariantList MURequestResponse::toList()
{
    return qvl{
        qvh{{qsl("resquest"), this->toMapResquest()}},
        qvh{{qsl("response"), this->toMapResponse()}}
    };
}
