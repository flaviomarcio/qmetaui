#pragma once

#include "./mu_global.h"
#include "./mu_paint_setting_item.h"

#define declareV(var)\
    public:\
    Q_INVOKABLE const MUPaintSettingItem &var(){\
    return pvt##var;\
    }\
    private:\
    MUPaintSettingItem pvt##var;\


#define initV(var) pvt##var(this)

class Q_MU_EXPORT MUPaintSetting : public QObject
{
    Q_OBJECT
public:
    MU_DECLARE_MUStringUtil()

    declareV(settingBase)
    declareV(button)
    declareV(buttonTool)
    declareV(buttonTabBar)
    declareV(buttonToggle)
    declareV(buttonFlat)
    declareV(buttonSolid)
    declareV(lineEdit)
    declareV(label)
    declareV(separator)
    declareV(rectangle)
    declareV(header)
    declareV(sumary)
    declareV(form)
    declareV(formHeader)
    declareV(toolBar)
    declareV(toolBarButton)
    declareV(delegateCell)
    declareV(delegateLabel)
    declareV(viewList)
    declareV(viewListaHeader)
    declareV(viewListCell)
    declareV(viewGrid)
    declareV(viewGridaHeader)
    declareV(viewGridaCell)

public:
    Q_INVOKABLE explicit MUPaintSetting(QObject *parent = nullptr);
    ~MUPaintSetting();

    Q_INVOKABLE static int desktopAvailableWidth();
    Q_INVOKABLE static void setDesktopAvailableWidth(int value);

    Q_INVOKABLE static int desktopAvailableHeight();
    Q_INVOKABLE static void setDesktopAvailableHeight(int value);

    static MUPaintSetting&i();

    Q_INVOKABLE void replaceInvalid(MUPaintSettingItem &settingBase);

    Q_INVOKABLE QVariant jsonObject();
private:
    void*p=nullptr;
signals:
    void refresh();
};
