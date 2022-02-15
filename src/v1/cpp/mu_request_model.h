#pragma once

#include "./mu_global.h"
#include "./mu_request.h"
#include <QAbstractTableModel>

//!
//! \brief The MURequestModel class
//!
class Q_MU_EXPORT MURequestModel : public MURequest
{
    Q_OBJECT
public:
    Q_PROPERTY(QVariant data READ data WRITE setData NOTIFY dataChanged)
    Q_PROPERTY(QAbstractTableModel*model READ model WRITE setModel NOTIFY modelChanged)
    Q_PROPERTY(int count READ count NOTIFY countChanged)
    Q_PROPERTY(bool isEmpty READ isEmpty NOTIFY isEmptyChanged)

    //!
    //! \brief MURequestModel
    //! \param parent
    //!
    Q_INVOKABLE explicit MURequestModel(QObject *parent = nullptr);
    ~MURequestModel();

    //!
    //! \brief count
    //! \return
    //!
    int count();
    bool isEmpty();

    //!
    //! \brief data
    //! \return
    //!
    virtual QVariant data()const;
    virtual void setData(const QVariant&v);

    //!
    //! \brief clear
    //!
    Q_INVOKABLE virtual void clear();

    //!
    //! \brief append
    //! \param vValue
    //!
    Q_INVOKABLE virtual void append(const QVariant&vValue);

    //!
    //! \brief setRows
    //! \param vRows
    //!
    Q_INVOKABLE virtual void setRows(const QVariant&vRows);

    //!
    //! \brief setJson
    //! \param v
    //! \return
    //!
    Q_INVOKABLE virtual QVariant setJson(const QVariant&v);

    //!
    //! \brief setCBor
    //! \param v
    //! \return
    //!
    Q_INVOKABLE virtual QVariant setCBor(const QVariant&v);

    //!
    //! \brief toList
    //! \return
    //!
    Q_INVOKABLE virtual QVariantList toList();

    //!
    //! \brief toMap
    //! \return
    //!
    Q_INVOKABLE virtual QVariantHash toMap();

    //!
    //! \brief toHash
    //! \return
    //!
    Q_INVOKABLE virtual QVariantHash toHash();

    //!
    //! \brief model
    //! \return
    //!
    QAbstractTableModel *model();
    void setModel(QAbstractTableModel*model);

signals:
    void itemsChanged();
    void dataChanged();
    void modelChanged();
    void countChanged();
    void isEmptyChanged();
private:
    void*p=nullptr;
};
