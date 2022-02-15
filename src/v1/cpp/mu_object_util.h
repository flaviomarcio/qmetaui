#pragma once

#include "./mu_global.h"
#include <QObject>
#include <QVariant>
#include <QDateTime>
#include <QVariantMap>
#include <QVariantList>
#include <QDateTime>
#include <QJsonDocument>
#include <QJsonObject>
#include <QCborValue>
#include <QCborMap>
#include <QCborArray>
#include <QColor>
#include <QObject>
#include <QQuickItem>
#include <QCborParserError>

//!
//! \brief The MUObjectUtil class
//!
class Q_MU_EXPORT MUObjectUtil : public QObject
{
    Q_OBJECT
public:

    //!
    //! \brief MUObjectUtil
    //! \param parent
    //!
    Q_INVOKABLE explicit MUObjectUtil(QObject *parent = nullptr);

    //!
    //!
    ~MUObjectUtil();

    static Q_INVOKABLE MUObjectUtil&i();

    //!
    //! \brief isDebug
    //! \return
    //!
    Q_INVOKABLE static bool isDebug();

    //!
    //! \brief isIOS
    //! \return
    //!
    Q_INVOKABLE static bool isIOS();

    //!
    //! \brief isAndroid
    //! \return
    //!
    Q_INVOKABLE static bool isAndroid();

    //!
    //! \brief isDesktop
    //! \return
    //!
    Q_INVOKABLE static bool isDesktop();

    //!
    //! \brief ifThen
    //! \param vThen
    //! \param vElse
    //! \return
    //!
    Q_INVOKABLE static const QVariant ifThen(const QVariant &vThen, const QVariant &vElse);

    //!
    //! \brief isDefined
    //! \param v
    //! \return
    //!
    Q_INVOKABLE static bool isDefined(const QVariant &v);

    //!
    //! \brief isUndefined
    //! \param v
    //! \return
    //!
    Q_INVOKABLE static bool isUndefined(const QVariant &v);

    //!
    //! \brief makeObjectName
    //! \param v
    //! \return
    //!
    Q_INVOKABLE static QString makeObjectName(const QVariant &v=QVariant());

    //!
    //! \brief objectToMap
    //! \param object
    //! \return
    //!
    Q_INVOKABLE static QVariantMap objectToMap(const QObject *object);

    //!
    //! \brief objectFromMap
    //! \param object
    //! \param v
    //! \return
    //!
    Q_INVOKABLE static bool objectFromMap(QObject*object, const QVariant&v);

    //!
    //! \brief objectToHash
    //! \param object
    //! \return
    //!
    Q_INVOKABLE static QVariantHash objectToHash(const QObject *object);

    //!
    //! \brief objectFromHash
    //! \param object
    //! \param v
    //! \return
    //!
    Q_INVOKABLE static bool objectFromHash(QObject*object, const QVariant&v);

signals:

};
