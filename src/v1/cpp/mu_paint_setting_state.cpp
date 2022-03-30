#include "mu_paint_setting_state.h"

MUPaintSettingState::MUPaintSettingState(QObject *parent) : QObject{parent}, _geometry(this), _drawing(this)
{

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
    else{
         auto jsonGeometry=jsonObject.value("geometry").toMap();
         if(!jsonGeometry.isEmpty()){
             control.geometry().height                = jsonGeometry.value("height");
             control.geometry().width                 = jsonGeometry.value("width");
             control.geometry().anchorsMarginOnTop    = jsonGeometry.value("anchorsMarginOnTop");
             control.geometry().anchorsMarginOnTop    = jsonGeometry.value("anchorsMarginOnTop");
             control.geometry().anchorsMarginOnBottom = jsonGeometry.value("anchorsMarginOnBottom");
             control.geometry().anchorsMarginOnLeft   = jsonGeometry.value("anchorsMarginOnLeft");
             control.geometry().anchorsMarginOnRight  = jsonGeometry.value("anchorsMarginOnRight");
             control.geometry().anchorsMargins        = jsonGeometry.value("anchors.margins");
             control.geometry().roundMargin           = jsonGeometry.value("round.margin");
         }

         auto jsonDrawing=jsonObject.value("drawing").toMap();
         if(!jsonObject.isEmpty()){
             control.drawing().fontSize        = jsonDrawing.value("font.size").toInt();
             control.drawing().fontFamily      = jsonDrawing.value("font.name").toString();
             control.drawing().fontColor       = this->u().toColor(jsonDrawing.value("font.color"));
             control.drawing().fontItalic      = jsonDrawing.value("font.italic").toBool();
             control.drawing().fontBold        = jsonDrawing.value("font.bold").toBool();
             control.drawing().color           = this->u().toColor(jsonDrawing.value("color"));
             control.drawing().borderColor     = this->u().toColor(jsonDrawing.value("border.color"));
             control.drawing().borderWidth     = jsonDrawing.value("border.width");
         }
    }
}
