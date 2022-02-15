#include "./private/p_mu_model_navigator.h"

#define dPvt()\
    auto&p = *reinterpret_cast<MUModelNavigatorPvt*>(this->p)

MUModelNavigator::MUModelNavigator(QObject *parent) : QObject(parent)
{
    this->p = new MUModelNavigatorPvt(this);
}

MUModelNavigator::~MUModelNavigator()
{
    dPvt();
    p.deleteLater();
}

int MUModelNavigator::count()
{
    dPvt();
    return p.model.count();
}

bool MUModelNavigator::isEmpty()
{
    dPvt();
    return p.model.isEmpty();
}

bool MUModelNavigator::clear()
{
    dPvt();
    return p.clear();
}

bool MUModelNavigator::search(const QVariant &bodyFilter)
{
    dPvt();
    return p.search(bodyFilter);
}

bool MUModelNavigator::reload(const QVariant&v)
{
    dPvt();
    return p.reload(v);
}

bool MUModelNavigator::first(const QVariant&v)
{
    dPvt();
    return p.first(v);
}

bool MUModelNavigator::prior(const QVariant&v)
{
    dPvt();
    return p.prior(v);
}

bool MUModelNavigator::next(const QVariant&v)
{
    dPvt();
    return p.next(v);
}

bool MUModelNavigator::last(const QVariant&v)
{
    dPvt();
    return p.last(v);
}

bool MUModelNavigator::cancel()
{
    dPvt();
    return p.cancel();
}

QVariant MUModelNavigator::setting() const
{
    dPvt();
    return p.model.setting();
}

void MUModelNavigator::setSetting(const QVariant &v)
{
    dPvt();
    p.model.setSetting(v);
}

QVariant MUModelNavigator::data() const
{
    dPvt();
    if(p.model.isEmpty())
        return QVariant();
    else
        return p.model.toList();
}

void MUModelNavigator::setData(const QVariant &v)
{
    dPvt();
    p.model.setRows(v);
}

QAbstractTableModel*MUModelNavigator::model()
{
    dPvt();
    return&p.model;
}

void MUModelNavigator::setModel(QAbstractTableModel *model)
{
    Q_UNUSED(model)
}

int MUModelNavigator::searchRowCount() const
{
    dPvt();
    return p.searchRowCount;
}

void MUModelNavigator::setSearchRowCount(int value)
{
    dPvt();
    p.searchRowCount=value;
}

int MUModelNavigator::searchPageCount() const
{
    dPvt();
    return p.searchPageCount;
}

void MUModelNavigator::setSearchPageCount(int searchPageCount)
{
    dPvt();
    p.searchPageCount = searchPageCount;
}

MUServerLink*MUModelNavigator::link()
{
    dPvt();
    return&p.link;
}

void MUModelNavigator::setLink(MUServerLink *link)
{
    if (link == nullptr )
        return;

    dPvt();
    p.linkCached=link;
    QObject::connect(p.linkCached, &MUServerLink::destroyed, this, [&p](){
        if(p.linkCached){
            p.linkCached=nullptr;
            mWarning()<<__PRETTY_FUNCTION__<<qsl(": clear linkedCache");
        }
    });
    QObject::connect(p.linkCached, &MUServerLink::headersChanged, this, [&p](){
        if(p.linkCached){
            p.reloadLink();
            emit p.link.headersChanged();
        }
    });
    p.reloadLink();
}

QString MUModelNavigator::cacheFileName() const
{
    dPvt();
    return p.cacheFileName;
}

void MUModelNavigator::setCacheFileName(const QString &value)
{
    dPvt();
    p.cacheFileName = value;
}

bool MUModelNavigator::cacheAutoLoad() const
{
    dPvt();
    return p.cacheAutoLoad;
}

void MUModelNavigator::setCacheAutoLoad(bool value)
{
    dPvt();
    p.cacheAutoLoad = value;
    p.loadCache();
}

bool MUModelNavigator::cacheAutoSave() const
{
    dPvt();
    return p.cacheAutoSave;
}

void MUModelNavigator::setCacheAutoSave(bool value)
{
    dPvt();
    p.cacheAutoSave=value;
}

bool MUModelNavigator::searchActiveNavigator() const
{
    dPvt();
    return p.searchActiveNavigator;
}

void MUModelNavigator::setSearchActiveNavigator(bool value)
{
    dPvt();
    p.searchActiveNavigator = value;
}

bool MUModelNavigator::saveCache()
{
    dPvt();
    return p.saveCache();
}

bool MUModelNavigator::loadCache()
{
    dPvt();
    return p.loadCache();
}
