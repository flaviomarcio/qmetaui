#ifndef MUREQUESTQUEUE_H
#define MUREQUESTQUEUE_H

#include <QObject>
#include <QThread>

#include "../mu_request.h"

class Q_MU_EXPORT MURequestQueue : public QThread
{
    Q_OBJECT
public:

    static MURequestQueue&instance();

    void run();

    Q_INVOKABLE explicit MURequestQueue(QObject*parent=nullptr);
    ~MURequestQueue();

    Q_INVOKABLE virtual int paralelism() const;
    Q_INVOKABLE virtual void setParalelism(int value);
public slots:
    Q_INVOKABLE virtual void requestQueue(MURequest*request);
    Q_INVOKABLE virtual void requestImediate(MURequest*request);
private:
    void*p=nullptr;
};

#endif // MUREQUESTQUEUE_H
