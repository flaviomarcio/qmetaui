#include "mu_paint_setting_drawing.h"

MUPaintSettingDrawing::MUPaintSettingDrawing(QObject *parent) : QObject(parent)
{

}

MUPaintSettingDrawing::~MUPaintSettingDrawing()
{

}

void MUPaintSettingDrawing::replaceInvalid(MUPaintSettingDrawing &baseObject)
{
    auto&control=*this;
    baseObject.fontFamily=(baseObject.fontFamily.trimmed()=="")?QStringLiteral("Sans Serif"):baseObject.fontFamily;
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
    fontFamily      = (fontFamily==""       )? baseObject.fontFamily      : fontFamily      ;
    fontColor       = (fontColor==""        )? baseObject.fontColor       : fontColor       ;
    color =           (color.isValid()      )? baseObject.color : color ;
    borderColor     = (borderColor==""      )? baseObject.borderColor     : borderColor     ;
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
