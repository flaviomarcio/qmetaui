#include "./mu_model_table.h"

//#include "./mu_string_util.h"
#include "./mu_variant_util.h"
#include "./mu_cache_util.h"

#include <QVariantHash>
#include <QStm>

#define dPvt()\
    auto&p = *reinterpret_cast<MUModelTablePvt*>(this->p)

namespace Qt{
    static const int StartRole     = Qt::UserRole+1;
    static const int id            = StartRole + 1;
    static const int Uuid          = StartRole + 2;
    static const int Md5id         = StartRole + 3;
    static const int Revision      = StartRole + 4;
    static const int RowRole       = StartRole + 5;
    static const int ColumnWidth   = StartRole + 6;
    static const int ColumnHeight  = StartRole + 7;
    static const int RowWidthRole  = StartRole + 8;
    static const int RowHeightRole = StartRole + 9;
    static const int ColumnRole    = StartRole +10;
    static const int maxRole       = StartRole +11;
}


class MUModelTablePvt{
public:
    MUVariantUtil&variantUtil=MUVariantUtil::i();
    MUCacheUtil&cacheUtil=MUCacheUtil::i();
    int rowCount=0;
    QHash<QByteArray, QVariant> list;
    QHash<int,QByteArray> roleNames;
    QHash<int,QByteArray> columnNames;
    QHash<int,int> columnRole;
    QVariantHash headerSetting;
    QMap<int,QVariantHash> columnSetting;
    QVariantHash setting;
    QVariantHash rowSetting;
    QMap<QByteArray,int> columnIndex;
    QMap<QByteArray,int> roleIndex;    

    QByteArray makeKey(int col, int row)const
    {
        return QStringLiteral("%1.%2").arg(col).arg(row).toUtf8();
    }

    void clear()
    {
        auto&p=*this;
        p.rowCount=0;
        p.columnRole.clear();
        p.setting.clear();
        p.headerSetting.clear();
        p.columnSetting.clear();
        p.columnNames.clear();
        p.columnIndex.clear();
        p.roleNames.clear();
        p.roleIndex.clear();        
    }

    void initRoles()
    {
        auto&p=*this;
        if(!p.roleNames.isEmpty())
            return;
        p.roleNames.insert(Qt::ForegroundRole   , QByteArrayLiteral("foreground"   ));
        p.roleNames.insert(Qt::BackgroundRole   , QByteArrayLiteral("background"   ));
        p.roleNames.insert(Qt::TextAlignmentRole, QByteArrayLiteral("textAlignment"));
        p.roleNames.insert(Qt::DisplayRole      , QByteArrayLiteral("display"      ));
        p.roleNames.insert(Qt::id               , QByteArrayLiteral("id"           ));
        p.roleNames.insert(Qt::Uuid             , QByteArrayLiteral("uuid"         ));
        p.roleNames.insert(Qt::Md5id            , QByteArrayLiteral("md5id"        ));
        p.roleNames.insert(Qt::Revision         , QByteArrayLiteral("revision"     ));
        p.roleNames.insert(Qt::RowRole          , QByteArrayLiteral("row"          ));
        p.roleNames.insert(Qt::ColumnHeight     , QByteArrayLiteral("columnHeight" ));
        p.roleNames.insert(Qt::ColumnWidth      , QByteArrayLiteral("columnWidth"  ));
        p.roleNames.insert(Qt::RowWidthRole     , QByteArrayLiteral("rowWidth"     ));
        p.roleNames.insert(Qt::RowHeightRole    , QByteArrayLiteral("rowHeight"    ));
        p.roleNames.insert(Qt::ColumnRole       , QByteArrayLiteral("column"       ));

        this->roleIndex.clear();
        QHashIterator<int,QByteArray> i(this->roleNames);
        while (i.hasNext()) {
            i.next();
            this->roleIndex.insert(i.value(), i.key());
        }
    }

    void setHeaderSettings(const QVariant&vSetting)
    {
        auto&p=*this;
        auto map=vSetting.toHash();
        map.insert(QStringLiteral("horizontalAlignment") , variantUtil.toAlignment(map.value(QStringLiteral("horizontalAlignment"))));
        map.insert(QStringLiteral("verticalAlignment") , variantUtil.toAlignment(map.value(QStringLiteral("verticalAlignment"))));
        map.insert(QStringLiteral("type") , variantUtil.toVariantType(map.value(QStringLiteral("type"))));
        p.headerSetting=map;
    }

    void setColumnSettings(const QVariant&vSetting)
    {
        auto&p=*this;        
        auto setting = this->variantUtil.toVar(vSetting);
        if(setting.isValid()){
            QVariantList list;
            switch (qTypeId(setting)){
            case QMetaType_QVariantHash:
            case QMetaType_QVariantMap:
            {
                QHash<int, QVariant> map;
                QHashIterator<QString, QVariant> i(setting.toHash());
                int maxCol=-1;
                while (i.hasNext()) {
                    i.next();
                    map.insert(i.key().toInt(), i.value());
                    if(i.key().toInt()>maxCol)
                        maxCol=i.key().toInt();
                }
                for (int i = 0; i <= maxCol; ++i){
                    auto v=map.value(i);
                    list<<v;
                }
                break;
            }
            case QMetaType_QVariantList:
            case QMetaType_QStringList:
            {
                    QVariantList list=setting.toList();

                    for (int colIndex = 0; colIndex < list.count(); ++colIndex){
                        auto v=list.at(colIndex);
                        QByteArray roleName;
                        QVariantHash map;
                        switch (qTypeId(v)){
                        case QMetaType_QVariantHash:
                        case QMetaType_QVariantMap:
                        {
                            map = v.toHash();

                            if(map.contains(QStringLiteral("role")))
                                roleName=map.value(QStringLiteral("role")).toByteArray().trimmed();
                            else if(map.contains(QStringLiteral("display")))
                                roleName=map.value(QStringLiteral("display")).toByteArray().trimmed();
    #if Q_MU_LOG
                            else
                                mWarning()<<"Invalid property [role] or [display] in : "<<map;
    #endif
                            break;
                        }
                        default:
                            roleName=v.toByteArray().trimmed();
                        }

                        if(!roleName.isEmpty()){
                            int roleIndex=-1;
                            if(p.roleIndex.contains(roleName))
                                roleIndex=p.roleIndex[roleName];
                            roleIndex=(roleIndex>=0)?roleIndex:Qt::maxRole+colIndex;
                            auto map=v.toHash();
                            map.insert(QStringLiteral("horizontalAlignment") , variantUtil.toAlignment(map.value(QStringLiteral("horizontalAlignment"))));
                            map.insert(QStringLiteral("verticalAlignment") , variantUtil.toAlignment(map.value(QStringLiteral("verticalAlignment"))));
                            map.insert(QStringLiteral("type") , variantUtil.toVariantType(map.value(QStringLiteral("type"))));

                            p.columnRole.insert(colIndex, roleIndex);
                            p.roleNames.insert(roleIndex, roleName);
                            p.columnNames.insert(colIndex, roleName);
                            p.columnSetting.insert(colIndex, map);
                            p.columnIndex.insert(roleName,colIndex);
                            p.roleIndex.insert(roleName,roleIndex);

                        }
                    }
                    break;
            }
            default:
                break;
            }
        }

    }

    void setRowSettings(const QVariant&setting)
    {
        auto&p=*this;
        p.headerSetting=setting.toHash();
    }

    QVariant rowRevision(int row)const
    {
        auto key=this->makeKey(Qt::Revision, row);
        return this->list[key];
    }

    QVariantHash rowData(int row)const
    {
        QVariantHash map;
        QHashIterator<int,QByteArray> i(this->roleNames);
        while (i.hasNext()) {
            i.next();
            auto&role=i.key();
            auto&roleName=i.value();
            auto key=this->makeKey(role, row);
            auto&roleValue=this->list[key];
            map.insert(roleName, roleValue);
        }
        return map;
    }

    QVariantList toList()
    {
        QVariantList vList;
        const auto&rowCount=this->rowCount;
        vList.reserve(this->rowCount);
        for (int row = 0; row < rowCount; ++row)
            vList<<this->rowData(row);
        return vList;
    }

    QVariantHash toHash()
    {
        QVariantHash __return;
        for (int row = 0; row < this->rowCount; ++row) {
            __return.insert(QString::number(row), this->rowData(row));
        }
        return __return;
    }

    explicit MUModelTablePvt()
    {
    }
    virtual ~MUModelTablePvt()
    {
    }
};

MUModelTable::MUModelTable(QObject *parent) : QAbstractTableModel(parent)
{
    this->p = new MUModelTablePvt();
}

MUModelTable::~MUModelTable()
{
    dPvt();
    delete&p;
}

QVariant MUModelTable::headerData(int section, Qt::Orientation , int role) const
{
    Q_UNUSED(section)
    dPvt();
    return p.roleNames.value(role);
}

int MUModelTable::count(const QModelIndex &parent) const
{
    return this->rowCount(parent);
}

int MUModelTable::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    dPvt();
    return p.rowCount;
}

int MUModelTable::columnCount(const QModelIndex&parent) const
{
    Q_UNUSED(parent)
    dPvt();
    return p.columnNames.size();
}

QVariant MUModelTable::data(const QModelIndex &index, int role) const
{
    dPvt();
    if(role==Qt::ForegroundRole)
        return this->rowForeground(index.column());
    else if(role==Qt::BackgroundRole)
        return this->rowBackground(index.column());
    else if(role==Qt::TextAlignmentRole)
        return int(this->columnAlignment(index.column()));
    else if(role==Qt::ColumnHeight)
        return this->columnHeight();
    else if(role==Qt::ColumnWidth)
        return this->columnWidth(index.column());
    else if(role==Qt::RowHeightRole)
        return this->rowHeight();
    else if(role==Qt::RowWidthRole)
        return this->rowWidth(index.column());
    else if(role==Qt::ColumnRole)
        return index.column();
    else if(role==Qt::RowRole)
        return index.row();
    else {
        const auto key=p.makeKey(role, index.row());
        auto&v=p.list[key];
        if(v.isValid())
            return v;
        else{
            const auto t=this->columnType(index.column());
            return p.variantUtil.convertVar(v, t);
        }
    }
    return QVariant();
}

QHash<int, QByteArray> MUModelTable::roleNames() const
{
    dPvt();
    if(!p.list.isEmpty()){
        return p.roleNames;
    }
    return QHash<int, QByteArray>();
}

QHash<int, QByteArray> MUModelTable::columnNames() const
{
    dPvt();
    return p.columnNames;
}

bool MUModelTable::saveFile(const QString &fileName) const
{
    dPvt();
    return p.cacheUtil.saveJsonFile(fileName, p.toList());
}

bool MUModelTable::loadFile(const QString &fileName)
{
    dPvt();
    if(p.cacheUtil.fileExists(fileName)){
        this->append(p.cacheUtil.loadJsonFile(fileName));
        return true;
    }
    return false;
}

QVariant MUModelTable::rowData(const int row)const
{
    dPvt();
    return p.rowData(row);
}

QVariant MUModelTable::rowRevision(const int row) const
{
    dPvt();
    return p.rowRevision(row);
}

QVariant MUModelTable::rowRevisionLast() const
{
    return this->rowRevision(this->rowCount()-1);
}

QVariant MUModelTable::columnHeight() const
{
    dPvt();
    return p.headerSetting.value(QStringLiteral("column.height"));
}

QVariant MUModelTable::columnWidth(int column) const
{
    dPvt();
    auto map=p.columnSetting.value(column);
    auto v=map.value(QStringLiteral("width"));
    if(!v.isValid())
        v=p.headerSetting.value(QStringLiteral("column.width"));
    return v;
}

int MUModelTable::columnType(int column) const
{
    dPvt();
    auto map=p.columnSetting.value(column);
    auto v=QMetaType::UnknownType;
    if(map.contains(QStringLiteral("type"))){
        v=QMetaType::Type(map.value(QStringLiteral("type")).toInt());
        if(p.headerSetting.contains(QStringLiteral("type")))
            v=QMetaType::Type(p.headerSetting.value(QStringLiteral("type")).toInt());
    }
    return v;
}

QColor MUModelTable::columnForeground(int column) const
{
    dPvt();
    auto map=p.columnSetting.value(column);
    auto color=QColor(map.value(QStringLiteral("foreground")).toString());
    return color.isValid()?color:Qt::black;
}

QColor MUModelTable::columnBackground(int column) const
{
    dPvt();
    auto map=p.columnSetting.value(column);
    auto color=QColor(map.value(QStringLiteral("background")).toString());
    return color.isValid()?color:Qt::white;
}

Qt::Alignment MUModelTable::columnAlignment(int column) const
{
    dPvt();
    auto map=p.columnSetting.value(column);
    auto v=map.value(QStringLiteral("alignment"));
    return v.isValid()?Qt::Alignment(v.toInt()):(Qt::AlignHCenter | Qt::AlignLeft);
}

QVariant MUModelTable::rowHeight() const
{
    dPvt();
    return p.rowSetting.value(QStringLiteral("row.height"));
}

QVariant MUModelTable::rowWidth(int column) const
{
    dPvt();
    auto map=p.columnSetting.value(column);
    auto v=map.value(QStringLiteral("width"));
    if(!v.isValid())
        v=p.headerSetting.value(QStringLiteral("row.width"));
    return v;
}

QColor MUModelTable::rowForeground(int column) const
{
    dPvt();
    auto map=p.columnSetting.value(column);
    auto color=QColor(map.value(QStringLiteral("foreground")).toString());
    return color.isValid()?color:Qt::black;
}

QColor MUModelTable::rowBackground(int column) const
{
    dPvt();
    auto map=p.columnSetting.value(column);
    auto color=QColor(map.value(QStringLiteral("background")).toString());
    return color.isValid()?color:Qt::white;
}

Qt::Alignment MUModelTable::rowAlignment(int column) const
{
    dPvt();
    auto map=p.columnSetting.value(column);
    auto v=map.value(QStringLiteral("alignment"));
    return v.isValid()?Qt::Alignment(v.toInt()):(Qt::AlignHCenter | Qt::AlignLeft | Qt::AlignVCenter);
}

bool MUModelTable::isEmpty()
{
    dPvt();
    return p.list.isEmpty();
}

void MUModelTable::clear()
{
    dPvt();
    QModelIndex parent;
    auto rowCount = this->rowCount(parent);
    if ( rowCount == 0 )
        return;

    if ( rowCount == 0 )
        return;

    beginRemoveRows( parent , 0, rowCount-1 );
    p.clear();
    endRemoveRows();
}

void MUModelTable::append(const QVariant &vValue)
{
    dPvt();
    QList<QVariantHash> lst;
    auto v=p.variantUtil.toVar(vValue);
    switch (qTypeId(v)){
    case QMetaType_QVariantHash:
    case QMetaType_QVariantMap:
        lst<<v.toHash();
        break;
    case QMetaType_QVariantList:
    {
        for(auto&v:v.toList()){
            auto m=v.toHash();
            if(!m.isEmpty())
                lst<<m;
        }
        break;
    }
    default:
        break;
    }

    if(!lst.isEmpty()){
        auto map=QVariantHash(lst.first());
        if(p.roleNames.isEmpty()){
            auto v=QVariant(map.keys());
            this->setHeaderSetting(v);
            this->setColumnSetting(v);
            p.initRoles();
        }

        auto __rowStart  = this->rowCount();
        auto __rowFinish = this->rowCount() + ( lst.size()-1 );

        if (__rowFinish < __rowStart)
            return;

        this->beginInsertRows( QModelIndex() , __rowStart, __rowFinish );
        for( auto &map: lst ){
            auto&row = p.rowCount;
            QHashIterator<QString, QVariant> i(map);
            while (i.hasNext()) {
                i.next();
                const auto&roleName=i.key().toUtf8();
                if(p.roleIndex.contains(roleName)){
                    const auto roleIndex=p.roleIndex.value(roleName);
                    const auto key=p.makeKey(roleIndex, row);
                    p.list.insert(key, i.value());
                }
            }
            ++row;
        }
        this->endInsertRows();//finish insert        
    }
}

void MUModelTable::setRows(const QVariant &vRows)
{
    dPvt();
    p.clear();
    auto v=p.variantUtil.toVar(vRows);
    switch (qTypeId(v)){
    case QMetaType_QVariantHash:
    case QMetaType_QVariantMap:
        this->append(v);
        break;
    case QMetaType_QVariantList:
    case QMetaType_QStringList:
    {
        for(auto&i:v.toList()){
            this->append(i);
        }
    }
    default:
        break;
    }
}

QVariant MUModelTable::setJson(const QVariant &v)
{
    dPvt();
    p.clear();
    QVariant data;
    switch (qTypeId(v)){
    case QMetaType_QVariantHash:
    case QMetaType_QVariantMap:
        data=v;
        break;
    case QMetaType_QString:
    case QMetaType_QByteArray:
        data=QJsonDocument::fromJson(v.toByteArray()).toVariant();
        break;
    default:
        break;
    }

    if(data.isValid())
        this->append(data);
    return p.toList();
}

QVariant MUModelTable::setCBor(const QVariant &v)
{
    dPvt();
    p.clear();
    QVariant data;
    switch (qTypeId(v)){
    case QMetaType_QVariantHash:
    case QMetaType_QVariantMap:
        data=v;
        break;
    case QMetaType_QString:
    case QMetaType_QByteArray:
        data=QCborValue::fromCbor(v.toByteArray()).toVariant();
        break;
    default:
        break;
    }

    if(data.isValid())
        this->append(data);
    return p.toList();
}

QVariantList MUModelTable::toList()
{
    dPvt();
    return p.toList();
}

QVariantMap MUModelTable::toMap()
{
    dPvt();
    return QVariant(p.toHash()).toMap();
}

QVariantHash MUModelTable::toHash()
{
    dPvt();
    return p.toHash();
}

QVariantHash MUModelTable::columnSetting() const
{
    dPvt();
    QVariantHash list;
    QMapIterator<int, QVariantHash> i(p.columnSetting);
    while (i.hasNext()) {
        i.next();
        auto map=i.value();
        map.insert(QStringLiteral("column"),i.key());
        list.insert(QString::number(i.key()), map);
    }
    return list;
}

QVariantHash MUModelTable::rowSetting() const
{
    dPvt();
    QVariantHash list;
    QHashIterator<QString, QVariant> i(p.rowSetting);
    while (i.hasNext()) {
        i.next();
        auto map=i.value().toHash();
        map.insert(QStringLiteral("column"),i.key());
        list.insert(i.key(), map);
    }
    return list;
}

QVariantHash MUModelTable::setting()
{
    dPvt();
    return p.setting;
}

void MUModelTable::setSetting(const QVariant &vSetting)
{
    dPvt();
    p.clear();
    p.setting = p.variantUtil.toVar(vSetting).toHash();
    p.setHeaderSettings(p.setting[QStringLiteral("header")]);
    p.setColumnSettings(p.setting[QStringLiteral("columns")]);
    p.setRowSettings(p.setting[QStringLiteral("rows")]);
}

void MUModelTable::setHeaderSetting(const QVariant &setting)
{
    dPvt();
    p.setHeaderSettings(setting);
}

void MUModelTable::setColumnSetting(const QVariant &setting)
{
    dPvt();
    p.setColumnSettings(setting);
}

void MUModelTable::setRowSetting(const QVariant &setting)
{
    dPvt();
    p.setRowSettings(setting);
}

QVariantHash MUModelTable::headerSetting() const
{
    dPvt();
    return p.headerSetting;
}
