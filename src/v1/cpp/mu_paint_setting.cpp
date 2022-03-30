#include "mu_paint_setting.h"
#include "./mu_geometry_util.h"

#define dPvt()\
    auto&p = *reinterpret_cast<MUPaintSettingPvt*>(this->p)

class MUPaintSettingPvt{
public:
    QVariant jsonObject;
    MUPaintSetting*parent=nullptr;
    explicit MUPaintSettingPvt(MUPaintSetting*parent) {
        this->parent=parent;
    }
    virtual ~MUPaintSettingPvt(){
    }
};

MUPaintSetting::MUPaintSetting(QObject *parent) : QObject{parent}
  ,initV(settingBase)
  ,initV(button)
  ,initV(buttonTool)
  ,initV(buttonTabBar)
  ,initV(buttonToggle)
  ,initV(buttonFlat)
  ,initV(buttonSolid)
  ,initV(lineEdit)
  ,initV(label)
  ,initV(separator)
  ,initV(rectangle)
  ,initV(header)
  ,initV(form)
  ,initV(formHeader)
  ,initV(toolBar)
  ,initV(toolBarButton)
  ,initV(delegateCell)
  ,initV(delegateLabel)
  ,initV(viewList)
  ,initV(viewListaHeader)
  ,initV(viewListCell)
  ,initV(viewGrid)
  ,initV(viewGridaHeader)
  ,initV(viewGridaCell)
{
    this->p = new MUPaintSettingPvt(this);
    //loadSettings();
}

MUPaintSetting::~MUPaintSetting()
{
    dPvt();
    delete&p;
}

int MUPaintSetting::desktopAvailableWidth(){
    return MUGeometryUtil::desktopAvailableWidth();
}

void MUPaintSetting::setDesktopAvailableWidth(int value)
{
    MUGeometryUtil::setDesktopAvailableWidth(value);
}

int MUPaintSetting::desktopAvailableHeight(){
    return MUGeometryUtil::desktopAvailableHeight();
}

void MUPaintSetting::setDesktopAvailableHeight(int value)
{
    MUGeometryUtil::setDesktopAvailableHeight(value);
}

MUPaintSetting &MUPaintSetting::i()
{
    static MUPaintSetting*__MUPaintSetting=nullptr;
    if(__MUPaintSetting==nullptr){
        __MUPaintSetting=new MUPaintSetting(nullptr);
    }

    return*__MUPaintSetting;
}

//void MUPaintSetting::loadSettings(QString fileName)
//{
//    dPvt();
//    fileName=(fileName.trimmed().isEmpty())?":/QMetaUI/Controls/mcpaintsetting.json":fileName;

//    auto jsonObject=this->u().loadFileMap(fileName).toMap();
//    p.jsonObject=jsonObject;

//    auto dataSettingBase    = (jsonObject["settingBase"]);
//    auto dataButton         = (jsonObject["button"]);
//    auto dataButtonTool     = (jsonObject["buttonTool"]);
//    auto dataButtonTabBar   = (jsonObject["ButtonTabBar"]);
//    auto dataButtonToggle   = (jsonObject["ButtonToggle"]);
//    auto dataButtonFlat     = (jsonObject["ButtonFlat"]);
//    auto dataButtonSolid    = (jsonObject["ButtonSolid"]);
//    auto dataLineEdit       = (jsonObject["lineEdit"]);
//    auto dataLabel          = (jsonObject["label"]);
//    auto dataSeparator      = (jsonObject["separator"]);
//    auto dataRectangle      = (jsonObject["rectangle"]);
//    auto dataHeader         = (jsonObject["header"]);
//    auto dataSumary         = (jsonObject["sumary"]);
//    auto dataForms          = (jsonObject["form"]);
//    auto dataFormHeader     = (jsonObject["formHeader"]);
//    auto dataToolBar        = (jsonObject["toolBar"]);
//    auto dataToolBarButton  = (jsonObject["toolBarButton"]);
//    auto dataDelegateCell   = (jsonObject["delegateCell"]);
//    auto dataDelegateLabel  = (jsonObject["delegateLabel"]);
//    auto dataViewList       = (jsonObject["viewList"]);
//    auto dataViewListHeader = (jsonObject["viewListHeader"]);
//    auto dataViewListCell   = (jsonObject["viewListCell"]);
//    auto dataViewGrid       = (jsonObject["viewGrid"]);
//    auto dataViewGridHeader = (jsonObject["viewGridHeader"]);
//    auto dataViewGridCell   = (jsonObject["viewGridCell"]);


//    dataButtonTool     = (dataButtonTool      .isNull()? dataButtonTool      : dataButton);
//    dataButtonTabBar   = (dataButtonTabBar    .isNull()? dataButtonTabBar    : dataButton);
//    dataButtonToggle   = (dataButtonToggle    .isNull()? dataButtonToggle    : dataButton);
//    dataButtonFlat     = (dataButtonFlat      .isNull()? dataButtonFlat      : dataButton);
//    dataButtonSolid    = (dataButtonSolid     .isNull()? dataButtonSolid     : dataButton);
//    dataDelegateCell   = (dataDelegateCell    .isNull()? dataDelegateCell    : dataRectangle);
//    dataDelegateLabel  = (dataDelegateLabel   .isNull()? dataDelegateLabel   : dataLabel);
//    dataHeader         = (dataHeader          .isNull()? dataHeader          : dataSettingBase);
//    dataSumary         = (dataSumary          .isNull()? dataSumary          : dataSettingBase);
//    dataFormHeader     = (dataFormHeader      .isNull()? dataFormHeader      : dataHeader);
//    dataViewGrid       = (dataViewGrid        .isNull()? dataViewGrid        : dataForms);
//    dataViewGridHeader = (dataViewGridHeader  .isNull()? dataViewGridHeader  : dataFormHeader);
//    dataViewGridCell   = (dataViewGridCell    .isNull()? dataViewGridCell    : dataLabel);
//    dataViewList       = (dataViewList        .isNull()? dataViewList        : dataForms);
//    dataViewListHeader = (dataViewListHeader  .isNull()? dataViewListHeader  : dataViewGridHeader);
//    dataViewListCell   = (dataViewListCell    .isNull()? dataViewListCell    : dataLabel);
//    dataToolBar        = (dataToolBar         .isNull()? dataToolBar         : dataForms);
//    dataToolBarButton  = (dataToolBarButton   .isNull()? dataToolBarButton   : dataButtonFlat);

//    pvtsettingBase.readValues(dataSettingBase);
//    pvtbutton.readValues(dataButton);
//    pvtbuttonTool.readValues(dataButtonTool);
//    pvtbuttonTabBar.readValues(dataButtonTabBar);
//    pvtbuttonToggle.readValues(dataButtonToggle);
//    pvtbuttonFlat.readValues(dataButtonFlat);
//    pvtbuttonSolid.readValues(dataButtonSolid);
//    pvtlineEdit.readValues(dataLineEdit);
//    pvtlabel.readValues(dataLabel);
//    pvtseparator.readValues(dataSeparator);
//    pvtrectangle.readValues(dataRectangle);
//    pvtheader.readValues(dataHeader);
//    pvtsumary.readValues(dataHeader);
//    pvtform.readValues(dataForms);
//    pvtformHeader.readValues(dataFormHeader);
//    pvttoolBar.readValues(dataToolBar);
//    pvttoolBarButton.readValues(dataToolBarButton);
//    pvtdelegateCell.readValues(dataDelegateCell);
//    pvtviewList.readValues(dataViewList);
//    pvtviewListaHeader.readValues(dataViewListHeader);
//    pvtviewListCell.readValues(dataViewListCell);
//    pvtviewGrid.readValues(dataViewGrid);
//    pvtviewGridaHeader.readValues(dataViewGridHeader);
//    pvtviewGridaCell.readValues(dataViewGridCell);

//    this->replaceInvalid(pvtsettingBase);
//}

void MUPaintSetting::replaceInvalid(MUPaintSettingItem &settingBase)
{
    pvtbutton.replaceInvalid(settingBase);
    pvtbuttonTool.replaceInvalid(settingBase);
    pvtbuttonTabBar.replaceInvalid(settingBase);
    pvtbuttonToggle.replaceInvalid(settingBase);
    pvtbuttonFlat.replaceInvalid(settingBase);
    pvtbuttonSolid.replaceInvalid(settingBase);
    pvtlineEdit.replaceInvalid(settingBase);
    pvtlabel.replaceInvalid(settingBase);
    pvtseparator.replaceInvalid(settingBase);
    pvtrectangle.replaceInvalid(settingBase);
    pvtform.replaceInvalid(settingBase);
    pvtformHeader.replaceInvalid(settingBase);
    pvttoolBar.replaceInvalid(settingBase);
    pvttoolBarButton.replaceInvalid(settingBase);
    pvtdelegateCell.replaceInvalid(settingBase);
    pvtviewList.replaceInvalid(settingBase);
    pvtviewListaHeader.replaceInvalid(settingBase);
    pvtviewListCell.replaceInvalid(settingBase);
    pvtviewGrid.replaceInvalid(settingBase);
    pvtviewGridaHeader.replaceInvalid(settingBase);
    pvtviewGridaCell.replaceInvalid(settingBase);
}

QVariant MUPaintSetting::jsonObject()
{
    dPvt();
    return p.jsonObject;

}
