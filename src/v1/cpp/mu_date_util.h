#pragma once

#include <QObject>
#include <QVariant>
#include <QVariantList>
#include <QVariantMap>
#include <QDate>
#include <QTime>
#include <QDateTime>
#include "./mu_global.h"

class Q_MU_EXPORT  MUDateUtil : public QObject
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit MUDateUtil(QObject *parent = nullptr);
    Q_INVOKABLE explicit MUDateUtil(const MUDateUtil &parent);
    ~MUDateUtil();

    Q_INVOKABLE static MUDateUtil&i();

    Q_INVOKABLE static bool isDebug();

    Q_INVOKABLE static const QVariant ifThen(const QVariant &vThen, const QVariant &vElse);
    Q_INVOKABLE static bool isDefined(const QVariant &v);
    Q_INVOKABLE static bool isUndefined(const QVariant &v);
    Q_INVOKABLE static bool isEmpty(const QVariant &v);
    Q_INVOKABLE static QVariant isEmptySet(const QVariant &vThen, const QVariant &vElse);

    Q_INVOKABLE static QDateTime currentDateTime();
    Q_INVOKABLE static QDateTime currentDate();
    Q_INVOKABLE static QDateTime currentTime();
    Q_INVOKABLE static QString toString(const QVariant&vDt);
    Q_INVOKABLE static QString toDateTimeFormat(const QVariant&vDt, const QString &format=QString());
    Q_INVOKABLE static QString toDateFormat(const QVariant&vDt, const QString &format=QString());
    Q_INVOKABLE static QString toTimeFormat(const QVariant&vDt, const QString &format=QString());

    Q_INVOKABLE static QString toDateInput(const QVariant&vDt, const QString &format=QString());

    Q_INVOKABLE static const QDateTime toDate(const QVariant&vDt);
    Q_INVOKABLE static const QDateTime toTime(const QVariant&vDt);
    Q_INVOKABLE static const QDateTime toDateTime(const QVariant&vDt);
    Q_INVOKABLE static int dayOfWeek(const QVariant&vDt);
    Q_INVOKABLE static const QString dayOfWeekName(const QVariant&vDt);
    Q_INVOKABLE static int daysInMonth(const QVariant&year, const QVariant&month);
    Q_INVOKABLE static int daysInMonth(const QVariant&vDt);

    Q_INVOKABLE static const QVariantList daysMonthModel(const QVariant&year, const QVariant&month);

    Q_INVOKABLE static int year(const QVariant&date=QVariant());
    Q_INVOKABLE static int month(const QVariant&date=QVariant());
    Q_INVOKABLE static int day(const QVariant&date=QVariant());


    Q_INVOKABLE static QDateTime firstDayMonth(const QVariant&year, const QVariant&month);
    Q_INVOKABLE static QDateTime lastDayMonth(const QVariant&date);
    Q_INVOKABLE static QDateTime lastDayMonth(const QVariant&year, const QVariant&month);
    Q_INVOKABLE static QDateTime nextDayMonth(const QVariant&year, const QVariant&month);
    Q_INVOKABLE static QDateTime lastDayNextMonth(const QVariant&date=QVariant());


    Q_INVOKABLE static QString monthName(const QVariant&month=QVariant());

    Q_INVOKABLE static bool equalDate(const QVariant&v1,const QVariant&v2);
    Q_INVOKABLE static bool equalDateTime(const QVariant&v1,const QVariant&v2);
    Q_INVOKABLE static bool equalTime(const QVariant&v1,const QVariant&v2);

    Q_INVOKABLE static bool isHigherDateTime(const QVariant &v1, const QVariant &v2);
    Q_INVOKABLE static bool isLowerDateTime(const QVariant &v1, const QVariant &v2);
    Q_INVOKABLE static bool isBetweenDateTime(const QVariant &v1, const QVariant &v2);
private:
    void *p=nullptr;
};
