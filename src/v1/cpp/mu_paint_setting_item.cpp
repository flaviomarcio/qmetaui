#include "mu_paint_setting_item.h"

MUPaintSettingItem::MUPaintSettingItem(QObject *parent) : QObject{parent}
{

}

MUPaintSettingState&MUPaintSettingItem::active()
{
    return this->_active;
}

MUPaintSettingState &MUPaintSettingItem::focused()
{
    return this->_focused;
}

MUPaintSettingState &MUPaintSettingItem::pressed()
{
    return this->_pressed;
}

MUPaintSettingState &MUPaintSettingItem::inactive()
{
    return this->_inactive;
}

void MUPaintSettingItem::readValues(const QVariant &json)
{
    auto jsonObject=this->u().toMap(json);

    if(!jsonObject.isEmpty()){
        auto jsonSettingActive = jsonObject.value("active");
        auto jsonSettingFocused = jsonObject.value("focused");
        auto jsonSettingPressed = jsonObject.value("pressed");
        auto jsonSettingInactive = jsonObject.value("inactive");

        this->active().readValues(jsonSettingActive);
        this->focused().readValues(jsonSettingFocused);
        this->pressed().readValues(jsonSettingPressed);
        this->inactive().readValues(jsonSettingInactive);
    }
}

void MUPaintSettingItem::replaceInvalid(MUPaintSettingItem &baseObject)
{
    this->active().replaceInvalid(baseObject.active());
    this->focused().replaceInvalid(baseObject.focused());
    this->pressed().replaceInvalid(baseObject.pressed());
    this->inactive().replaceInvalid(baseObject.inactive());
}
