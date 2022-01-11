#ifndef MUPaintSettingItem_H
#define MUPaintSettingItem_H

#include "./mu_global.h"
#include "./mu_paint_setting_state.h"

class Q_MU_EXPORT MUPaintSettingItem : public QObject
{
    Q_OBJECT
public:
    MU_DECLARE_MUStringUtil()
    Q_INVOKABLE explicit MUPaintSettingItem(QObject *parent = nullptr);
    Q_INVOKABLE explicit MUPaintSettingItem(const MUPaintSettingItem &parent) : QObject(nullptr){
        Q_FOREACH( const QByteArray & prop, parent.dynamicPropertyNames() )
                    setProperty( prop.constData(), parent.property( prop.constData() ) );
    }

    Q_INVOKABLE MUPaintSettingState&active();
    Q_INVOKABLE MUPaintSettingState&focused();
    Q_INVOKABLE MUPaintSettingState&pressed();
    Q_INVOKABLE MUPaintSettingState&inactive();


    Q_INVOKABLE void readValues(const QVariant &json);
    Q_INVOKABLE void replaceInvalid(MUPaintSettingItem &baseObject);

private:
    MUPaintSettingState _active;
    MUPaintSettingState _focused;
    MUPaintSettingState _pressed;
    MUPaintSettingState _inactive;
signals:
    void refresh();
    void changed();
};

#endif // MUPaintSettingItem_H
