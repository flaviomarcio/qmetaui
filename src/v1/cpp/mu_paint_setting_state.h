#ifndef MUPaintSettingState_H
#define MUPaintSettingState_H

#include "./mu_global.h"
#include "./mu_paint_setting_drawing.h"
#include "./mu_paint_setting_geometry.h"

class Q_MU_EXPORT MUPaintSettingState : public QObject
{
    Q_OBJECT
public:
    MU_DECLARE_MUStringUtil()
    Q_INVOKABLE explicit MUPaintSettingState(QObject *parent = nullptr);
    Q_INVOKABLE explicit MUPaintSettingState(const MUPaintSettingState &parent) : QObject(nullptr){
        Q_FOREACH( const QByteArray & prop, parent.dynamicPropertyNames() )
                    setProperty( prop.constData(), parent.property( prop.constData() ) );
    }
    Q_INVOKABLE MUPaintSettingGeometry&geometry();
    Q_INVOKABLE MUPaintSettingDrawing&drawing();

    Q_INVOKABLE void replaceInvalid(MUPaintSettingState &baseObject);
    Q_INVOKABLE void readValues(const QVariant&jsonObject);

    //Q_PROPERTY(MUPaintSettingGeometry MEMBER _geometry)
    //Q_PROPERTY(MUPaintSettingDrawing  MEMBER _drawing)

    MUPaintSettingGeometry _geometry;
    MUPaintSettingDrawing _drawing;
signals:
    void refresh();
};

Q_DECLARE_METATYPE(MUPaintSettingState      )


#endif // MUPaintSettingState_H
