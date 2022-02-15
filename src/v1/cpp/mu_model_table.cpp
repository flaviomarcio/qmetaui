#include "./mu_model_table.h"

//#include "./mu_string_util.h"
#include "./mu_variant_util.h"
#include "./mu_cache_util.h"

#include <QVariantHash>

#define dPvt()\
    auto&p = *reinterpret_cast<MUModelTablePvt*>(this->p)

namespace Qt{
    static const int StartRole = Qt::UserRole+1;
    static const int id = StartRole + 1;
    static const int Uuid = StartRole + 2;
    static const int Md5id = StartRole + 3;
    static const int Revision = StartRole + 4;
    static const int RowRole = StartRole + 5;
    static const int ColumnWidth = StartRole + 6;
    static const int ColumnHeight = StartRole + 7;
    static const int RowWidthRole = StartRole + 8;
    static const int RowHeightRole = StartRole + 9;
    static const int ColumnRole = StartRole +10;
    static const int maxRole = StartRole +11;
}


class MUModelTablePvt{
public:
    QMutex mutexLock;
    MUVariantUtil&vu=MUVariantUtil::i();
    MUCacheUtil&cu=MUCacheUtil::i();
    int rowCount=0;
    QHash<QByteArray, QVariant> list;
    QHash<int,QByteArray> roleNames;
    QHash<int,QByteArray> columnNames;
    QHash<int,int> columnRole;
    QVariantHash headerSetting;
    QHash<int,QVariantHash> columnSetting;
    QVariantHash setting;
    QVariantHash rowSetting;
    QMap<QByteArray,int> columnIndex;
    QMap<QByteArray,int> roleIndex;    

    QByteArray makeKey(int col, int row)const
    {
        return qsl("%1.%2").arg(col).arg(row).toUtf8();
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

        QMutexLocker locker(&p.mutexLock);

        if(!p.roleNames.isEmpty())
            return;

        p.roleNames.insert(Qt::ForegroundRole, qbl("foreground"));
        p.roleNames.insert(Qt::BackgroundRole, qbl("background"));
        p.roleNames.insert(Qt::TextAlignmentRole, qbl("textAlignment"));
        p.roleNames.insert(Qt::DisplayRole, qbl("display"));
        p.roleNames.insert(Qt::id, qbl("id"));
        p.roleNames.insert(Qt::Uuid, qbl("uuid"));
        p.roleNames.insert(Qt::Md5id, qbl("md5id"));
        p.roleNames.insert(Qt::Revision, qbl("revision"));
        p.roleNames.insert(Qt::RowRole, qbl("row"));
        p.roleNames.insert(Qt::ColumnHeight, qbl("columnHeight"));
        p.roleNames.insert(Qt::ColumnWidth, qbl("columnWidth"));
        p.roleNames.insert(Qt::RowWidthRole, qbl("rowWidth"));
        p.roleNames.insert(Qt::RowHeightRole, qbl("rowHeight"));
        p.roleNames.insert(Qt::ColumnRole, qbl("column"));

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
        auto vHash=vSetting.toHash();
        vHash.insert(qsl("horizontalAlignment"), vu.toAlignment(vHash.value(qsl("horizontalAlignment"))));
        vHash.insert(qsl("verticalAlignment"), vu.toAlignment(vHash.value(qsl("verticalAlignment"))));
        vHash.insert(qsl("type"), vu.toVariantType(vHash.value(qsl("type"))));
        p.headerSetting=vHash;
    }

    void setColumnSettings(const QVariant&vSetting)
    {
        auto&p=*this;        
        auto setting = this->vu.toVar(vSetting);

        if(!setting.isValid())
            return;

        QVariantList list;
        switch (qTypeId(setting)) {
        case QMetaType_QVariantHash:
        case QMetaType_QVariantMap:
        {
            QMap<int, QVariant> map;
            QMapIterator<QString, QVariant> i(setting.toMap());
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
            list=setting.toList();
            break;
        default:
            break;
        }
        for (int colIndex = 0; colIndex < list.count(); ++colIndex){
            auto v=list.at(colIndex);
            switch (qTypeId(v)) {
            case QMetaType_QVariantHash:
            case QMetaType_QVariantMap:
            {
                QByteArray roleName;
                auto vHash = v.toHash();
                if(vHash.contains(qsl("role")))
                    roleName=vHash.value(qsl("role")).toByteArray().trimmed();
                else if(vHash.contains(qsl("display")))
                    roleName=vHash.value(qsl("display")).toByteArray().trimmed();
#if Q_MU_LOG
                else
                    mWarning()<<"Invalid property [role] or [display] in : "<<map;
#endif
                else
                    roleName=v.toByteArray().trimmed();

                if(!roleName.isEmpty()){
                    int roleIndex=-1;
                    if(p.roleIndex.contains(roleName))
                        roleIndex=p.roleIndex[roleName];
                    roleIndex=(roleIndex>=0)?roleIndex:Qt::maxRole+colIndex;
                    auto vHash=v.toHash();
                    vHash.insert(qsl("horizontalAlignment"), vu.toAlignment(vHash.value(qsl("horizontalAlignment"))));
                    vHash.insert(qsl("verticalAlignment"), vu.toAlignment(vHash.value(qsl("verticalAlignment"))));
                    vHash.insert(qsl("type"), vu.toVariantType(vHash.value(qsl("type"))));

                    p.columnRole.insert(colIndex, roleIndex);
                    p.roleNames.insert(roleIndex, roleName);
                    p.columnNames.insert(colIndex, roleName);
                    p.columnSetting.insert(colIndex, vHash);
                    p.columnIndex.insert(roleName,colIndex);
                    p.roleIndex.insert(roleName,roleIndex);

                }
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
        QVariantHash vHash;
        QHashIterator<int,QByteArray> i(this->roleNames);
        while (i.hasNext()) {
            i.next();
            auto&role=i.key();
            auto&roleName=i.value();
            auto key=this->makeKey(role, row);
            auto&roleValue=this->list[key];
            vHash.insert(roleName, roleValue);
        }
        return vHash;
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

MUModelTable::MUModelTable(const MUModelTable &parent) : QAbstractTableModel(nullptr)
{
    Q_UNUSED(parent)
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
    switch (role) {
    case Qt::ForegroundRole:
        return this->rowForeground(index.column());
    case Qt::BackgroundRole:
        return this->rowBackground(index.column());
    case Qt::TextAlignmentRole:
        return int(this->columnAlignment(index.column()));
    case Qt::ColumnHeight:
        return this->columnHeight();
    case Qt::ColumnWidth:
        return this->columnWidth(index.column());
    case Qt::RowHeightRole:
        return this->rowHeight();
    case Qt::RowWidthRole:
        return this->rowWidth(index.column());
    case Qt::ColumnRole:
        return index.column();
    case Qt::RowRole:
        return index.row();
    default:
        const auto key=p.makeKey(role, index.row());
        auto&v=p.list[key];
        if(v.isValid())
            return v;
        const auto t=this->columnType(index.column());
        return p.vu.convertVar(v, t);
    }
    return {};
}

QHash<int, QByteArray> MUModelTable::roleNames() const
{
    dPvt();
    if(!p.list.isEmpty())
        return p.roleNames;
    return {};
}

QHash<int, QByteArray> MUModelTable::columnNames() const
{
    dPvt();
    return p.columnNames;
}

bool MUModelTable::saveFile(const QString &fileName) const
{
    dPvt();
    return p.cu.saveJsonFile(fileName, p.toList());
}

bool MUModelTable::loadFile(const QString &fileName)
{
    dPvt();
    if(!p.cu.fileExists(fileName))
        return false;
    this->append(p.cu.loadJsonFile(fileName));
    return true;
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
    return p.headerSetting.value(qsl("column.height"));
}

QVariant MUModelTable::columnWidth(int column) const
{
    dPvt();
    auto map=p.columnSetting.value(column);
    auto v=map.value(qsl("width"));
    if(!v.isValid())
        v=p.headerSetting.value(qsl("column.width"));
    return v;
}

QVariant::Type MUModelTable::columnType(int column) const
{
    dPvt();
    auto vHash=p.columnSetting.value(column);
    auto v=QVariant::Invalid;
    if(vHash.contains(qsl("type"))){
        v=QVariant::Type(vHash.value(qsl("type")).toInt());
        if(p.headerSetting.contains(qsl("type")))
            v=QVariant::Type(p.headerSetting.value(qsl("type")).toInt());
    }
    return v;
}

QColor MUModelTable::columnForeground(int column) const
{
    dPvt();
    auto map=p.columnSetting.value(column);
    auto color=QColor(map.value(qsl("foreground")).toString());
    return color.isValid()?color:Qt::black;
}

QColor MUModelTable::columnBackground(int column) const
{
    dPvt();
    auto map=p.columnSetting.value(column);
    auto color=QColor(map.value(qsl("background")).toString());
    return color.isValid()?color:Qt::white;
}

Qt::Alignment MUModelTable::columnAlignment(int column) const
{
    dPvt();
    auto map=p.columnSetting.value(column);
    auto v=map.value(qsl("alignment"));
    return v.isValid()?Qt::Alignment(v.toInt()):(Qt::AlignHCenter | Qt::AlignLeft);
}

QVariant MUModelTable::rowHeight() const
{
    dPvt();
    return p.rowSetting.value(qsl("row.height"));
}

QVariant MUModelTable::rowWidth(int column) const
{
    dPvt();
    auto map=p.columnSetting.value(column);
    auto v=map.value(qsl("width"));
    if(!v.isValid())
        v=p.headerSetting.value(qsl("row.width"));
    return v;
}

QColor MUModelTable::rowForeground(int column) const
{
    dPvt();
    auto map=p.columnSetting.value(column);
    auto color=QColor(map.value(qsl("foreground")).toString());
    return color.isValid()?color:Qt::black;
}

QColor MUModelTable::rowBackground(int column) const
{
    dPvt();
    auto map=p.columnSetting.value(column);
    auto color=QColor(map.value(qsl("background")).toString());
    return color.isValid()?color:Qt::white;
}

Qt::Alignment MUModelTable::rowAlignment(int column) const
{
    dPvt();
    auto map=p.columnSetting.value(column);
    auto v=map.value(qsl("alignment"));
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

    beginRemoveRows( parent , 0, rowCount-1 );
    p.clear();
    endRemoveRows();
}

void MUModelTable::append(const QVariant &vValue)
{
    dPvt();
    QList<QVariantHash> lst;
    auto v=p.vu.toVar(vValue);
    switch (qTypeId(v)) {
    case QMetaType_QVariantHash:
    case QMetaType_QVariantMap:
        lst<<v.toHash();
        break;
    case QMetaType_QVariantList:
    case QMetaType_QStringList:
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

    if(lst.isEmpty())
        return;

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
            if(!p.roleIndex.contains(roleName))
                continue;

            const auto roleIndex=p.roleIndex.value(roleName);
            const auto key=p.makeKey(roleIndex, row);
            p.list.insert(key, i.value());
        }
        ++row;
    }
    this->endInsertRows();//finish insert
}

void MUModelTable::setRows(const QVariant &vRows)
{
    dPvt();
    p.clear();
    auto v=p.vu.toVar(vRows);
    switch (qTypeId(v)) {
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
        break;
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
    switch (qTypeId(v)) {
    case QMetaType_QVariantList:
    case QMetaType_QStringList:
        data=v;
        break;
    default:
        data=QJsonDocument::fromJson(v.toByteArray()).toVariant();
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
    switch (qTypeId(v)) {
    case QMetaType_QVariantHash:
    case QMetaType_QVariantMap:
        data=v;
        break;
    default:
        data=QCborValue::fromCbor(v.toByteArray()).toVariant();
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

QVariantMap MUModelTable::columnSetting() const
{
    dPvt();
    QVariantMap list;
    QHashIterator<int, QVariantHash> i(p.columnSetting);
    while (i.hasNext()) {
        i.next();
        auto map=i.value();
        map.insert(qsl("column"),i.key());
        list.insert(QString::number(i.key()), map);
    }
    return list;
}

QVariantMap MUModelTable::rowSetting() const
{
    dPvt();
    QVariantMap list;
    QHashIterator<QString, QVariant> i(p.rowSetting);
    while (i.hasNext()) {
        i.next();
        auto map=i.value().toMap();
        map.insert(qsl("column"),i.key());
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
    p.setting = p.vu.toVar(vSetting).toHash();
    p.setHeaderSettings(p.setting[qsl("header")]);
    p.setColumnSettings(p.setting[qsl("columns")]);
    p.setRowSettings(p.setting[qsl("rows")]);
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
