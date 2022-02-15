#include "p_mu_request_queue_pvt.h"

#define dPvt()\
    auto&p = *reinterpret_cast<MURequestQueuePvt*>(this->p)

Q_GLOBAL_STATIC(MURequestQueue, instanceQueue);

static void init()
{
    instanceQueue->start();
}

Q_COREAPP_STARTUP_FUNCTION(init);

MURequestQueue::MURequestQueue(QObject*parent) : QThread(nullptr)
{
    Q_UNUSED(parent)
    this->p = new MURequestQueuePvt(this);
}

MURequestQueue::~MURequestQueue()
{
    dPvt();
    p.deleteLater();
}

MURequestQueue &MURequestQueue::instance()
{
    return*instanceQueue;
}

void MURequestQueue::run()
{
    dPvt();
    this->exec();
    p.dinit();
}

int MURequestQueue::paralelism() const
{
    dPvt();
    return p.paralelism;
}

void MURequestQueue::setParalelism(int value)
{
    dPvt();
    p.paralelism = value;
}

void MURequestQueue::requestQueue(MURequest *request)
{
    dPvt();
    p.requestQueue(request);
}

void MURequestQueue::requestImediate(MURequest *request)
{
    dPvt();
    p.requestQueue(request);
}
