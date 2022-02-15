#pragma once

#include "./mu_global.h"
#include <QObject>
#include <QVariant>
#include <QVariantList>
#include <QVariantMap>
#include <QtQml>

//!
//! \brief The MUObject class
//!
class Q_MU_EXPORT MUObject : public QObject
{
    Q_OBJECT
public:
    //!
    //! \brief MUObject
    //! \param parent
    //!
    Q_INVOKABLE explicit MUObject(QObject *parent = nullptr);

    //!
    //! \brief toHash
    //! \return
    //!
    Q_INVOKABLE QVariantHash toHash()const;

    //!
    //! \brief toJson
    //! \return
    //!
    Q_INVOKABLE QByteArray toJson()const;

    //!
    //! \brief fromMap
    //! \param v
    //! \return
    //!
    Q_INVOKABLE bool fromMap(const QVariantMap &v);

    //!
    //! \brief fromHash
    //! \param v
    //! \return
    //!
    Q_INVOKABLE bool fromHash(const QVariantHash &v);

};
