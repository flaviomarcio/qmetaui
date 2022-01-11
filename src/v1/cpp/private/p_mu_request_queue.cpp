#include "p_mu_request_queue_pvt.h"

#define dPvt()\
    auto&p = *reinterpret_cast<MURequestQueuePvt*>(this->p)


static MURequestQueue*newInstanceQueue(){
    auto queue=new MURequestQueue();
    return queue;
}

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
    static auto _instance = newInstanceQueue();
    if(!_instance->isRunning())
        _instance->start();
    return*_instance;
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
