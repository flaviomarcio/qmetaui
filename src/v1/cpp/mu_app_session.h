#pragma once

#include "./mu_app_repository.h"
#include "./mu_app_info.h"

//!
//! \brief The MUAppSession class
//!
class Q_MU_EXPORT MUAppSession: public MUObject
{
    Q_OBJECT
    QML_ELEMENT
public:
    Q_PROPERTY(MUAppRepository* repository READ repository WRITE set_repository NOTIFY appInfoChanged);
    Q_PROPERTY(MUAppInfo*app READ app WRITE set_app NOTIFY appInfoChanged);

    //!
    //! \brief MUAppSession
    //! \param parent
    //!
    Q_INVOKABLE explicit MUAppSession(QObject *parent = nullptr);
    ~MUAppSession();

    //!
    //! \brief operator =
    //! \param v
    //! \return
    //!
    MUAppSession&operator=(const QVariant&v);

    //!
    //! \brief i
    //! \return
    //!
    static Q_INVOKABLE MUAppSession&i();

    //!
    //! \brief repository
    //! \return
    //!
    virtual MUAppRepository *repository() const;
    virtual bool set_repository(MUAppRepository *v);

    //!
    //! \brief app
    //! \return
    //!
    virtual MUAppInfo *app() const;
    virtual bool set_app(MUAppInfo *v);

    //!
    //! \brief data
    //! \return
    //!
    Q_INVOKABLE virtual QVariantHash data();
    Q_INVOKABLE virtual bool setData(const QVariant&v);
    Q_INVOKABLE virtual bool getData();



public slots:
    Q_INVOKABLE bool load();
    Q_INVOKABLE bool save();

signals:
    void appInfoChanged();
    void appStart();
    void appRestart();

signals:
    void startloadingInfo();
    void errorLoadingInfo();
    void finishLoadingInfo();

private:
    void*p=nullptr;
};
