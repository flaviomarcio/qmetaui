#include "mu_paint_setting_item.h"

MUPaintSettingItem::MUPaintSettingItem(QObject *parent) : QObject{parent}
{

}

MUPaintSettingItem::MUPaintSettingItem(const MUPaintSettingItem &parent) : QObject{nullptr}{
    Q_FOREACH( const QByteArray & prop, parent.dynamicPropertyNames() )
        setProperty( prop.constData(), parent.property( prop.constData() ) );
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
        auto jsonSettingActive = jsonObject.value(QStringLiteral("active"));
        auto jsonSettingFocused = jsonObject.value(QStringLiteral("focused"));
        auto jsonSettingPressed = jsonObject.value(QStringLiteral("pressed"));
        auto jsonSettingInactive = jsonObject.value(QStringLiteral("inactive"));

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
