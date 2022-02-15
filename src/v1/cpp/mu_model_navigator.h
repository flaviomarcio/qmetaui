#pragma once

#include <QObject>
#include <QAbstractTableModel>
#include "./mu_server_link.h"

//!
//! \brief The MUModelNavigator class
//!
class Q_MU_EXPORT MUModelNavigator : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int searchRowCount READ searchRowCount WRITE setSearchRowCount NOTIFY searchRowCountChanged)
    Q_PROPERTY(int searchPageCount READ searchPageCount WRITE setSearchPageCount NOTIFY searchPageCountChanged)
    Q_PROPERTY(bool searchActiveNavigator READ searchActiveNavigator WRITE setSearchActiveNavigator NOTIFY searchActiveNavigatorChanged)
    Q_PROPERTY(QString cacheFileName READ cacheFileName WRITE setCacheFileName NOTIFY cacheFileNameChanged)
    Q_PROPERTY(bool cacheAutoLoad READ cacheAutoLoad WRITE setCacheAutoLoad NOTIFY cacheAutoLoadChanged)
    Q_PROPERTY(bool cacheAutoSave READ cacheAutoSave WRITE setCacheAutoSave NOTIFY cacheAutoSaveChanged)
    Q_PROPERTY(QVariant setting READ setting WRITE setSetting NOTIFY settingChanged)
    Q_PROPERTY(QVariant data READ data WRITE setData NOTIFY dataChanged)
    Q_PROPERTY(QAbstractTableModel*model READ model WRITE setModel NOTIFY modelChanged)
    Q_PROPERTY(MUServerLink*link READ link WRITE setLink NOTIFY linkChanged)
    Q_PROPERTY(int count READ count NOTIFY linkChanged)
    Q_PROPERTY(bool isEmpty READ isEmpty NOTIFY linkChanged)

public:
    //!
    //! \brief MUModelNavigator
    //! \param parent
    //!
    Q_INVOKABLE explicit MUModelNavigator(QObject *parent = nullptr);
    ~MUModelNavigator();

    //!
    //! \brief count
    //! \return
    //!
    int count();
    bool isEmpty();

    //!
    //! \brief clear
    //! \return
    //!
    Q_INVOKABLE bool clear();

    //!
    //! \brief search
    //! \param bodyFilter
    //! \return
    //!
    Q_INVOKABLE bool search(const QVariant &bodyFilter);

    //!
    //! \brief reload
    //! \param v
    //! \return
    //!
    Q_INVOKABLE bool reload(const QVariant &v);

    //!
    //! \brief first
    //! \param v
    //! \return
    //!
    Q_INVOKABLE bool first(const QVariant &v=QVariant());

    //!
    //! \brief prior
    //! \param v
    //! \return
    //!
    Q_INVOKABLE bool prior(const QVariant &v=QVariant());

    //!
    //! \brief next
    //! \param v
    //! \return
    //!
    Q_INVOKABLE bool next(const QVariant &v=QVariant());

    //!
    //! \brief last
    //! \param v
    //! \return
    //!
    Q_INVOKABLE bool last(const QVariant &v=QVariant());

    //!
    //! \brief cancel
    //! \return
    //!
    Q_INVOKABLE bool cancel();

    //!
    //! \brief setting
    //! \return
    //!
    virtual QVariant setting()const;
    virtual void setSetting(const QVariant&v);

    //!
    //! \brief data
    //! \return
    //!
    virtual QVariant data()const;
    virtual void setData(const QVariant&v);

    //!
    //! \brief model
    //! \return
    //!
    QAbstractTableModel *model();
    void setModel(QAbstractTableModel*model);

    //!
    //! \brief searchRowCount
    //! \return
    //!
    virtual int searchRowCount() const;
    virtual void setSearchRowCount(int value);

    //!
    //! \brief searchPageCount
    //! \return
    //!
    virtual int searchPageCount() const;
    virtual void setSearchPageCount(int searchPageCount);

    //!
    //! \brief link
    //! \return
    //!
    virtual MUServerLink *link();
    virtual void setLink(MUServerLink *link);

    //!
    //! \brief cacheFileName
    //! \return
    //!
    virtual QString cacheFileName() const;
    virtual void setCacheFileName(const QString &value);

    //!
    //! \brief cacheAutoLoad
    //! \return
    //!
    virtual bool cacheAutoLoad() const;
    virtual void setCacheAutoLoad(bool value);

    //!
    //! \brief cacheAutoSave
    //! \return
    //!
    virtual bool cacheAutoSave() const;
    virtual void setCacheAutoSave(bool value);

    //!
    //! \brief searchActiveNavigator
    //! \return
    //!
    virtual bool searchActiveNavigator() const;
    virtual void setSearchActiveNavigator(bool value);

    //!
    //! \brief loadCache
    //! \return
    //!
    Q_INVOKABLE virtual bool loadCache();

    //!
    //! \brief saveCache
    //! \return
    //!
    Q_INVOKABLE virtual bool saveCache();

signals:
    //!
    //! \brief searchStarted
    //!
    void searchStarted();

    //!
    //! \brief searchResponse
    //! \param responseBody
    //!
    void searchResponse(const QVariant&responseBody);

    //!
    //! \brief searchFinished
    //!
    void searchFinished();

    //!
    //! \brief searchDiscarted
    //!
    void searchDiscarted();

    //!
    //! \brief searchUnauthorized
    //! \param message
    //!
    void searchUnauthorized(const QVariant&message);

    //!
    //! \brief searchFail
    //! \param message
    //!
    void searchFail(const QVariant&message);

    //!
    //! \brief searchError
    //! \param message
    //!
    void searchError(const QVariant&message);


signals:
    //!
    //! \brief searchRowCountChanged
    //!
    void searchRowCountChanged();

    //!
    //! \brief searchPageCountChanged
    //!
    void searchPageCountChanged();

    //!
    //! \brief searchActiveNavigatorChanged
    //!
    void searchActiveNavigatorChanged();

    //!
    //! \brief cacheFileNameChanged
    //!
    void cacheFileNameChanged();

    //!
    //! \brief cacheAutoLoadChanged
    //!
    void cacheAutoLoadChanged();

    //!
    //! \brief cacheAutoSaveChanged
    //!
    void cacheAutoSaveChanged();

    //!
    //! \brief settingChanged
    //!
    void settingChanged();

    //!
    //! \brief dataChanged
    //!
    void dataChanged();

    //!
    //! \brief modelChanged
    //!
    void modelChanged();

    //!
    //! \brief linkChanged
    //!
    void linkChanged();

    //!
    //! \brief countChanged
    //!
    void countChanged();

private:
    void*p=nullptr;
};
