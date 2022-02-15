#include "./mu_date_util.h"
#include "./mu_object_util.h"
#include <QLocale>
#include <QDebug>

#define dPvt()\
    auto&p = *reinterpret_cast<MUDateUtilPvt*>(this->p)

class MUDateUtilPvt
{
public:
    QString token;
    QVariantMap rawHeader;
    QString protocol=qsl("http");
    QString host=qsl("localhost");
    int port=8080;
    QString route=qsl("/");
    QString endpoint=qsl_null;

    explicit MUDateUtilPvt()
    {
    }

    virtual ~MUDateUtilPvt()
    {
    }

    static QString toDateTimeFormat(const QDate &d, const QTime &t,const QString&format)
    {
        Q_UNUSED(format)
        if(d.isValid() && t.isValid())
            return d.toString(qsl("d MMM yyyy"))+" "+t.toString(qsl("HH:mm:ss"));

        if(d.isValid())
            return d.toString(qsl("d MMM yyyy"));

        if(t.isValid())
            return t.toString(qsl("HH:mm:ss"));

        return {};
    }


    static QString toDateTimeInput(const QDate &d, const QTime &t,const QString&format)
    {
        Q_UNUSED(format)
        if(d.isValid() && t.isValid())
            return d.toString(qsl("dd/MM/yyyy"))+qsl(" ")+t.toString(qsl("HH:mm:ss"));

        if(d.isValid())
            return d.toString(qsl("dd/MM/yyyy"));

        if(t.isValid())
            return t.toString(qsl("HH:mm:ss"));

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
    //TODO implement switch (typeId) {}
    if(v.canConvert(QMetaType_QString) || v.canConvert(QMetaType_QChar) || v.canConvert(QMetaType_QByteArray))
        return v.toString().trimmed().isEmpty();
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
    //TODO implement switch (typeId) {}
    if(vDt.canConvert(QMetaType_QTime))
        return vDt.toTime().toString(Qt::ISODate);

    if(vDt.canConvert(QMetaType_QDate))
        return vDt.toDate().toString(Qt::ISODate);

    if(vDt.canConvert(QMetaType_QDateTime))
        return vDt.toDateTime().toString(Qt::ISODateWithMs);

    return {};
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

QDateTime MUDateUtil::toDate(const QVariant &vDt)
{
    auto dt=vDt.toDate();
    if(!dt.isValid())
        dt=QDate::fromString(vDt.toString(),qsl("dd/MM/yyyy"));
    if(!dt.isValid())
        dt=QDate::fromString(vDt.toString(),qsl("dd-MM-yyyy"));

    return QDateTime(dt,QTime());
}

QDateTime MUDateUtil::toTime(const QVariant &vDt)
{
    return QDateTime(QDate(),vDt.toTime());
}

QDateTime MUDateUtil::toDateTime(const QVariant &vDt)
{
    QDateTime vv;
    if(vDt.type()==QMetaType_QDateTime || vDt.type()==QMetaType_QDate || vDt.type()==QMetaType_QTime){
        if(vDt.type()==QMetaType_QDateTime)
            vv=vDt.toDateTime();
        else if(vDt.type()==QMetaType_QDate)
            vv=QDateTime(vDt.toDate(),QTime());
        else if(vDt.type()==QMetaType_QTime)
            vv=QDateTime(QDate(1901,1,1),vDt.toTime());
    }
    else if(vDt.type()==QMetaType_Double || vDt.type()==QMetaType_Int || vDt.type()==QVariant::UInt || vDt.type()==QMetaType_LongLong || vDt.type()==QVariant::ULongLong){
        vv=QDateTime::fromMSecsSinceEpoch(vDt.toLongLong());
    }
    else{
        if(vDt.canConvert(QMetaType_QDateTime))
            vv=vDt.toDateTime();
        else if(vDt.canConvert(QMetaType_QTime))
            vv=QDateTime(QDate(1901,1,1),vDt.toTime());
        else if(vDt.canConvert(QMetaType_QDate))
            vv=QDateTime::fromString(vDt.toString()).toLocalTime();

        if(!vv.isValid()){
            if(vDt.canConvert(QMetaType_QDateTime))
                vv=QDateTime::fromString(vDt.toString()).toLocalTime();
            else if(vDt.canConvert(QMetaType_QTime))
                vv=QDateTime(QDate(1901,01,01), QTime::fromString(vDt.toString())).toLocalTime();
            else if(vDt.canConvert(QMetaType_QDate))
                vv=QDateTime(QDate::fromString(vDt.toString()),QTime()).toLocalTime();
        }
    }

    return vv;
}

int MUDateUtil::dayOfWeek(const QVariant &vDt)
{
    auto v=toDate(vDt).date();
    return v.dayOfWeek();
}

QString MUDateUtil::dayOfWeekName(const QVariant &vDt)
{
    return toDate(vDt).toString(qsl("dddd"));
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

QVariantList MUDateUtil::daysMonthModel(const QVariant &year, const QVariant &month)
{
    QVariantList vList;
    for (int day = 0; day < daysInMonth(year, month); ++day) {
        QVariantMap map;
        auto dd=QDate(year.toInt(), month.toInt(), 1);
        map.insert(qsl("name"), dayOfWeekName(dd) );
        map.insert(qsl("day"), QString::number(day).rightJustified(2,'0') );
        vList<<map;
    }
    return vList;
}

int MUDateUtil::year(const QVariant &date)
{
    auto v=date.canConvert(QMetaType_QDate)?date.toDate():QDate::currentDate();
    return v.year();
}

int MUDateUtil::month(const QVariant &date)
{
    auto v=date.canConvert(QMetaType_QDate)?date.toDate():QDate::currentDate();
    return v.month();
}

int MUDateUtil::day(const QVariant &date)
{
    auto v=date.canConvert(QMetaType_QDate)?date.toDate():QDate::currentDate();
    return v.day();
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
    auto dt=date.canConvert(QMetaType_QDate)?date.toDate():QDate::currentDate();//
    dt=nextDayMonth(dt.year(),dt.month()).date();
    dt=QDate(dt.year(), dt.month(), dt.daysInMonth());
    return QDateTime(dt,QTime());
}

QString MUDateUtil::monthName(const QVariant &month)
{
    int m=0;
    if(month.canConvert(QMetaType_Int))
        m=month.toInt();
    else if(month.canConvert(QMetaType_QDateTime))
        m=month.toDateTime().date().month();
    else if(month.canConvert(QMetaType_QDate))
        m=month.toDate().month();
    else
        m=QDate::currentDate().month();

    m=(m>0 && m<=12)?m:1;

    return QLocale::c().monthName(m);
}

bool MUDateUtil::isHigherDateTime(const QVariant &v1, const QVariant &v2)
{
    auto d1=v1.canConvert(QMetaType_QDateTime)?v1.toDateTime():QDateTime(v1.toDate(), QTime());
    auto d2=v2.canConvert(QMetaType_QDateTime)?v2.toDateTime():QDateTime(v2.toDate(), QTime());
    return (d1>=d2);
}

bool MUDateUtil::isLowerDateTime(const QVariant &v1, const QVariant &v2)
{
    auto d1=v1.canConvert(QMetaType_QDateTime)?v1.toDateTime():QDateTime(v1.toDate(), QTime());
    auto d2=v2.canConvert(QMetaType_QDateTime)?v2.toDateTime():QDateTime(v2.toDate(), QTime());
    return (d1<d2);
}

bool MUDateUtil::isBetweenDateTime(const QVariant &v1, const QVariant &v2)
{
    auto d1=v1.canConvert(QMetaType_QDateTime)?v1.toDateTime():QDateTime(v1.toDate(), QTime());
    auto d2=v2.canConvert(QMetaType_QDateTime)?v2.toDateTime():QDateTime(v2.toDate(), QTime());
    auto da = QDateTime::currentDateTime();
    return (da >= d1) && (da <= d2);
}

bool MUDateUtil::equalDate(const QVariant &v1, const QVariant &v2)
{
    auto d1=v1.canConvert(QMetaType_QDateTime)?v1.toDateTime().date():v1.toDate();
    auto d2=v2.canConvert(QMetaType_QDateTime)?v2.toDateTime().date():v2.toDate();
    return (d1==d2);    
}

bool MUDateUtil::equalDateTime(const QVariant &v1, const QVariant &v2)
{
    auto d1=v1.canConvert(QMetaType_QDateTime)?v1.toDateTime():QDateTime();
    auto d2=v2.canConvert(QMetaType_QDateTime)?v2.toDateTime():QDateTime();
    return (d1==d2);
}

bool MUDateUtil::equalTime(const QVariant &v1, const QVariant &v2)
{
    auto d1=v1.canConvert(QMetaType_QDateTime)?v1.toDateTime().time():v1.toTime();
    auto d2=v2.canConvert(QMetaType_QDateTime)?v2.toDateTime().time():v2.toTime();
    return (d1==d2);
}
