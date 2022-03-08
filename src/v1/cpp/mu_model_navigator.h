#pragma once

#include <QObject>
#include <QAbstractTableModel>
#include "./mu_server_link.h"

class Q_MU_EXPORT MUModelNavigator : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int searchRowCount READ searchRowCount WRITE setSearchRowCount)
    Q_PROPERTY(int searchPageCount READ searchPageCount WRITE setSearchPageCount)
    Q_PROPERTY(bool searchActiveNavigator READ searchActiveNavigator WRITE setSearchActiveNavigator)
    Q_PROPERTY(QString cacheFileName READ cacheFileName WRITE setCacheFileName)
    Q_PROPERTY(bool cacheAutoLoad READ cacheAutoLoad WRITE setCacheAutoLoad)
    Q_PROPERTY(bool cacheAutoSave READ cacheAutoSave WRITE setCacheAutoSave)
    Q_PROPERTY(QVariant setting READ setting WRITE setSetting)
    Q_PROPERTY(QVariant data READ data WRITE setData)
    Q_PROPERTY(QAbstractTableModel*model READ model WRITE setModel NOTIFY modelChanged)
    Q_PROPERTY(MUServerLink*link READ link WRITE setLink NOTIFY linkChanged)
    Q_PROPERTY(int count READ count NOTIFY linkChanged)
    Q_PROPERTY(bool isEmpty READ isEmpty NOTIFY linkChanged)

public:

    Q_INVOKABLE explicit MUModelNavigator(QObject *parent = nullptr);
    ~MUModelNavigator();

    int count();
    bool isEmpty();
    Q_INVOKABLE bool clear();
    Q_INVOKABLE bool search(const QVariant &bodyFilter);
    Q_INVOKABLE bool reload(const QVariant &v);
    Q_INVOKABLE bool first(const QVariant &v=QVariant());
    Q_INVOKABLE bool prior(const QVariant &v=QVariant());
    Q_INVOKABLE bool next(const QVariant &v=QVariant());
    Q_INVOKABLE bool last(const QVariant &v=QVariant());
    Q_INVOKABLE bool cancel();

    virtual QVariant setting()const;
    virtual void setSetting(const QVariant&v);

    virtual QVariant data()const;
    virtual void setData(const QVariant&v);

    QAbstractTableModel *model();
    void setModel(QAbstractTableModel*model);

    virtual int searchRowCount() const;
    virtual void setSearchRowCount(int value);

    virtual int searchPageCount() const;
    virtual void setSearchPageCount(int searchPageCount);

    virtual MUServerLink *link();
    virtual void setLink(MUServerLink *link);

    virtual QString cacheFileName() const;
    virtual void setCacheFileName(const QString &value);

    virtual bool cacheAutoLoad() const;
    virtual void setCacheAutoLoad(bool value);

    virtual bool cacheAutoSave() const;
    virtual void setCacheAutoSave(bool value);

    virtual bool searchActiveNavigator() const;
    virtual void setSearchActiveNavigator(bool value);

    Q_INVOKABLE virtual bool loadCache();
    Q_INVOKABLE virtual bool saveCache();

signals:
    void searchStarted();
    void searchResponse(const QVariant&responseBody);
    void searchFinished();
    void searchDiscarted();
    void searchUnauthorized(const QVariant&message);
    void searchFail(const QVariant&message);
    void searchError(const QVariant&message);

    void modelChanged();
    void linkChanged();
private:
    void*p=nullptr;
};
