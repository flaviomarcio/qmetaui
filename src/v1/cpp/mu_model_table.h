#pragma once

#include "./mu_global.h"
#include <QObject>
#include <QAbstractTableModel>
#include <QColor>
#include <QtQml>

class Q_MU_EXPORT MUModelTable : public QAbstractTableModel
{
    QML_ELEMENT
public:
    //!
    //! \brief MUModelTable
    //! \param parent
    //!
    Q_INVOKABLE explicit MUModelTable(QObject *parent = nullptr);

    //!
    //! \brief MUModelTable
    //! \param parent
    //!
    Q_INVOKABLE explicit MUModelTable(const MUModelTable &parent);
    ~MUModelTable();

    //!
    //! \brief headerData
    //! \param section
    //! \param role
    //! \return
    //!
    Q_INVOKABLE QVariant headerData(int section, Qt::Orientation, int role = Qt::DisplayRole) const override;

    //!
    //! \brief count
    //! \param parent
    //! \return
    //!
    Q_INVOKABLE virtual int count(const QModelIndex &parent = QModelIndex()) const;

    //!
    //! \brief rowCount
    //! \param parent
    //! \return
    //!
    Q_INVOKABLE int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    //!
    //! \brief columnCount
    //! \param parent
    //! \return
    //!
    Q_INVOKABLE int columnCount(const QModelIndex &parent) const override;

    //!
    //! \brief data
    //! \param index
    //! \param role
    //! \return
    //!
    Q_INVOKABLE QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    //!
    //! \brief roleNames
    //! \return
    //!
    Q_INVOKABLE virtual QHash<int,QByteArray> roleNames() const override;

    //!
    //! \brief columnNames
    //! \return
    //!
    Q_INVOKABLE virtual QHash<int,QByteArray> columnNames() const;

    //!
    //! \brief saveFile
    //! \param fileName
    //! \return
    //!
    Q_INVOKABLE virtual bool saveFile(const QString&fileName)const;

    //!
    //! \brief loadFile
    //! \param fileName
    //! \return
    //!
    Q_INVOKABLE virtual bool loadFile(const QString&fileName);

    //!
    //! \brief rowData
    //! \param row
    //! \return
    //!
    Q_INVOKABLE virtual QVariant rowData(const int row=-1) const;

    //!
    //! \brief rowRevision
    //! \param row
    //! \return
    //!
    Q_INVOKABLE virtual QVariant rowRevision(const int row=-1) const;
    Q_INVOKABLE virtual QVariant rowRevisionLast() const;

    //!
    //! \brief columnHeight
    //! \return
    //!
    Q_INVOKABLE virtual QVariant columnHeight() const;
    Q_INVOKABLE virtual QVariant columnWidth(int column = 0) const;

    //!
    //! \brief columnType
    //! \param column
    //! \return
    //!
    Q_INVOKABLE virtual QVariant::Type columnType(int column = 0) const;

    //!
    //! \brief columnForeground
    //! \param column
    //! \return
    //!
    Q_INVOKABLE virtual QColor columnForeground(int column = 0) const;
    Q_INVOKABLE virtual QColor columnBackground(int column = 0) const;

    //!
    //! \brief columnAlignment
    //! \param column
    //! \return
    //!
    Q_INVOKABLE virtual Qt::Alignment columnAlignment(int column = 0) const;

    //!
    //! \brief rowHeight
    //! \return
    //!
    Q_INVOKABLE virtual QVariant rowHeight() const;
    Q_INVOKABLE virtual QVariant rowWidth(int column = 0) const;

    //!
    //! \brief rowForeground
    //! \param column
    //! \return
    //!
    Q_INVOKABLE virtual QColor rowForeground(int column = 0) const;
    Q_INVOKABLE virtual QColor rowBackground(int column = 0) const;

    //!
    //! \brief rowAlignment
    //! \param column
    //! \return
    //!
    Q_INVOKABLE virtual Qt::Alignment rowAlignment(int column = 0) const;

    //!
    //! \brief isEmpty
    //! \return
    //!
    Q_INVOKABLE virtual bool isEmpty();

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
    Q_INVOKABLE virtual QVariantMap toMap();

    //!
    //! \brief toHash
    //! \return
    //!
    Q_INVOKABLE virtual QVariantHash toHash();

    //!
    //! \brief setting
    //! \return
    //!
    Q_INVOKABLE virtual QVariantHash setting();
    Q_INVOKABLE virtual void setSetting(const QVariant&vSetting);

    //!
    //! \brief setHeaderSetting
    //! \param setting
    //!
    Q_INVOKABLE virtual void setHeaderSetting(const QVariant&setting);

    //!
    //! \brief setColumnSetting
    //! \param setting
    //!
    Q_INVOKABLE virtual void setColumnSetting(const QVariant&setting);

    //!
    //! \brief setRowSetting
    //! \param setting
    //!
    Q_INVOKABLE virtual void setRowSetting(const QVariant&setting);

    //!
    //! \brief headerSetting
    //! \return
    //!
    Q_INVOKABLE virtual QVariantHash headerSetting()const;

    //!
    //! \brief columnSetting
    //! \return
    //!
    Q_INVOKABLE virtual QVariantMap columnSetting()const;

    //!
    //! \brief rowSetting
    //! \return
    //!
    Q_INVOKABLE virtual QVariantMap rowSetting()const;

signals:

private:
    void*p=nullptr;
};
//Q_DECLARE_METATYPE(MUModelTable             )
