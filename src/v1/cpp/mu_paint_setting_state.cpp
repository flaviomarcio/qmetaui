#include "mu_paint_setting_state.h"

MUPaintSettingState::MUPaintSettingState(QObject *parent) : QObject{parent}, _geometry(this), _drawing(this)
{

}

MUPaintSettingState::MUPaintSettingState(const MUPaintSettingState &parent) : QObject{nullptr}{
    Q_FOREACH( const QByteArray & prop, parent.dynamicPropertyNames() )
        setProperty( prop.constData(), parent.property( prop.constData() ) );
}

MUPaintSettingGeometry &MUPaintSettingState::geometry()
{
    return this->_geometry;
}

MUPaintSettingDrawing &MUPaintSettingState::drawing()
{
    return this->_drawing;
}

void MUPaintSettingState::replaceInvalid(MUPaintSettingState &baseObject)
{
    this->_geometry.replaceInvalid(baseObject._geometry);
    this->_drawing.replaceInvalid(baseObject._drawing);
}

void MUPaintSettingState::readValues(const QVariant &json)
{
    auto jsonObject = this->u().toMap(json);

    auto&control=*this;

    if(jsonObject.isEmpty())
        return;

    auto jsonGeometry=jsonObject.value(QStringLiteral("geometry")).toHash();
    if(!jsonGeometry.isEmpty()){
        control.geometry().height                = jsonGeometry.value(QStringLiteral("height"));
        control.geometry().width                 = jsonGeometry.value(QStringLiteral("width"));
        control.geometry().anchorsMarginOnTop    = jsonGeometry.value(QStringLiteral("anchorsMarginOnTop"));
        control.geometry().anchorsMarginOnTop    = jsonGeometry.value(QStringLiteral("anchorsMarginOnTop"));
        control.geometry().anchorsMarginOnBottom = jsonGeometry.value(QStringLiteral("anchorsMarginOnBottom"));
        control.geometry().anchorsMarginOnLeft   = jsonGeometry.value(QStringLiteral("anchorsMarginOnLeft"));
        control.geometry().anchorsMarginOnRight  = jsonGeometry.value(QStringLiteral("anchorsMarginOnRight"));
        control.geometry().anchorsMargins        = jsonGeometry.value(QStringLiteral("anchors.margins"));
        control.geometry().roundMargin           = jsonGeometry.value(QStringLiteral("round.margin"));
    }

    auto jsonDrawing=jsonObject.value(QStringLiteral("drawing")).toHash();
    if(!jsonObject.isEmpty()){
        control.drawing().fontSize        = jsonDrawing.value(QStringLiteral("font.size")).toInt();
        control.drawing().fontFamily      = jsonDrawing.value(QStringLiteral("font.name")).toString();
        control.drawing().fontColor       = this->u().toColor(jsonDrawing.value(QStringLiteral("font.color")));
        control.drawing().fontItalic      = jsonDrawing.value(QStringLiteral("font.italic")).toBool();
        control.drawing().fontBold        = jsonDrawing.value(QStringLiteral("font.bold")).toBool();
        control.drawing().color           = this->u().toColor(jsonDrawing.value(QStringLiteral("color")));
        control.drawing().borderColor     = this->u().toColor(jsonDrawing.value(QStringLiteral("border.color")));
        control.drawing().borderWidth     = jsonDrawing.value(QStringLiteral("border.width"));
    }
}
