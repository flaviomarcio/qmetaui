#pragma once

#include <QObject>
#include "./mu_global.h"
#include "./mu_server_link.h"
#include "./mu_login_engine_routes.h"

namespace QMetaUi{

//!
//! \brief The Hosting class
//!
class Q_MU_EXPORT Hosting : public QObject
{
    Q_OBJECT
public:
    //!
    //! \brief Hosting
    //! \param parent
    //!
    Q_INVOKABLE explicit Hosting(QObject *parent = nullptr);
    ~Hosting();

    //!
    //! \brief backendHost
    //! \return
    //!
    virtual MUServerLink&backendHost();

    //!
    //! \brief bh
    //! \return
    //!
    virtual MUServerLink&bh();
    virtual MUServerLink&bh(const QString&protocol, const QString&host, int port, const QString&route);
    virtual MUServerLink&bh(const QString&protocol, const QString&host, int port, const QString&route, const QString&method);
    virtual void reload();

    //!
    //! \brief readReturn
    //! \param parent
    //! \param vv
    //! \param endpoint
    //! \return
    //!
    MUServerLink*readReturn(Hosting*parent, MUServerLink*&vv, const QString&endpoint);
    MUServerLink*readReturn(Hosting*parent, MUServerLink*&vv, const QString&endpoint, const QString &method);

    //!
    //! \brief getHeaders
    //! \return
    //!
    Q_INVOKABLE QVariantHash getHeaders();

public slots:
    //!
    //! \brief disconnectHeaders
    //! \param vv
    //!
    void disconnectHeaders(QObject *vv);

private:
    void*p=nullptr;
signals:
    //!
    //! \brief hostingChanged
    //!
    void hostingChanged();

    //!
    //! \brief headersChanged
    //! \param value
    //!
    void headersChanged(const QVariantHash &value);
};
}
