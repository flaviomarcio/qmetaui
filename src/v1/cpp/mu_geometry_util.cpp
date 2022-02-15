#include "./mu_geometry_util.h"
#include "./mu_object_util.h"

#if defined(Q_OS_ANDROID)
    #include <QtAndroid>
#endif

#include <QGuiApplication>
#include <QScreen>


static int staticDesktopAvailableWidth=1024;
static int staticDesktopAvailableHeight=640;

Q_GLOBAL_STATIC(MUGeometryUtil, muGeometryUtil)

MUGeometryUtil::MUGeometryUtil(QObject *parent) : QObject(parent)
{

}

MUGeometryUtil::~MUGeometryUtil()
{

}

MUGeometryUtil &MUGeometryUtil::i()
{
    return*muGeometryUtil;
}


const QVariant MUGeometryUtil::ifThen(const QVariant &vThen, const QVariant &vElse)
{
    return MUObjectUtil::ifThen(vThen, vElse);
}

bool MUGeometryUtil::isDefined(const QVariant &v)
{
    return MUObjectUtil::isDefined(v);
}

bool MUGeometryUtil::isUndefined(const QVariant &v)
{
    return MUObjectUtil::isUndefined(v);
}

int MUGeometryUtil::desktopAvailableWidth()
{
    return staticDesktopAvailableWidth;
}

void MUGeometryUtil::setDesktopAvailableWidth(int value)
{
    staticDesktopAvailableWidth=value;
}

int MUGeometryUtil::desktopAvailableHeight()
{
    return staticDesktopAvailableHeight;
}

void MUGeometryUtil::setDesktopAvailableHeight(int value)
{
    staticDesktopAvailableHeight=value;
}

double MUGeometryUtil::toDoubleSize(const QVariant &v, const QVariant&defaultValue)
{
    auto vv=QVariant(v.toString().replace(qsl("%"), qsl_null));
    switch (qTypeId(vv)) {
    case QMetaType_Double:
    case QMetaType_Int:
    case QMetaType_LongLong:
    case QMetaType_UInt:
    case QMetaType_ULongLong:
        return vv.toDouble();
    default:
        return defaultValue.toDouble();
    }
}

qlonglong MUGeometryUtil::toIntSize(const QVariant &v, const QVariant&defaultValue)
{
    auto vv=QVariant(v.toString().replace(qsl("%"), qsl_null));
    switch (qTypeId(vv)) {
    case QMetaType_Double:
    case QMetaType_Int:
    case QMetaType_LongLong:
    case QMetaType_UInt:
    case QMetaType_ULongLong:
        return vv.toLongLong();
    default:
        return defaultValue.toLongLong();
    }
}

const QString MUGeometryUtil::toProportion(const QVariant &v)
{
    if(!v.isValid())
        return {};
    auto vv=v.toString().trimmed();
    if(vv.contains(qsl("%")))
        return qsl("%");
    return vv;
}

double MUGeometryUtil::calcProportion(const QVariant &vSize, const QVariant &vSizeMax)
{
    auto sizeMax=vSizeMax.toDouble();
    bool proportion=vSize.toString().contains(qsl("%"));
    double size=toDoubleSize(vSize);
    size=toDoubleSize(size);
    if(proportion)
        size=(size>100)?100:size;
    size=(size<0)?0:size;
    sizeMax=toDoubleSize(sizeMax);
    sizeMax=(sizeMax<=0)?0:sizeMax;
    double r=proportion ? ((sizeMax/100)*size) : size;
    return r;
}

double calcProportion (bool fontRatio)
{
    double refDpi = 216. ;
    double refHeight = 1776.; //1920
    double refWidth = 1080.;

#if (defined(Q_OS_ANDROID) || defined(Q_OS_IOS))
    QRect  rect   = QGuiApplication::primaryScreen()->geometry();
    double height = qMax(rect.width(), rect.height());
    double width  = qMin(rect.width(), rect.height());
    double dpi    = QGuiApplication::primaryScreen()->logicalDotsPerInch();
#else
    double height = 1776;
    double width = 1080/3;
    double dpi = 64;
#endif

    if (fontRatio)
        return qMin<double>(height*refDpi/(dpi*refHeight), width*refDpi/(dpi*refWidth));
    return qMin(height/refHeight, width/refWidth);

}

double MUGeometryUtil::proportion()
{
    return calcProportion(false);
}

double MUGeometryUtil::proportionFont()
{
    return calcProportion(true);
}

double MUGeometryUtil::heightBase()
{
#if (defined(Q_OS_ANDROID) || defined(Q_OS_IOS))
    QScreen* m_screen = QGuiApplication::primaryScreen();
    if (!m_screen)
        return 0;
    return qMax(m_screen->availableVirtualSize().width(), m_screen->availableVirtualSize().height());
#else
    return ( 1.1 * 648 );
#endif
}

double MUGeometryUtil::widthBase()
{
#if (defined(Q_OS_ANDROID) || defined(Q_OS_IOS))
    QScreen* m_screen = QGuiApplication::primaryScreen();
    if (!m_screen)
        return 0;
    return qMin(m_screen->availableVirtualSize().width(), m_screen->availableVirtualSize().height());
#else
    return ( 1.1 * 360 );
#endif
}

void MUGeometryUtil::hideSplashScreen()
{
#if defined(Q_OS_ANDROID)
    QtAndroid::hideSplashScreen();
#endif
    return;
}

