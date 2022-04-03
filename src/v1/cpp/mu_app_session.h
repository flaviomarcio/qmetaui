#pragma once

#include "./mu_app_repository.h"
#include "./mu_app_info.h"

class Q_MU_EXPORT MUAppSession: public MUObject
{
    Q_OBJECT
public:
    Q_PROPERTY(MUAppRepository* repository READ repository WRITE set_repository NOTIFY repositoryChanged);
    Q_PROPERTY(MUAppInfo* app READ app WRITE set_app NOTIFY appChanged);

    Q_INVOKABLE explicit MUAppSession(QObject *parent = nullptr);
    ~MUAppSession();

    static Q_INVOKABLE MUAppSession&i();

    virtual MUAppRepository *repository() const;
    virtual bool set_repository(MUAppRepository *v);

    virtual MUAppInfo *app() const;
    virtual bool set_app(MUAppInfo *v);

    Q_INVOKABLE virtual QVariantHash data();
    Q_INVOKABLE virtual bool setData(const QVariant&v);

    Q_INVOKABLE virtual bool getData();

    MUAppSession&operator=(const QVariant&v);

public slots:
    Q_INVOKABLE bool load();
    Q_INVOKABLE bool save();

signals:
    void repositoryChanged();
    void appChanged();
    void appStart();
    void appRestart();

signals:
    void startloadingInfo();
    void errorLoadingInfo();
    void finishLoadingInfo();

private:
    void*p=nullptr;
};
