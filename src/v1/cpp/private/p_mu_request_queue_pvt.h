#pragma once

#include "./qrpc_macro.h"
#include "./p_mu_request.h"
#include "./p_mu_request_queue.h"
#include "./p_mu_request_job.h"

#define REQUEST_QUEUE_ACTIVE

class Q_MU_EXPORT MURequestQueuePvt: public QObject{
    Q_OBJECT
public:
    int paralelism=QThread::idealThreadCount();
    QMutex mutex;
    QMap<MURequest*, MURequestJob*> muList;

    explicit MURequestQueuePvt(QObject*object=nullptr);

    virtual ~MURequestQueuePvt();

    void jobConnect(MURequestJob*job);

    void jobDisconnect(MURequestJob*job);

    MURequestJob *jobNew();

    void jobTerminate(MURequestJob*job);

    void jobRemove(MURequest*request);

    void init();

    void dinit();

    void requestQueue(MURequest*request);

private slots:

    void onRequestDestroy(QObject*object);

    void onFinishThread(MURequestJob*job);

    void onRequestFinish(MURequest*request, const QVariantHash&vResponse);
};
