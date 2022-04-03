#include "./p_mu_request_queue_pvt.h"

MURequestQueuePvt::MURequestQueuePvt(QObject *object)
{
    Q_UNUSED(object)
    this->init();
}

MURequestQueuePvt::~MURequestQueuePvt()
{
    this->dinit();
}

void MURequestQueuePvt::jobConnect(MURequestJob *job)
{
    if(job==nullptr)
        return;
    QObject::connect(job,&MURequestJob::finishThread,this,&MURequestQueuePvt::onFinishThread);
    QObject::connect(job,&MURequestJob::finishRequest,this,&MURequestQueuePvt::onRequestFinish);
}

void MURequestQueuePvt::jobDisconnect(MURequestJob *job)
{
    if(job==nullptr)
        return;
    QObject::disconnect(job,&MURequestJob::finishThread,this,&MURequestQueuePvt::onFinishThread);
    QObject::disconnect(job,&MURequestJob::finishRequest,this,&MURequestQueuePvt::onRequestFinish);
}

MURequestJob *MURequestQueuePvt::jobNew()
{
    auto job=new MURequestJob();
    this->jobConnect(job);
    return job;
}

void MURequestQueuePvt::jobTerminate(MURequestJob *job)
{
    this->jobDisconnect(job);
    job->quit();
    if(job->wait(1000))
        delete job;
    else
        job->deleteLater();
}

void MURequestQueuePvt::jobRemove(MURequest *request)
{
    if(request==nullptr)
        return;
    QObject::disconnect(request, &MURequest::destroyed,this,&MURequestQueuePvt::onRequestDestroy);
    MURequestJob*job=nullptr;
    {
        QMutexLocker locker(&this->mutex);
        if(this->muList.contains(request))//lock controller
            job=this->muList.take(request);
    }

    if(job!=nullptr){//finish job
#if Q_MU_LOG_VERBOSE
        sWarning()<<QString("Removing requestJob: %1").arg(job->url().toString());
#endif
        this->jobTerminate(job);
        job=nullptr;
    }
}

void MURequestQueuePvt::init()
{
}

void MURequestQueuePvt::dinit()
{
    QList<MURequestJob*> jobList;
    {
        QMutexLocker locker(&this->mutex);
        jobList=this->muList.values();
        this->muList.clear();
    }

    for(auto&job:jobList){
        this->jobDisconnect(job);
    }

    for(auto&job:jobList){
        this->jobTerminate(job);
    }
}

void MURequestQueuePvt::requestQueue(MURequest *request)
{
    MURequestJob*job=nullptr;
    this->jobRemove(request);

    {//new job
        job=jobNew();
        QMutexLocker locker(&this->mutex);
        this->muList.insert(request, job);
        QObject::connect(request, &MURequest::destroyed,this,&MURequestQueuePvt::onRequestDestroy);
    }
    QObject::connect(job,&MURequestJob::finishThread,this,&MURequestQueuePvt::onFinishThread);

    job->start();
    //sendo request to Job
    emit job->requestSend(request);
}

void MURequestQueuePvt::onRequestDestroy(QObject *object)
{
    auto request=dynamic_cast<MURequest*>(object);
    this->jobRemove(request);
}

void MURequestQueuePvt::onFinishThread(MURequestJob *job)
{
    MURequest*request=nullptr;
    {
        QMutexLocker locker(&this->mutex);
        request=this->muList.key(job);
    }
    this->jobRemove(request);
}

void MURequestQueuePvt::onRequestFinish(MURequest *request, const QVariantHash &vResponse)
{
    bool contains=false;
    {
        QMutexLocker locker(&this->mutex);
        contains=this->muList.contains(request);
    }
    if(contains){
        auto pvt=static_cast<MURequestPvt*>(request->p);
        if(pvt!=nullptr)
            emit pvt->requestResponse(vResponse);
    }
    this->jobRemove(request);
}
