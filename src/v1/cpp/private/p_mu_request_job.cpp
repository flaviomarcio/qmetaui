#include "./p_mu_request_job.h"
#include <QDir>

static const auto _muLogDirBase=qsl("%1/QMetaUiLog").arg(QDir::homePath());
static auto _muLogDir=qsl("%1/QMetaUiLog").arg(QDir::homePath());
static bool _muLogRegister=false;

static void _MuLogClearDir(const QString&ormLogDir)
{
    QStringList dir_found;
    QStringList dir_rm_file;
    dir_found.append(ormLogDir);
    while(!dir_found.isEmpty()){
        auto scanDir = dir_found.takeFirst();
        dir_rm_file.append(scanDir);
        QDir dir(scanDir);
        if(!dir.exists(scanDir))
            continue;
        dir.setFilter(QDir::AllDirs);
        for(auto&scanInDir:dir.entryList()){
            if(scanInDir==qsl(".") || scanInDir==qsl(".."))
                continue;
            auto dir=qsl("%1/%2").arg(scanDir, scanInDir);
            dir_rm_file.append(dir);
            dir_found.append(dir);
        }
    }

    static auto ext=QStringList{qsl("*.*")};
    for(auto&sdir:dir_rm_file){
        QDir scanDir(sdir);
        if(!scanDir.exists())
            continue;
        scanDir.setFilter(QDir::Drives | QDir::Files);
        scanDir.setNameFilters(ext);
        for(auto&dirFile : scanDir.entryList()){
            auto fileName=qsl("%1/%2").arg(sdir, dirFile);
            QFile::remove(fileName);
        }
    }
}

static void init()
{
    auto env = QString(getenv("logRegister")).trimmed();
#ifdef QT_DEBUG
    _muLogRegister = env.isEmpty()?true :QVariant(env).toBool();
#else
    _muLogRegister = env.isEmpty()?false:QVariant(env).toBool();
#endif
    if(!_muLogRegister)
        return;
    _muLogDir=qsl("%1/%2").arg(_muLogDirBase, qApp->applicationName());
    QDir dir(_muLogDir);
    if(!dir.exists(_muLogDir))
        dir.mkpath(_muLogDir);
    if(dir.exists(_muLogDir)){
        _MuLogClearDir(_muLogDir);
    }
}

Q_COREAPP_STARTUP_FUNCTION(init);


MURequestJob::MURequestJob():QThread(nullptr)
{
    this->fileLog=qsl("%1/%2.log").arg(_muLogDir, QString::number(qlonglong(QThread::currentThreadId()),16));
    static qlonglong taskCount=0;
    ++taskCount;
    this->setObjectName(qsl("MUReqJob%1").arg(taskCount));
    this->moveToThread(this);
}

MURequestJob::~MURequestJob()
{
}

QUrl MURequestJob::url() const
{
    return response.request_url.toString();
}

void MURequestJob::writeLog(MURequestResponse &response, const QVariantList &request)
{
    if(!_muLogRegister)
        return;

    if(request.isEmpty())
        return;

    QFile file(this->fileLog);
    if (file.open(QIODevice::Append | QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream outText(&file);
    auto request_method=MUEnumRequestMethodName.value(response.request_method).toUpper();
    outText << request_method<<qsl(": ")<<response.request_url.toString()<<'\n';
    outText << QJsonDocument::fromVariant(request).toJson(QJsonDocument::Indented);
    outText << '\n';
    outText << '\n';
    file.flush();
    file.close();
}

void MURequestJob::connectDinit()
{
    if(this->reply!=nullptr){
#if QT_VERSION >= QT_VERSION_CHECK(5, 15, 0)
        QObject::disconnect(this->reply, QOverload<QNetworkReply::NetworkError>::of(&QNetworkReply::errorOccurred), this, &MURequestJob::onReplyError);
#else
        QObject::disconnect(this->reply, QOverload<QNetworkReply::NetworkError>::of(&QNetworkReply::error), this, &MURequestJob::onReplyError);
#endif
    }
    if(this->networkAccessManager!=nullptr)
        QObject::disconnect(this->networkAccessManager, &QNetworkAccessManager::finished, this, &MURequestJob::onReplyFinish);
}

void MURequestJob::networkInit()
{
    this->networkDInit();
    if(this->networkAccessManager==nullptr){
        this->networkAccessManager=new QNetworkAccessManager(nullptr);
        QObject::connect(this->networkAccessManager, &QNetworkAccessManager::finished, this, &MURequestJob::onReplyFinish);
    }
}

void MURequestJob::networkDInit()
{
    connectDinit();
    if(this->networkAccessManager!=nullptr){
        delete this->networkAccessManager;
        this->networkAccessManager=nullptr;
    }
    this->reply=nullptr;
}

void MURequestJob::run()
{
    QObject::connect(this, &MURequestJob::requestSend, this, &MURequestJob::onRequestSend, Qt::QueuedConnection);
    this->exec();

    QObject::disconnect(this, &MURequestJob::requestSend, this, &MURequestJob::onRequestSend);
    emit finishThread(this);
    this->networkDInit();
}

MURequestJob&MURequestJob::start()
{
    if(!this->isRunning()){
        QThread::start();
        while(this->eventDispatcher()==nullptr)
            QThread::msleep(1);
    }
    return*this;
}

MURequestJob &MURequestJob::quit()
{
    this->connectDinit();
    QThread::quit();
    return*this;
}

void MURequestJob::onReplyFinish(QNetworkReply *r)
{
    response.response_qt_status_code=r->error();
    this->onRequestFinish();
}

void MURequestJob::onReplyError(QNetworkReply::NetworkError e)
{
    this->response.response_qt_status_code=e;
    this->onRequestFinish();
}

void MURequestJob::onReplyTimeout()
{
    this->response.response_qt_status_code=QNetworkReply::TimeoutError;
    this->onRequestFinish();
}

void MURequestJob::onReplyCancel()
{
    this->response.response_qt_status_code=QNetworkReply::OperationCanceledError;
    this->onRequestFinish();
}

void MURequestJob::onRequestFinish()
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

void MURequestJob::onRequestSend(MURequest *muRequest)
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
            parameters<<qsl("%1=%2").arg(i.key(), i.value().toString());
        }
        if(!parameters.isEmpty())
            request_url+=qsl("?%1").arg(parameters.join(','));
    }

    QUrl url(request_url);
    QNetworkRequest request(url);

    auto contentType=qbl("application/x-www-form-urlencoded");

    switch (muRequest->requestAppType()) {
    case MUEnumRequest::AppType::atCBor:
        contentType=qbl("application/cbor");
        break;
    case MUEnumRequest::AppType::atJson:
        contentType=qbl("application/json");
        break;
    case MUEnumRequest::AppType::atXml:
        contentType=qbl("application/xml");
        break;
    case MUEnumRequest::AppType::atBinary:
        contentType=qbl("application/binary");
        break;
    default:
        break;
    }
    request.setHeader(QNetworkRequest::ContentTypeHeader, contentType);

#if Q_MU_LOG
    mWarning()<<qsl(":request.url(%1)").arg(request_url);
#endif
    QHashIterator<QString, QVariant> i(response.request_header);
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
    mWarning()<<qsl(":request.method(%1)").arg(QString(response.request_method));
    mWarning()<<qsl(":request.body(%1)").arg(QString(response.request_body));
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
    QObject::connect(reply, QOverload<QNetworkReply::NetworkError>::of(&QNetworkReply::errorOccurred), this, &MURequestJob::onReplyError);
#else
    QObject::connect(reply, QOverload<QNetworkReply::NetworkError>::of(&QNetworkReply::error), this, &MURequestJob::onReplyError);
#endif

    for(auto&v:reply->rawHeaderPairs()){
        response.response_header.insert(v.first, v.second);
    }
}
