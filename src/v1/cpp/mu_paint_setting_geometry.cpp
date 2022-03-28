#include "./mu_paint_setting_geometry.h"
#include "./mu_geometry_util.h"
#include <QStm>

#define dPvt()\
    auto&pvt = *reinterpret_cast<MUPaintSettingGeometryPvt*>(this->p)

class MUPaintSettingGeometryPvt{
public:
    MUPaintSettingGeometry*parent=nullptr;
    explicit MUPaintSettingGeometryPvt(MUPaintSettingGeometry*parent)
    {
        this->parent=parent;
    }
    virtual ~MUPaintSettingGeometryPvt()
    {
    }
};


MUPaintSettingGeometry::MUPaintSettingGeometry(QObject *parent) : QObject{parent}
{
    this->p=new MUPaintSettingGeometryPvt(this);
}

MUPaintSettingGeometry::~MUPaintSettingGeometry()
{

}

int MUPaintSettingGeometry::desktopAvailableWidth()
{
    return MUGeometryUtil::desktopAvailableWidth();
}

void MUPaintSettingGeometry::setDesktopAvailableWidth(int value)
{
    return MUGeometryUtil::setDesktopAvailableWidth(value);
}

int MUPaintSettingGeometry::desktopAvailableHeight()
{
    return MUGeometryUtil::desktopAvailableHeight();
}

void MUPaintSettingGeometry::setDesktopAvailableHeight(int value)
{
    return MUGeometryUtil::setDesktopAvailableHeight(value);
}

double MUPaintSettingGeometry::calcProportion(const QVariant &size, const double &sizeMax)
{
    return MUGeometryUtil::calcProportion(size, sizeMax);
}

double MUPaintSettingGeometry::calcWidth(const QVariant &v)
{
    QVariant vv;
    switch (qTypeId(v)){
    case QMetaType_Double:
    case QMetaType_Int:
    case QMetaType_UInt:
    case QMetaType_LongLong:
    case QMetaType_ULongLong:
        vv=v.toDouble();
        break;
    case QMetaType_QString:
    case QMetaType_QByteArray:
        vv=v.toString();
        break;
    default:
        vv={};
    }
    vv=vv.isValid()?vv:this->width;
    return MUGeometryUtil::calcProportion(vv, this->desktopAvailableWidth());
}

double MUPaintSettingGeometry::calcHeight(const QVariant &v)
{
    QVariant vv;
    switch (qTypeId(v)){
    case QMetaType_Double:
    case QMetaType_Int:
    case QMetaType_UInt:
    case QMetaType_LongLong:
    case QMetaType_ULongLong:
        vv=v.toDouble();
        break;
    default:
        vv={};
    }
    vv=vv.isValid()?vv:this->height;
    return MUGeometryUtil::calcProportion(vv, this->desktopAvailableHeight());
}

void MUPaintSettingGeometry::replaceInvalid(MUPaintSettingGeometry &baseObject)
{
    auto&control=*this;

    baseObject.height                  =baseObject.height.isValid()?baseObject.height:qsl("0.5%");
    baseObject.width                   =baseObject.width.isValid()?baseObject.width:qsl("0.5%");

    baseObject.anchorsMarginOnTop      =(baseObject.anchorsMarginOnTop.isValid())?0:baseObject.anchorsMarginOnTop;
    baseObject.anchorsMarginOnBottom   =(baseObject.anchorsMarginOnBottom.isValid())?0:baseObject.anchorsMarginOnBottom;
    baseObject.anchorsMarginOnLeft     =(baseObject.anchorsMarginOnLeft.isValid())?0:baseObject.anchorsMarginOnLeft;
    baseObject.anchorsMarginOnRight    =(baseObject.anchorsMarginOnRight.isValid())?0:baseObject.anchorsMarginOnRight;
    baseObject.anchorsMargins          =(baseObject.anchorsMargins.isValid())?0:baseObject.anchorsMargins;
    baseObject.roundMargin             =(baseObject.roundMargin.isValid())?0:baseObject.roundMargin;

    control.anchorsMarginOnTop    = baseObject.anchorsMarginOnTop   ;
    control.anchorsMarginOnBottom = baseObject.anchorsMarginOnBottom;
    control.anchorsMarginOnLeft   = baseObject.anchorsMarginOnLeft  ;
    control.anchorsMarginOnRight  = baseObject.anchorsMarginOnRight ;
    control.anchorsMargins        = baseObject.anchorsMargins       ;
    control.roundMargin           = baseObject.roundMargin          ;
}
