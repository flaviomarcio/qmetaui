#include "./mu_request_model.h"
#include "./mu_model_table.h"

#define dPvt()\
    auto&p = *reinterpret_cast<MURequestModelPvt*>(this->p)

class MURequestModelPvt:public QObject{
public:
    QVariant jsonObject;
    MURequestModel*parent=nullptr;
    MUModelTable model;
    explicit MURequestModelPvt(MURequestModel*parent): QObject(parent), model(parent)
    {
        this->parent=parent;
    }
    virtual ~MURequestModelPvt()
    {
    }
};

MURequestModel::MURequestModel(QObject *parent) : MURequest(parent)
{
    this->p=new MURequestModelPvt(this);
}

MURequestModel::~MURequestModel()
{
    dPvt();
    delete&p;
}

int MURequestModel::count()
{
    dPvt();
    return p.model.rowCount();
}

bool MURequestModel::isEmpty()
{
    dPvt();
    return p.model.isEmpty();
}

QVariant MURequestModel::data() const
{
    dPvt();
    if(p.model.isEmpty())
        return QVariant();
    return p.model.toList();
}

void MURequestModel::setData(const QVariant &v)
{
    dPvt();
    return p.model.setRows(v);
    emit itemsChanged();
}

void MURequestModel::clear()
{
    dPvt();
    p.model.clear();
    emit itemsChanged();
}

void MURequestModel::append(const QVariant &vValue)
{
    dPvt();
    p.model.append(vValue);
    emit itemsChanged();
}

void MURequestModel::setRows(const QVariant &vRows)
{
    dPvt();
    p.model.setRows(vRows);
    emit itemsChanged();
}

QVariant MURequestModel::setJson(const QVariant &v)
{
    dPvt();
    auto r=p.model.setJson(v);
    emit itemsChanged();
    return r;
}

QVariant MURequestModel::setCBor(const QVariant &v)
{
    dPvt();
    auto r=p.model.setCBor(v);
    emit itemsChanged();
    return r;
}

QVariantList MURequestModel::toList()
{
    dPvt();
    auto r=p.model.toList();
    return r;
}

QVariantHash MURequestModel::toMap()
{
    dPvt();
    auto r=p.model.toHash();
    return r;
}

QVariantHash MURequestModel::toHash()
{
    dPvt();
    auto r=p.model.toHash();
    return r;
}

QAbstractTableModel *MURequestModel::model()
{
    dPvt();
    return&p.model;
}

void MURequestModel::setModel(QAbstractTableModel *model)
{
    Q_UNUSED(model)
}
