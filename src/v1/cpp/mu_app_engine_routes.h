#ifndef MUAppEngineRoutes_H
#define MUAppEngineRoutes_H

#include <QObject>
#include "./mu_global.h"
#include "./mu_routes.h"

class Q_MU_EXPORT MUAppEngineRoutes:public MURoutes{
    Q_OBJECT
public:

    Q_PROPERTY(QString server           READ server           WRITE setServer           )
    Q_PROPERTY(QString protocol         READ protocol         WRITE setProtocol         )
    Q_PROPERTY(QString hostName         READ hostName         WRITE setHostName         )
    Q_PROPERTY(int     port             READ port             WRITE setPort             )

    Q_PROPERTY(QString info             READ info             WRITE setInfo     )

    Q_INVOKABLE explicit MUAppEngineRoutes(QObject *parent = nullptr);
    ~MUAppEngineRoutes();

    Q_INVOKABLE virtual void load();
    Q_INVOKABLE virtual void load(const QString &fileName);

    /**
     * @brief info
     * @return
     */
    Q_INVOKABLE virtual QString info() const;
    Q_INVOKABLE virtual void setInfo(const QString &info);

private:
    void*p=nullptr;
};

#endif
