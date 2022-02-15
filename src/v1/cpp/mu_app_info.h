#pragma once

#include "./mu_global.h"
#include "./mu_object.h"

#include <QVariantMap>

//!
//! \brief The MUAppInfo class
//!
class Q_MU_EXPORT MUAppInfo : public MUObject
{
    Q_OBJECT
    QML_ELEMENT
public:

    Q_PROPERTY(bool strong READ strong WRITE setStrong NOTIFY dataChanged )
    Q_PROPERTY(bool show READ show WRITE setShow NOTIFY dataChanged )
    Q_PROPERTY(QString display READ display WRITE setDisplay NOTIFY dataChanged )
    Q_PROPERTY(QString version READ version WRITE setVersion NOTIFY dataChanged )

    //!
    //! \brief MUAppInfo
    //! \param parent
    //!
    Q_INVOKABLE explicit MUAppInfo(QObject *parent = nullptr);
    ~MUAppInfo();

    //!
    //! \brief operator =
    //! \param v
    //! \return
    //!
    MUAppInfo&operator=(const MUAppInfo&v);

    //!
    //! \brief operator =
    //! \param v
    //! \return
    //!
    MUAppInfo&operator=(const QVariant&v);

    //!
    //! \brief strong
    //! \return
    //!
    Q_INVOKABLE virtual bool strong() const;
    Q_INVOKABLE virtual void setStrong(bool strong);

    //!
    //! \brief show
    //! \return
    //!
    Q_INVOKABLE virtual bool show() const;
    Q_INVOKABLE virtual void setShow(bool show);

    //!
    //! \brief display
    //! \return
    //!
    Q_INVOKABLE virtual QString display() const;
    Q_INVOKABLE virtual void setDisplay(const QString &display);

    //!
    //! \brief version
    //! \return
    //!
    Q_INVOKABLE virtual QString version() const;
    Q_INVOKABLE virtual void setVersion(const QString &version);

private:
    void*p=nullptr;

signals:
    void dataChanged();
};
