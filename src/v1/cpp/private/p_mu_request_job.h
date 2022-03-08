#pragma once

#include <QCoreApplication>
#include <QDir>
#include "./p_mu_request_response.h"

static bool _MuLogRegister=false;
static auto _MuLogDirBase=QString("%1/QMetaUiLog").arg(QDir::homePath());
static auto _MuLogDir=_MuLogDirBase;

static void _MuLogClearDir(const QString&ormLogDir){
    QStringList dir_found;
    QStringList dir_rm_file;
    dir_found.append(ormLogDir);
    while(!dir_found.isEmpty()){
        auto scanDir = dir_found.takeFirst();
        dir_rm_file.append(scanDir);
        QDir dir(scanDir);
        if(dir.exists(scanDir)){
            dir.setFilter(QDir::AllDirs);
            for(auto&scanInDir:dir.entryList()){
                if(scanInDir=="." || scanInDir=="..")
                    continue;
                else{
                    auto dir=QString("%1/%2").arg(scanDir).arg(scanInDir);
                    dir_rm_file.append(dir);
                    dir_found.append(dir);
                }
            }
        }
    }

    auto ext=QStringList()<<"*.*";
    for(auto&sdir:dir_rm_file){
        QDir scanDir(sdir);
        if(scanDir.exists()){
            scanDir.setFilter(QDir::Drives | QDir::Files);
            scanDir.setNameFilters(ext);
            for(auto&dirFile : scanDir.entryList()){
                auto fileName=sdir+"/"+dirFile;
                QFile::remove(fileName);
            }
        }
    }
}

static void _MuInitLogDir(){
    auto env = QString(getenv("logRegister")).trimmed();
#ifdef QT_DEBUG
    _MuLogRegister = env.isEmpty()?true :QVariant(env).toBool();
#else
    _MuLogRegister = env.isEmpty()?false:QVariant(env).toBool();
#endif
    if(_MuLogRegister){
        _MuLogDir=QStringLiteral("%1/%2").arg(_MuLogDirBase).arg(qApp->applicationName());
        QDir dir(_MuLogDir);
        if(!dir.exists(_MuLogDir))
            dir.mkpath(_MuLogDir);
        if(dir.exists(_MuLogDir)){
            _MuLogClearDir(_MuLogDir);
        }
    }
}

Q_COREAPP_STARTUP_FUNCTION(_MuInitLogDir);

class Q_MU_EXPORT MURequestJob : public QThread
{
    Q_OBJECT
public:
    QString fileLog;
    QNetworkReply *reply = nullptr;
    QNetworkAccessManager*networkAccessManager=nullptr;
    MURequestResponse response;
    QUrl url()const{
        return response.request_url.toString();
    }
    explicit MURequestJob():QThread(nullptr)
    {
        this->fileLog=QStringLiteral("%1/%2.log").arg(_MuLogDir).arg(QString::number(qlonglong(QThread::currentThreadId()),16));
        static qlonglong taskCount=0;
        ++taskCount;
        this->setObjectName(QStringLiteral("MUReqJob%1").arg(taskCount));
        this->moveToThread(this);
    }
    ~MURequestJob()
    {
    }

    void writeLog(MURequestResponse&response, const QVariantList&request)
    {
        if(!_MuLogRegister)
            return;
        if(request.isEmpty())
            return;
        QFile file(this->fileLog);
        if (file.open(QIODevice::Append | QIODevice::WriteOnly | QIODevice::Text))
            return;

        QTextStream outText(&file);
        auto request_method=MUEnumRequestMethodName.value(response.request_method).toUpper();
        outText << request_method<<QStringLiteral(": ")<<response.request_url.toString()<<'\n';
        outText << QJsonDocument::fromVariant(request).toJson(QJsonDocument::Indented);
        outText << '\n';
        outText << '\n';
        file.flush();
        file.close();
    }

    void connectDinit()
    {
        if(this->reply!=nullptr){
#if QT_VERSION >= QT_VERSION_CHECK(5, 15, 0)
            QObject::disconnect(this->reply, QOverload<QNetworkReply::NetworkError>::of(&QNetworkReply::errorOccurred), this, &MURequestJob::on_reply_error);
#else
            QObject::disconnect(this->reply, QOverload<QNetworkReply::NetworkError>::of(&QNetworkReply::error), this, &MURequestJob::on_reply_error);
#endif
        }
        if(this->networkAccessManager!=nullptr)
            QObject::disconnect(this->networkAccessManager, &QNetworkAccessManager::finished, this, &MURequestJob::on_reply_finish);
    }

    void networkInit()
    {
        this->networkDInit();
        if(this->networkAccessManager==nullptr){
            this->networkAccessManager=new QNetworkAccessManager(nullptr);
            QObject::connect(this->networkAccessManager, &QNetworkAccessManager::finished, this, &MURequestJob::on_reply_finish);
        }
    }

    void networkDInit()
    {
        connectDinit();
        if(this->networkAccessManager!=nullptr){
            delete this->networkAccessManager;
            this->networkAccessManager=nullptr;
        }
        this->reply=nullptr;
    }

    void run()
    {
        QObject::connect(this, &MURequestJob::requestSend, this, &MURequestJob::onRequestSend, Qt::QueuedConnection);
        this->exec();

        QObject::disconnect(this, &MURequestJob::requestSend, this, &MURequestJob::onRequestSend);
        emit finishThread(this);
        this->networkDInit();
    }

    auto start()
    {
        if(!this->isRunning()){
            QThread::start();
            while(this->eventDispatcher()==nullptr)
                QThread::msleep(1);
        }
        return this;
    }

    void quit()
    {
        this->connectDinit();
        QThread::quit();
    }

public slots:

    void on_reply_finish(QNetworkReply*r)
    {
        response.response_qt_status_code=r->error();
        this->onRequestFinish();
    };

    void on_reply_error(QNetworkReply::NetworkError e)
    {
        this->response.response_qt_status_code=e;
        this->onRequestFinish();
    };
    void on_reply_timeout()
    {
        this->response.response_qt_status_code=QNetworkReply::TimeoutError;
        this->onRequestFinish();
    };
    void on_reply_cancel()
    {
        this->response.response_qt_status_code=QNetworkReply::OperationCanceledError;
        this->onRequestFinish();
    };

    void onRequestFinish()
    {
        response.request_finish=QDateTime::currentDateTime();
        this->connectDinit();
#if Q_MU_LOG_VERBOSE
        mWarning()<<QString(":response.url(%1)").arg(reply->url().toString());
#endif

        if(this->reply!=nullptr){
            auto qt_stt=response.response_qt_status_code;
            if(qt_stt!=QNetworkReply::TimeoutError && qt_stt!=QNetworkReply::OperationCanceledError){

                response.response_body = QString(reply->readAll());
                response.response_status_code = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
                response.response_status_reason_phrase = reply->attribute(QNetworkRequest::HttpReasonPhraseAttribute).toString();
                if(qt_stt==QNetworkReply::NoError){
                    if(response.response_status_code!=200){
                        response.response_qt_status_code=QNetworkReply::NetworkError(response.response_status_code);
                    }
                }


#if Q_MU_LOG_SUPER_VERBOSE
                for (auto rawHeader : reply->rawHeaderPairs()) {
                    mWarning()<<QString(":response.rawHeader(%1, %2)").arg(QString(rawHeader.first)).arg(QString(rawHeader.second));
                }
                mWarning()<<QString(":response.statusCode(%1, %2)").arg(response.response_status_code).arg(QString(response.response_status_reason_phrase));
                mWarning()<<QString(":response.qtStatusCode(%1)").arg(response.response_qt_status_code );
                mWarning()<<QString(":response.body(%1)").arg( response.response_body.toString() );
#endif
            }
            {
                this->reply->abort();
                this->reply->deleteLater();
                this->reply=nullptr;
            }
        }

        auto vResponse=this->response.toMap();
        emit finishRequest(response.request, vResponse);
        this->writeLog(this->response, this->response.toList());
    }

    void onRequestSend(MURequest*muRequest)
    {
        this->response.request_start=QDateTime::currentDateTime();
        this->networkInit();
        this->response=MURequestResponse(*muRequest);

        auto method      = response.request_method;
        auto request_url = this->response.request_url.toString();

        if(method==MUEnumRequest::Method::rmGet || method==MUEnumRequest::Method::rmDelete){
            QVariantMap requestMap = muRequest->bodyMap();
            QStringList parameters;
            QMapIterator<QString, QVariant> i(requestMap);
            while (i.hasNext()){
                i.next();
                parameters<<QStringLiteral("%1=%2").arg(i.key()).arg(i.value().toString());
            }
            if(!parameters.isEmpty())
                request_url+=QStringLiteral("?%1").arg(parameters.join(','));
        }

        QUrl url(request_url);
        QNetworkRequest request(url);

        auto contentType=QByteArrayLiteral("application/x-www-form-urlencoded");

        switch (muRequest->requestAppType()) {
        case MUEnumRequest::AppType::atCBor:
            contentType=QByteArrayLiteral("application/cbor");
            break;
        case MUEnumRequest::AppType::atJson:
            contentType=QByteArrayLiteral("application/json");
            break;
        case MUEnumRequest::AppType::atXml:
            contentType=QByteArrayLiteral("application/xml");
            break;
        case MUEnumRequest::AppType::atBinary:
            contentType=QByteArrayLiteral("application/binary");
            break;
        default:
            break;
        }
        request.setHeader(QNetworkRequest::ContentTypeHeader, contentType);

#if Q_MU_LOG
        mWarning()<<QStringLiteral(":request.url(%1)").arg(request_url);
#endif
        QMapIterator<QString, QVariant> i(response.request_header);
        while (i.hasNext()) {
            i.next();
            auto k=i.key().toUtf8();
            auto v=i.value().toByteArray();
            request.setRawHeader(k, v);
#if Q_MU_LOG_VERBOSE
            mWarning()<<QString(":request.rawHeader(%1, %2)").arg(QString(k)).arg(QString(v));
#endif
        }

#if Q_MU_LOG_SUPER_VERBOSE
        mWarning()<<QStringLiteral(":request.method(%1)").arg(QString(response.request_method));
        mWarning()<<QStringLiteral(":request.body(%1)").arg(QString(response.request_body));
#endif

        switch (method) {
        case MUEnumRequest::Method::rmHead:
            reply=networkAccessManager->get(request);
            break;
        case MUEnumRequest::Method::rmGet:
            reply=networkAccessManager->head(request);
            break;
        case MUEnumRequest::Method::rmPost:
            reply=networkAccessManager->post(request, response.request_body);
            break;
        case MUEnumRequest::Method::rmPut:
            reply=networkAccessManager->put(request, response.request_body);
            break;
        case MUEnumRequest::Method::rmDelete:
            reply=networkAccessManager->deleteResource(request);
            break;
        default:
            delete reply;
            reply=nullptr;
        }

        if(reply==nullptr){
            response.response_status_code=QNetworkReply::UnknownServerError;
            response.response_body.clear();
            return;
        }
        reply->ignoreSslErrors();
#if (QT_VERSION >= QT_VERSION_CHECK(5, 15, 0))
        QObject::connect(reply, QOverload<QNetworkReply::NetworkError>::of(&QNetworkReply::errorOccurred), this, &MURequestJob::on_reply_error);
#else
        QObject::connect(reply, QOverload<QNetworkReply::NetworkError>::of(&QNetworkReply::error), this, &MURequestJob::on_reply_error);
#endif

        for(auto&v:reply->rawHeaderPairs()){
            response.response_header.insert(v.first, v.second);
        }
    }

signals:
    void requestSend(MURequest*muRequest);
    void finishRequest(MURequest*request, const QVariantMap&vResponse);
    void finishThread(MURequestJob*job);

};
