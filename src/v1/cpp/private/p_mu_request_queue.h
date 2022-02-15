#pragma once

#include <QObject>
#include <QThread>
#include "../mu_request.h"

class Q_MU_EXPORT MURequestQueue : public QThread
{
    Q_OBJECT
public:

    static MURequestQueue&instance();

    void run();

    explicit MURequestQueue(QObject*parent=nullptr);
    ~MURequestQueue();

    virtual int paralelism() const;
    virtual void setParalelism(int value);
public slots:
    virtual void requestQueue(MURequest*request);
    virtual void requestImediate(MURequest*request);
private:
    void*p=nullptr;
};
