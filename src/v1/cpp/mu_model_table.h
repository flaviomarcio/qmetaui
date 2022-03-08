#pragma once

#include "./mu_global.h"
#include <QObject>
#include <QAbstractTableModel>
#include <QColor>

class Q_MU_EXPORT MUModelTable : public QAbstractTableModel
{
    Q_OBJECT
public:

     Q_INVOKABLE explicit MUModelTable(QObject *parent = nullptr);
     Q_INVOKABLE explicit MUModelTable(const MUModelTable &parent) : QAbstractTableModel(nullptr){
         Q_UNUSED(parent)
     }
     ~MUModelTable();

    Q_INVOKABLE QVariant headerData(int section, Qt::Orientation, int role = Qt::DisplayRole) const override;
    Q_INVOKABLE virtual int count(const QModelIndex &parent = QModelIndex()) const;
    Q_INVOKABLE int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    Q_INVOKABLE int columnCount(const QModelIndex &parent) const override;
    Q_INVOKABLE QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    Q_INVOKABLE virtual QHash<int,QByteArray> roleNames() const override;
    Q_INVOKABLE virtual QHash<int,QByteArray> columnNames() const;

    Q_INVOKABLE virtual bool saveFile(const QString&fileName)const;
    Q_INVOKABLE virtual bool loadFile(const QString&fileName);

    Q_INVOKABLE virtual QVariant rowData(const int row=-1) const;
    Q_INVOKABLE virtual QVariant rowRevision(const int row=-1) const;
    Q_INVOKABLE virtual QVariant rowRevisionLast() const;

    Q_INVOKABLE virtual QVariant columnHeight() const;
    Q_INVOKABLE virtual QVariant columnWidth(int column = 0) const;
    Q_INVOKABLE virtual QVariant::Type columnType(int column = 0) const;

    Q_INVOKABLE virtual QColor columnForeground(int column = 0) const;
    Q_INVOKABLE virtual QColor columnBackground(int column = 0) const;
    Q_INVOKABLE virtual Qt::Alignment columnAlignment(int column = 0) const;

    Q_INVOKABLE virtual QVariant rowHeight() const;
    Q_INVOKABLE virtual QVariant rowWidth(int column = 0) const;

    Q_INVOKABLE virtual QColor rowForeground(int column = 0) const;
    Q_INVOKABLE virtual QColor rowBackground(int column = 0) const;
    Q_INVOKABLE virtual Qt::Alignment rowAlignment(int column = 0) const;

    Q_INVOKABLE virtual bool isEmpty();
    Q_INVOKABLE virtual void clear();
    Q_INVOKABLE virtual void append(const QVariant&vValue);
    Q_INVOKABLE virtual void setRows(const QVariant&vRows);

    Q_INVOKABLE virtual QVariant setJson(const QVariant&v);
    Q_INVOKABLE virtual QVariant setCBor(const QVariant&v);

    Q_INVOKABLE virtual QVariantList toList();
    Q_INVOKABLE virtual QVariantMap toMap();
    Q_INVOKABLE virtual QVariantHash toHash();

    Q_INVOKABLE virtual QVariantHash setting();
    Q_INVOKABLE virtual void setSetting(const QVariant&vSetting);

    Q_INVOKABLE virtual void setHeaderSetting(const QVariant&setting);
    Q_INVOKABLE virtual void setColumnSetting(const QVariant&setting);
    Q_INVOKABLE virtual void setRowSetting(const QVariant&setting);

    Q_INVOKABLE virtual QVariantHash headerSetting()const;
    Q_INVOKABLE virtual QVariantMap columnSetting()const;
    Q_INVOKABLE virtual QVariantMap rowSetting()const;

signals:

private:
    void*p=nullptr;
};
