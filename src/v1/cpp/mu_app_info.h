#pragma once

#include "./mu_global.h"
#include "./mu_object.h"

class Q_MU_EXPORT MUAppInfo : public MUObject
{
    Q_OBJECT
public:

    Q_PROPERTY(bool    strong     READ strong  WRITE setStrong   NOTIFY strongChanged )
    Q_PROPERTY(bool    show       READ show    WRITE setShow     NOTIFY showChanged )
    Q_PROPERTY(QString display    READ display WRITE setDisplay  NOTIFY displayChanged )
    Q_PROPERTY(QString version    READ version WRITE setVersion  NOTIFY versionChanged )

    Q_INVOKABLE explicit MUAppInfo(QObject *parent = nullptr);
    ~MUAppInfo();

    MUAppInfo&operator=(const MUAppInfo&v);
    MUAppInfo&operator=(const QVariant&v);

    Q_INVOKABLE virtual bool strong() const;
    Q_INVOKABLE virtual void setStrong(bool strong);

    Q_INVOKABLE virtual bool show() const;
    Q_INVOKABLE virtual void setShow(bool show);

    Q_INVOKABLE virtual QString display() const;
    Q_INVOKABLE virtual void setDisplay(const QString &display);

    Q_INVOKABLE virtual QString version() const;
    Q_INVOKABLE virtual void setVersion(const QString &version);

private:
    void*p=nullptr;
signals:
    void strongChanged();
    void showChanged();
    void displayChanged();
    void versionChanged();
};
