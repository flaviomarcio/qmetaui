#pragma once

#include "./mu_global.h"
#include <QAbstractTableModel>
#include "./mu_request.h"

class Q_MU_EXPORT MURequestModel : public MURequest
{
    Q_OBJECT
public:
    Q_PROPERTY(QVariant data READ data WRITE setData NOTIFY dataChanged)
    Q_PROPERTY(QAbstractTableModel*model READ model WRITE setModel NOTIFY modelChanged)
    Q_PROPERTY(int count READ count NOTIFY countChanged)
    Q_PROPERTY(bool isEmpty READ isEmpty NOTIFY isEmptyChanged)

    Q_INVOKABLE explicit MURequestModel(QObject *parent = nullptr);
    ~MURequestModel();

    /**
     * @brief count
     * @return
     */
    int count();
    bool isEmpty();

    /**
     * @brief data
     * @return
     */
    virtual QVariant data()const;
    virtual void setData(const QVariant&v);

    Q_INVOKABLE virtual void clear();
    Q_INVOKABLE virtual void append(const QVariant&vValue);
    Q_INVOKABLE virtual void setRows(const QVariant&vRows);

    Q_INVOKABLE virtual QVariant setJson(const QVariant&v);
    Q_INVOKABLE virtual QVariant setCBor(const QVariant&v);

    Q_INVOKABLE virtual QVariantList toList();
    Q_INVOKABLE virtual QVariantMap toMap();

    /**
     * @brief model
     * @return
     */
    QAbstractTableModel *model();
    void setModel(QAbstractTableModel*model);

signals:
    void dataChanged();
    void modelChanged();
    void countChanged();
    void isEmptyChanged();
private:
    void*p=nullptr;
};
