#include "mu_paint_setting_drawing.h"

MUPaintSettingDrawing::MUPaintSettingDrawing(QObject *parent) : QObject(parent)
{

}

MUPaintSettingDrawing::MUPaintSettingDrawing(const MUPaintSettingDrawing &parent) : QObject(nullptr){
    Q_FOREACH( const QByteArray & prop, parent.dynamicPropertyNames() )
        setProperty( prop.constData(), parent.property( prop.constData() ) );
}

MUPaintSettingDrawing::~MUPaintSettingDrawing()
{

}

void MUPaintSettingDrawing::replaceInvalid(MUPaintSettingDrawing &baseObject)
{
    auto&control=*this;
    baseObject.fontFamily=(baseObject.fontFamily.trimmed()==qsl_null)?qsl("Sans Serif"):baseObject.fontFamily;
    baseObject.fontSize=(baseObject.fontSize<0)?6:baseObject.fontSize;
    baseObject.borderWidth=(!baseObject.borderWidth.isValid())?0:baseObject.borderWidth;

    auto fontSize        = control.fontSize    ;
    auto fontFamily      = control.fontFamily  ;
    auto fontColor       = control.fontColor   ;
    auto fontItalic      = control.fontItalic  ;
    auto fontBold        = control.fontBold    ;
    auto color           = control.color       ;
    auto borderColor     = control.borderColor ;
    auto borderWidth     = control.borderWidth ;

    fontSize        = (fontSize             )? baseObject.fontSize        : fontSize        ;
    fontFamily      = (fontFamily==qsl_null )? baseObject.fontFamily      : fontFamily      ;
    fontColor       = (fontColor==qsl_null  )? baseObject.fontColor       : fontColor       ;
    color =           (color.isValid()      )? baseObject.color : color ;
    borderColor     = (borderColor==qsl_null)? baseObject.borderColor     : borderColor     ;
    borderWidth     = (borderWidth.isValid())? baseObject.borderWidth     : borderWidth     ;

    control.fontSize        = fontSize       ;
    control.fontFamily      = fontFamily     ;
    control.fontColor       = fontColor      ;
    control.fontItalic      = fontItalic     ;
    control.fontBold        = fontBold       ;
    control.color = color;
    control.borderColor     = borderColor    ;
    control.borderWidth    = borderWidth    ;
}
