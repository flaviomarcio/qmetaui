#pragma once

#include "./mu_global.h"
#include "./mu_object.h"
#include <QVariant>
#include <QDate>
#include <QVariantList>
#include <QVariantMap>

//!
//! \brief The MULoginToken class
//!
class Q_MU_EXPORT MULoginToken : public MUObject{
    Q_OBJECT
public:
     Q_PROPERTY(QDateTime iat READ iat WRITE setIat NOTIFY tokenChanged )
     Q_PROPERTY(QDateTime exp READ exp WRITE setExp NOTIFY payloadChanged )
     Q_PROPERTY(QString md5 READ md5 WRITE setMd5 NOTIFY md5Changed )
     Q_PROPERTY(QByteArray payload READ payload WRITE setPayload NOTIFY expChanged )
     Q_PROPERTY(QByteArray token READ token WRITE setToken NOTIFY iatChanged )

    //!
    //! \brief MULoginToken
    //! \param parent
    //!
    Q_INVOKABLE explicit MULoginToken(QObject *parent = nullptr);
    ~MULoginToken();

    //!
    //! \brief isRecent
    //! \return
    //!
    Q_INVOKABLE bool isRecent();

    //!
    //! \brief operator =
    //! \param v
    //! \return
    //!
    MULoginToken&operator=(const QVariantHash&v);

    //!
    //! \brief clear
    //!
    void clear();

    //!
    //! \brief exp
    //! \return
    //!
    QDateTime exp() const;
    void setExp(const QDateTime &value);

    //!
    //! \brief iat
    //! \return
    //!
    QDateTime iat() const;
    void setIat(const QDateTime &value);

    //!
    //! \brief md5
    //! \return
    //!
    QString md5() const;
    void setMd5(const QString &value);

    //!
    //! \brief payload
    //! \return
    //!
    QByteArray payload() const;
    void setPayload(const QByteArray &value);

    //!
    //! \brief token
    //! \return
    //!
    QByteArray token() const;
    void setToken(const QByteArray &value);
private:
    void*p=nullptr;
signals:
    //!
    //! \brief tokenChanged
    //!
    void tokenChanged();

    //!
    //! \brief payloadChanged
    //!
    void payloadChanged();

    //!
    //! \brief md5Changed
    //!
    void md5Changed();

    //!
    //! \brief expChanged
    //!
    void expChanged();

    //!
    //! \brief iatChanged
    //!
    void iatChanged();
};
