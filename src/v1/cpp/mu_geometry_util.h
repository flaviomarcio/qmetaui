#pragma once

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
#include "./mu_global.h"

//!
//! \brief The MUGeometryUtil class
//!
class Q_MU_EXPORT MUGeometryUtil : public QObject
{
    Q_OBJECT
public:

    //!
    //! \brief MUGeometryUtil
    //! \param parent
    //!
    Q_INVOKABLE explicit MUGeometryUtil(QObject *parent = nullptr);
    ~MUGeometryUtil();

    //!
    //! \brief i
    //! \return
    //!
    static Q_INVOKABLE MUGeometryUtil&i();

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
    //! \brief desktopAvailableWidth
    //! \return
    //!
    Q_INVOKABLE static int desktopAvailableWidth();
    Q_INVOKABLE static void setDesktopAvailableWidth(int value);

    //!
    //! \brief desktopAvailableHeight
    //! \return
    //!
    Q_INVOKABLE static int desktopAvailableHeight();
    Q_INVOKABLE static void setDesktopAvailableHeight(int value);

    //!
    //! \brief toDoubleSize
    //! \param v
    //! \param defaultValue
    //! \return
    //!
    Q_INVOKABLE static double toDoubleSize(const QVariant &v, const QVariant&defaultValue=0);

    //!
    //! \brief toIntSize
    //! \param v
    //! \param defaultValue
    //! \return
    //!
    Q_INVOKABLE static qlonglong toIntSize(const QVariant &v, const QVariant&defaultValue=0);

    //!
    //! \brief toProportion
    //! \param v
    //! \return
    //!
    Q_INVOKABLE static const QString toProportion(const QVariant &v);

    //!
    //! \brief calcProportion
    //! \param vSize
    //! \param vSizeMax
    //! \return
    //!
    Q_INVOKABLE static double calcProportion(const QVariant &vSize, const QVariant &vSizeMax=0);

    //!
    //! \brief proportion
    //! \return
    //!
    Q_INVOKABLE static double proportion();

    //!
    //! \brief proportionFont
    //! \return
    //!
    Q_INVOKABLE static double proportionFont();

    //!
    //! \brief heightBase
    //! \return
    //!
    Q_INVOKABLE static double heightBase();

    //!
    //! \brief widthBase
    //! \return
    //!
    Q_INVOKABLE static double widthBase();

    //!
    //! \brief hideSplashScreen
    //!
    Q_INVOKABLE static void hideSplashScreen();
};
