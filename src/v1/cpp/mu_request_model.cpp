#include "./mu_request_model.h"
#include "./mu_model_table.h"

#define dPvt()\
    auto&p = *reinterpret_cast<MURequestModelPvt*>(this->p)

class MURequestModelPvt:public QObject{
public:
    QVariant jsonObject;
    MURequestModel*parent=nullptr;
    MUModelTable model;
    explicit MURequestModelPvt(MURequestModel*parent):QObject(parent), model(parent){
        this->parent=parent;
    }
    virtual ~MURequestModelPvt(){
    }
};

MURequestModel::MURequestModel(QObject *parent) : MURequest(parent)
{
    this->p=new MURequestModelPvt(this);

    QObject::connect(this, &MURequestModel::modelChanged, this, &MURequestModel::dataChanged);
    QObject::connect(this, &MURequestModel::modelChanged, this, &MURequestModel::countChanged);
    QObject::connect(this, &MURequestModel::modelChanged, this, &MURequestModel::isEmptyChanged);

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
    else
        return p.model.toList();
}

void MURequestModel::setData(const QVariant &v)
{
    dPvt();
    return p.model.setRows(v);
}

void MURequestModel::clear()
{
    dPvt();
    p.model.clear();
    emit modelChanged();
}

void MURequestModel::append(const QVariant &vValue)
{
    dPvt();
    p.model.append(vValue);
    emit modelChanged();
}

void MURequestModel::setRows(const QVariant &vRows)
{
    dPvt();
    p.model.setRows(vRows);
    emit modelChanged();
}

QVariant MURequestModel::setJson(const QVariant &v)
{
    dPvt();
    auto r=p.model.setJson(v);
    emit modelChanged();
    return r;
}

QVariant MURequestModel::setCBor(const QVariant &v)
{
    dPvt();
    auto r=p.model.setCBor(v);
    emit modelChanged();
    return r;
}

QVariantList MURequestModel::toList()
{
    dPvt();
    auto r=p.model.toList();
    emit modelChanged();
    return r;
}

QVariantMap MURequestModel::toMap()
{
    dPvt();
    auto r=p.model.toMap();
    emit modelChanged();
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
