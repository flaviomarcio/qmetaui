#pragma once

#include <QObject>
#include <QVariant>
#include <QVariantList>
#include <QVariantMap>
#include <QDate>
#include <QTime>
#include <QDateTime>
#include "./mu_global.h"

//!
//! \brief The MUDateUtil class
//!
class Q_MU_EXPORT MUDateUtil : public QObject
{
    Q_OBJECT
public:
    //!
    //! \brief MUDateUtil
    //! \param parent
    //!
    Q_INVOKABLE explicit MUDateUtil(QObject *parent = nullptr);
    explicit MUDateUtil(const MUDateUtil &parent);
    ~MUDateUtil();

    //!
    //! \brief i
    //! \return
    //!
    Q_INVOKABLE static MUDateUtil&i();

    //!
    //! \brief isDebug
    //! \return
    //!
    Q_INVOKABLE static bool isDebug();

    //!
    //! \brief ifThen
    //! \param vThen
    //! \param vElse
    //! \return
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
    //! \brief isEmpty
    //! \param v
    //! \return
    //!
    Q_INVOKABLE static bool isEmpty(const QVariant &v);

    //!
    //! \brief isEmptySet
    //! \param vThen
    //! \param vElse
    //! \return
    //!
    Q_INVOKABLE static QVariant isEmptySet(const QVariant &vThen, const QVariant &vElse);

    //!
    //! \brief currentDateTime
    //! \return
    //!
    Q_INVOKABLE static QDateTime currentDateTime();

    //!
    //! \brief currentDate
    //! \return
    //!
    Q_INVOKABLE static QDateTime currentDate();

    //!
    //! \brief currentTime
    //! \return
    //!
    Q_INVOKABLE static QDateTime currentTime();

    //!
    //! \brief toString
    //! \param vDt
    //! \return
    //!
    Q_INVOKABLE static QString toString(const QVariant&vDt);

    //!
    //! \brief toDateTimeFormat
    //! \param vDt
    //! \param format
    //! \return
    //!
    Q_INVOKABLE static QString toDateTimeFormat(const QVariant&vDt, const QString &format=QString());

    //!
    //! \brief toDateFormat
    //! \param vDt
    //! \param format
    //! \return
    //!
    Q_INVOKABLE static QString toDateFormat(const QVariant&vDt, const QString &format=QString());

    //!
    //! \brief toTimeFormat
    //! \param vDt
    //! \param format
    //! \return
    //!
    Q_INVOKABLE static QString toTimeFormat(const QVariant&vDt, const QString &format=QString());

    //!
    //! \brief toDateInput
    //! \param vDt
    //! \param format
    //! \return
    //!
    Q_INVOKABLE static QString toDateInput(const QVariant&vDt, const QString &format=QString());

    //!
    //! \brief toDate
    //! \param vDt
    //! \return
    //!
    Q_INVOKABLE static QDateTime toDate(const QVariant&vDt);

    //!
    //! \brief toTime
    //! \param vDt
    //! \return
    //!
    Q_INVOKABLE static QDateTime toTime(const QVariant&vDt);

    //!
    //! \brief toDateTime
    //! \param vDt
    //! \return
    //!
    Q_INVOKABLE static QDateTime toDateTime(const QVariant&vDt);

    //!
    //! \brief dayOfWeek
    //! \param vDt
    //! \return
    //!
    Q_INVOKABLE static int dayOfWeek(const QVariant&vDt);

    //!
    //! \brief dayOfWeekName
    //! \param vDt
    //! \return
    //!
    Q_INVOKABLE static QString dayOfWeekName(const QVariant&vDt);

    //!
    //! \brief daysInMonth
    //! \param year
    //! \param month
    //! \return
    //!
    Q_INVOKABLE static int daysInMonth(const QVariant&year, const QVariant&month);
    Q_INVOKABLE static int daysInMonth(const QVariant&vDt);

    //!
    //! \brief daysMonthModel
    //! \param year
    //! \param month
    //! \return
    //!
    Q_INVOKABLE static QVariantList daysMonthModel(const QVariant&year, const QVariant&month);

    //!
    //! \brief year
    //! \param date
    //! \return
    //!
    Q_INVOKABLE static int year(const QVariant&date=QVariant());

    //!
    //! \brief month
    //! \param date
    //! \return
    //!
    Q_INVOKABLE static int month(const QVariant&date=QVariant());

    //!
    //! \brief day
    //! \param date
    //! \return
    //!
    Q_INVOKABLE static int day(const QVariant&date=QVariant());

    //!
    //! \brief firstDayMonth
    //! \param year
    //! \param month
    //! \return
    //!
    Q_INVOKABLE static QDateTime firstDayMonth(const QVariant&year, const QVariant&month);

    //!
    //! \brief lastDayMonth
    //! \param date
    //! \return
    //!
    Q_INVOKABLE static QDateTime lastDayMonth(const QVariant&date);
    Q_INVOKABLE static QDateTime lastDayMonth(const QVariant&year, const QVariant&month);
    Q_INVOKABLE static QDateTime nextDayMonth(const QVariant&year, const QVariant&month);

    //!
    //! \brief lastDayNextMonth
    //! \param date
    //! \return
    //!
    Q_INVOKABLE static QDateTime lastDayNextMonth(const QVariant&date=QVariant());

    //!
    //! \brief monthName
    //! \param month
    //! \return
    //!
    Q_INVOKABLE static QString monthName(const QVariant&month=QVariant());

    //!
    //! \brief equalDate
    //! \param v1
    //! \param v2
    //! \return
    //!
    Q_INVOKABLE static bool equalDate(const QVariant&v1,const QVariant&v2);

    //!
    //! \brief equalDateTime
    //! \param v1
    //! \param v2
    //! \return
    //!
    Q_INVOKABLE static bool equalDateTime(const QVariant&v1,const QVariant&v2);

    //!
    //! \brief equalTime
    //! \param v1
    //! \param v2
    //! \return
    //!
    Q_INVOKABLE static bool equalTime(const QVariant&v1,const QVariant&v2);

    //!
    //! \brief isHigherDateTime
    //! \param v1
    //! \param v2
    //! \return
    //!
    Q_INVOKABLE static bool isHigherDateTime(const QVariant &v1, const QVariant &v2);

    //!
    //! \brief isLowerDateTime
    //! \param v1
    //! \param v2
    //! \return
    //!
    Q_INVOKABLE static bool isLowerDateTime(const QVariant &v1, const QVariant &v2);

    //!
    //! \brief isBetweenDateTime
    //! \param v1
    //! \param v2
    //! \return
    //!
    Q_INVOKABLE static bool isBetweenDateTime(const QVariant &v1, const QVariant &v2);
private:
    void *p=nullptr;
};
