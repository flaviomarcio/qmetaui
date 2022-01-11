#ifndef MULoginSession_H
#define MULoginSession_H

#include <QObject>
#include <QUuid>
#include <QVariant>
#include <QDate>
#include <QVariantList>
#include <QVariantMap>
#include "./mu_global.h"
#include "./mu_object.h"
#include "./mu_login_token.h"
#include "./mu_login_profile.h"

class Q_MU_EXPORT MULoginSession : public MUObject
{
    Q_OBJECT
public:

    Q_PROPERTY(QUuid           uuid        READ uuid       WRITE set_uuid    NOTIFY loginChanged);
    Q_PROPERTY(QByteArray      hsh_md5     READ hsh_md5    WRITE set_hsh_md5 NOTIFY loginChanged);
    Q_PROPERTY(MULoginProfile* profile     READ profile    WRITE set_profile NOTIFY loginChanged);
    Q_PROPERTY(MULoginToken*   token       READ token      WRITE set_token   NOTIFY loginChanged);

    Q_INVOKABLE explicit MULoginSession(QObject *parent = nullptr);
    ~MULoginSession();

    static Q_INVOKABLE MULoginSession&i();

    virtual QUuid uuid() const;
    virtual void set_uuid(const QUuid &value);

    virtual QByteArray hsh_md5() const;
    virtual void set_hsh_md5(const QByteArray &value);

    virtual MULoginProfile *profile();
    virtual bool set_profile(const MULoginProfile *v) const;

    virtual MULoginToken* token();
    virtual bool set_token(const MULoginToken *v) const;

    Q_INVOKABLE virtual QVariantHash data();
    Q_INVOKABLE virtual bool setData(const QVariant&v);

    Q_INVOKABLE virtual QVariant value(const QString&key) const;

    MULoginSession&operator=(const QVariant&v);
    Q_INVOKABLE virtual bool isLogged() const;

    void clear();

public slots:

    Q_INVOKABLE bool load();
    Q_INVOKABLE bool save();
    Q_INVOKABLE bool logoff();
    Q_INVOKABLE void verify();
    Q_INVOKABLE bool verifyData();


signals:

    void invalidData(const QVariant&message);

    void loginChanged();

    void loginSuccessful(const QVariant&message);
    void loginUnSuccessful(const QVariant&message);

    void sessionLogged();
    void sessionUnLogged();
    void sessionUnAuthorized();

    void notifyError(const QVariant&message);
    void notifyFail(const QVariant&message);
    void notify(int type, int especification, const QVariant&payload);

    void clientOnLine(const QVariant&message);
    void clientOffLine(const QVariant&message);
private:
    void*p=nullptr;
};

#endif // MULoginSession_H
