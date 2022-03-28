#include "./mu_date_util.h"
#include "./mu_object_util.h"
#include <QLocale>
#include <QDebug>
#include <QStm>

#define dPvt()\
    auto&p = *reinterpret_cast<MUDateUtilPvt*>(this->p)

class MUDateUtilPvt
{
public:
    QString token;
    QVariantMap rawHeader;
    QString protocol="http";
    QString host="localhost";
    int port=8080;
    QString route="/";
    QString endpoint="";

    explicit MUDateUtilPvt(){
    }

    virtual ~MUDateUtilPvt(){
    }

    static QString toDateTimeFormat(const QDate &d, const QTime &t,const QString&format)
    {
        Q_UNUSED(format)
        if(d.isValid() && t.isValid())
            return d.toString(QStringLiteral("d MMM yyyy"))+" "+t.toString(QStringLiteral("HH:mm:ss"));

        if(d.isValid())
            return d.toString(QStringLiteral("d MMM yyyy"));

        if(t.isValid())
            return t.toString(QStringLiteral("HH:mm:ss"));

        return {};
    }


    static QString toDateTimeInput(const QDate &d, const QTime &t,const QString&format)
    {
        Q_UNUSED(format)
        if(d.isValid() && t.isValid())
            return d.toString(QStringLiteral("dd/MM/yyyy"))+QStringLiteral(" ")+t.toString(QStringLiteral("HH:mm:ss"));

        if(d.isValid())
            return d.toString(QStringLiteral("dd/MM/yyyy"));

        if(t.isValid())
            return t.toString(QStringLiteral("HH:mm:ss"));

        return {};
    }

};


MUDateUtil::MUDateUtil(QObject *parent) : QObject(parent)
{
    this->p=new MUDateUtilPvt();
}

MUDateUtil::MUDateUtil(const MUDateUtil &parent): QObject(nullptr)
{
    Q_UNUSED(parent)
    this->p=new MUDateUtilPvt();
}

MUDateUtil::~MUDateUtil()
{
    dPvt();
    delete&p;
}

MUDateUtil &MUDateUtil::i()
{
    static MUDateUtil __i;
    return __i;
}

bool MUDateUtil::isDebug()
{
    return MUObjectUtil::isDebug();
}

const QVariant MUDateUtil::ifThen(const QVariant &vThen, const QVariant &vElse)
{
    return MUObjectUtil::ifThen(vThen, vElse);
}

bool MUDateUtil::isDefined(const QVariant &v)
{
    return MUObjectUtil::isDefined(v);
}

bool MUDateUtil::isUndefined(const QVariant &v)
{
    return MUObjectUtil::isUndefined(v);
}

bool MUDateUtil::isEmpty(const QVariant &v)
{
    switch (qTypeId(v)){
    case QMetaType_QString:
    case QMetaType_QByteArray:
    case QMetaType_QChar:
        return v.toString().trimmed().isEmpty();
        break;
    default:
        return false;
    }
    return true;
}

QVariant MUDateUtil::isEmptySet(const QVariant &vThen, const QVariant &vElse)
{
    return isEmpty(vThen)?vElse:vThen;
}

QDateTime MUDateUtil::currentDateTime()
{
    return QDateTime::currentDateTime();
}

QDateTime MUDateUtil::currentDate()
{
    return QDateTime(QDate::currentDate(),QTime());
}

QDateTime MUDateUtil::currentTime()
{
    return QDateTime(QDate(),QTime::currentTime());
}

QString MUDateUtil::toString(const QVariant &vDt)
{
    QString vv;
    switch (qTypeId(vDt)){
    case QMetaType_QTime:
        return vDt.toTime().toString(Qt::ISODate);
    case QMetaType_QDate:
        return vDt.toDate().toString(Qt::ISODate);
    case QMetaType_QDateTime:
        return vDt.toDateTime().toString(Qt::ISODateWithMs);
    default:
        return {};
    }
}

QString MUDateUtil::toDateTimeFormat(const QVariant &vDt,const QString&format)
{
    auto d=toDateTime(vDt);
    auto s=MUDateUtilPvt::toDateTimeFormat(d.date(), d.time(), format);
    return s;
}

QString MUDateUtil::toDateFormat(const QVariant &vDt,const QString&format)
{
    auto v=toDateTime(vDt).date();
    auto s=MUDateUtilPvt::toDateTimeFormat(v,QTime(), format);
    return s;
}

QString MUDateUtil::toTimeFormat(const QVariant &vDt,const QString&format)
{
    auto v=toDateTime(vDt).time();
    auto s=MUDateUtilPvt::toDateTimeFormat(QDate(), v, format);
    return s;
}

QString MUDateUtil::toDateInput(const QVariant &vDt, const QString &format)
{
    auto v=toDateTime(vDt).date();
    auto s=MUDateUtilPvt::toDateTimeInput(v,QTime(), format);
    return s;
}

const QDateTime MUDateUtil::toDate(const QVariant &vDt)
{
    switch (qTypeId(vDt)){
    case QMetaType_QDate:
        return QDateTime{vDt.toDate(),QTime()};
    case QMetaType_QDateTime:
        return QDateTime{vDt.toDateTime().date(),QTime()};
    default:
        QDate dt;

        dt=QDate::fromString(vDt.toString());
        if(dt.isValid())
            return QDateTime{dt,QTime()};

        dt=QDate::fromString(vDt.toString(),QStringLiteral("dd/MM/yyyy"));
        if(dt.isValid())
            return QDateTime{dt,QTime()};

        dt=QDate::fromString(vDt.toString(),QStringLiteral("dd-MM-yyyy"));
        if(dt.isValid())
            return QDateTime{dt,QTime()};
    }
    return {};
}


const QDateTime MUDateUtil::toTime(const QVariant &vDt)
{
    return QDateTime(QDate(),vDt.toTime());
}

const QDateTime MUDateUtil::toDateTime(const QVariant &vDt)
{
    QDateTime vv;

    switch (qTypeId(vDt)){
    case QMetaType_QTime:
        return QDateTime(QDate(1901,1,1),vDt.toTime());
    case QMetaType_QDate:
        return QDateTime(vDt.toDate(),QTime());
    case QMetaType_QDateTime:
        return vDt.toDateTime();

    case QMetaType_Double:
    case QMetaType_Int:
    case QMetaType_UInt:
    case QMetaType_LongLong:
    case QMetaType_ULongLong:
        return QDateTime::fromMSecsSinceEpoch(vDt.toLongLong());
    default:
        return QDateTime(QDate::fromString(vDt.toString()),QTime()).toLocalTime();
    }

    return vv;
}

int MUDateUtil::dayOfWeek(const QVariant &vDt)
{
    auto v=toDate(vDt).date();
    return v.dayOfWeek();
}

const QString MUDateUtil::dayOfWeekName(const QVariant &vDt)
{
    return toDate(vDt).toString(QStringLiteral("dddd"));
}

int MUDateUtil::daysInMonth(const QVariant &year, const QVariant &month)
{
    auto dt=QDate(year.toInt(), month.toInt(), 1);
    dt=dt.isNull() || !dt.isValid()?QDate::currentDate():dt;
    return dt.daysInMonth();
}

int MUDateUtil::daysInMonth(const QVariant &vDt)
{
    auto dt=toDate(vDt).date();
    return daysInMonth(dt.year(), dt.month());
}

const QVariantList MUDateUtil::daysMonthModel(const QVariant &year, const QVariant &month)
{
    QVariantList vList;
    for (int day = 0; day < daysInMonth(year, month); ++day) {
        QVariantMap map;
        auto dd=QDate(year.toInt(), month.toInt(), 1);
        map.insert(QStringLiteral("name"), dayOfWeekName(dd) );
        map.insert(QStringLiteral("day"), QString::number(day).rightJustified(2,'0') );
        vList<<map;
    }
    return vList;
}

int MUDateUtil::year(const QVariant &date)
{
    switch (qTypeId(date)){
    case QMetaType_QDate:
        return date.toDate().year();
    case QMetaType_QDateTime:
        return date.toDateTime().date().year();
    default:
        return QDate::currentDate().year();
    }
}

int MUDateUtil::month(const QVariant &date)
{
    switch (qTypeId(date)){
    case QMetaType_QDate:
        return date.toDate().month();
    case QMetaType_QDateTime:
        return date.toDateTime().date().month();
    default:
        return QDate::currentDate().month();
    }
}

int MUDateUtil::day(const QVariant &date)
{
    switch (qTypeId(date)){
    case QMetaType_QDate:
        return date.toDate().day();
    case QMetaType_QDateTime:
        return date.toDateTime().date().day();
    default:
        return QDate::currentDate().day();
    }
}

QDateTime MUDateUtil::firstDayMonth(const QVariant &year, const QVariant &month)
{
    auto dt=QDate(year.toInt(),month.toInt(), 1);
    dt=QDate(dt.year(), dt.month(), dt.daysInMonth());
    return QDateTime(dt,QTime());
}

QDateTime MUDateUtil::lastDayMonth(const QVariant &date)
{
    auto dt=date.toDate();
    dt=QDate(dt.year(), dt.month(), dt.daysInMonth());
    return QDateTime(dt,QTime());
}

QDateTime MUDateUtil::lastDayMonth(const QVariant &year, const QVariant &month)
{
    auto dt=QDate(year.toInt(),month.toInt(), 1);
    dt=QDate(dt.year(), dt.month(), dt.daysInMonth());
    return QDateTime(dt,QTime());
}

QDateTime MUDateUtil::nextDayMonth(const QVariant &year, const QVariant &month)
{
    auto y=year.toInt();
    auto m=month.toInt();
    if(m==12){
        m=1;
        y+=1;
    }
    else{
        m+=1;
    }
    auto dt=QDate(y,m,1);
    return QDateTime(dt,QTime());
}

QDateTime MUDateUtil::lastDayNextMonth(const QVariant &date)
{
    QDate dt;
    switch (qTypeId(date)){
    case QMetaType_QDate:
        dt=date.toDate();
        break;
    case QMetaType_QDateTime:
        dt=date.toDateTime().date();
        break;
    default:
        dt=QDate::currentDate();
    }
    dt=nextDayMonth(dt.year(),dt.month()).date();
    dt=QDate(dt.year(), dt.month(), dt.daysInMonth());
    return QDateTime(dt,QTime());
}

QString MUDateUtil::monthName(const QVariant &month)
{
    int m=0;
    switch (qTypeId(month)){
    case QMetaType_Int:
    case QMetaType_UInt:
    case QMetaType_LongLong:
    case QMetaType_ULongLong:
    case QMetaType_Double:
        m=month.toInt();
        break;
    case QMetaType_QDate:
        m=month.toDate().month();
        break;
    case QMetaType_QDateTime:
        m=month.toDateTime().date().month();
        break;
    default:
        m=QDate::currentDate().month();
    }
    m=(m>0 && m<=12)?m:1;
    return QLocale::c().monthName(m);
}

bool MUDateUtil::isHigherDateTime(const QVariant &v1, const QVariant &v2)
{
    auto d1=toDateTime(v1);
    auto d2=toDateTime(v2);
    return (d1>=d2);
}

bool MUDateUtil::isLowerDateTime(const QVariant &v1, const QVariant &v2)
{
    auto d1=toDateTime(v1);
    auto d2=toDateTime(v2);
    return (d1<d2);
}

bool MUDateUtil::isBetweenDateTime(const QVariant &v1, const QVariant &v2)
{
    auto d1=toDateTime(v1);
    auto d2=toDateTime(v2);
    auto da = QDateTime::currentDateTime();
    return (da >= d1) && (da <= d2);
}

bool MUDateUtil::equalDate(const QVariant &v1, const QVariant &v2)
{
    auto d1=toDate(v1);
    auto d2=toDate(v2);
    return (d1==d2);
}

bool MUDateUtil::equalDateTime(const QVariant &v1, const QVariant &v2)
{
    auto d1=toDate(v1);
    auto d2=toDate(v2);
    return (d1==d2);
}

bool MUDateUtil::equalTime(const QVariant &v1, const QVariant &v2)
{
    auto d1=toTime(v1);
    auto d2=toTime(v2);
    return (d1==d2);
}
