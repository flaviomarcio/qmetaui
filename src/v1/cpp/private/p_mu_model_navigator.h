#pragma once

#include "../mu_const.h"
#include "../mu_login_session.h"
#include "../mu_model_navigator.h"
#include "../mu_register.h"
#include "../mu_request.h"
#include "../mu_model_table.h"
#include "../mu_model_navigator.h"
#include "../mu_notification.h"
#include "../mu_cache_util.h"

class Q_MU_EXPORT MUModelNavigatorPvt : public QObject
{
    Q_OBJECT
public:
    const int searchVersion=2;
    MUModelNavigator*parent=nullptr;
    MUVariantUtil&variantUtil=MUVariantUtil::i();
    MUCacheUtil&cacheUtil=MUCacheUtil::i();
    MUNotification&notification=MUNotification::i();
    MUServerLink *linkCached = nullptr;
    MUServerLink link;
    MURequest request;
    MUModelTable model;
    QString cacheFileName;
    QVariantList cachePage;
    QVariant searchFilter;
    QVariant searchRevision;
    bool searchActiveNavigator=false;
    int searchRowCount =-1;
    int searchPageCount =-1;
    int searchOffset =-1;
    bool cacheAutoLoad=false;
    bool cacheAutoSave=false;

    explicit MUModelNavigatorPvt(MUModelNavigator *parent = nullptr);

    ~MUModelNavigatorPvt();

    bool loadCache();

    void reloadLink();

    bool saveCache();

    bool clearCursor();

    bool clear();

    bool search(const QVariant&searchFilter);

    bool reload(const QVariant&v=QVariant());

    bool first(const QVariant &v=QVariant());

    bool prior(const QVariant &v=QVariant());

    bool next(const QVariant &v=QVariant());

    bool last(const QVariant &v=QVariant());

    bool cancel(const QVariant &v=QVariant());

    QVariant bodyMount();

    bool call();

private slots:
    void onRequestResponse(QVariant v);
signals:
    void requestResponse(QVariant v);
};
