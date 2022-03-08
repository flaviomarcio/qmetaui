#pragma once

#include "./mu_global.h"
#include "./mu_string_util.h"

class Q_MU_EXPORT MUPaintSettingGeometry : public QObject
{
    Q_OBJECT
    friend class Q_MU_EXPORT MUPaintSettingState;
public:

    MU_DECLARE_MUStringUtil()

    Q_PROPERTY(QVariant    height                MEMBER height               )
    Q_PROPERTY(QVariant    width                 MEMBER width                )
    Q_PROPERTY(QVariant    anchorsMarginOnTop    MEMBER anchorsMarginOnTop   )
    Q_PROPERTY(QVariant    anchorsMarginOnBottom MEMBER anchorsMarginOnBottom)
    Q_PROPERTY(QVariant    anchorsMarginOnLeft   MEMBER anchorsMarginOnLeft  )
    Q_PROPERTY(QVariant    anchorsMarginOnRight  MEMBER anchorsMarginOnRight )
    Q_PROPERTY(QVariant    anchorsMargins        MEMBER anchorsMargins       )
    Q_PROPERTY(QVariant    roundMargin           MEMBER roundMargin          )

    Q_INVOKABLE explicit MUPaintSettingGeometry(QObject *parent = nullptr);
    Q_INVOKABLE explicit MUPaintSettingGeometry(const MUPaintSettingGeometry &parent) : QObject(nullptr){
        Q_FOREACH( const QByteArray & prop, parent.dynamicPropertyNames() )
                    setProperty( prop.constData(), parent.property( prop.constData() ) );
    }
    ~MUPaintSettingGeometry();

    Q_INVOKABLE static int desktopAvailableWidth();
    Q_INVOKABLE static void setDesktopAvailableWidth(int value);

    Q_INVOKABLE static int desktopAvailableHeight();
    Q_INVOKABLE static void setDesktopAvailableHeight(int value);

    Q_INVOKABLE double calcProportion(const QVariant &size, const double &sizeMax);
    Q_INVOKABLE double calcWidth(const QVariant &v);
    Q_INVOKABLE double calcHeight(const QVariant &v);

    Q_INVOKABLE void replaceInvalid(MUPaintSettingGeometry&baseObject);


private:
    void*p=nullptr;

    QVariant height = "0.5%";
    QVariant width = "0.5%";
    QVariant anchorsMarginOnTop = 0;
    QVariant anchorsMarginOnBottom = 0;
    QVariant anchorsMarginOnLeft = 0;
    QVariant anchorsMarginOnRight = 0;
    QVariant anchorsMargins = 0;
    QVariant roundMargin = 0;

signals:
    void refresh();
};

Q_DECLARE_METATYPE(MUPaintSettingGeometry   )
