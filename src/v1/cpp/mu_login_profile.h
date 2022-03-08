#pragma once

#include "./mu_global.h"
#include "./mu_object.h"
#include <QDate>
#include <QUuid>

class Q_MU_EXPORT MULoginProfile : public MUObject
{
    Q_OBJECT
public:
    Q_PROPERTY(QUuid        uuid         READ uuid           WRITE set_uuid           NOTIFY uuidChanged            )
    Q_PROPERTY(QString      hsh_account  READ hsh_account    WRITE set_hsh_account    NOTIFY hsh_accountChanged     )
    Q_PROPERTY(QString      name         READ name           WRITE set_name           NOTIFY nameChanged            )
    Q_PROPERTY(QString      document     READ document       WRITE set_document       NOTIFY documentChanged        )
    Q_PROPERTY(QDateTime    dt_birth     READ dt_birth       WRITE set_dt_birth       NOTIFY dt_birthChanged        )
    Q_PROPERTY(QString      email        READ email          WRITE set_email          NOTIFY emailChanged           )
    Q_PROPERTY(QString      phone_number READ phone_number   WRITE set_phone_number   NOTIFY phone_numberChanged    )
    Q_PROPERTY(bool         validated    READ validated      WRITE set_validated      NOTIFY validated_Changed      )

    Q_INVOKABLE explicit MULoginProfile(QObject *parent = nullptr);
    ~MULoginProfile();

public:

    /**
     * @brief uuid
     * @return
     */
    QUuid uuid() const;
    void set_uuid(const QUuid &value);

    /**
     * @brief hsh_account
     * @return
     */
    QString hsh_account() const;
    void set_hsh_account(const QString &value);

    /**
     * @brief name
     * @return
     */
    QString name() const;
    void set_name(const QString &value);

    /**
     * @brief document
     * @return
     */
    QString document() const;
    void set_document(const QString &value);

    /**
     * @brief dt_birth
     * @return
     */
    QDateTime dt_birth() const;
    void set_dt_birth(const QDateTime &value);

    /**
     * @brief email
     * @return
     */
    QString email() const;
    void set_email(const QString &value);

    /**
     * @brief phone_number
     * @return
     */
    QString phone_number() const;
    void set_phone_number(const QString &value);

    /**
     * @brief validated
     * @return
     */
    bool validated() const;
    void set_validated(const bool &value);

    /**
     * @brief loadCurrentSession
     * @param v
     * @return
     */
    Q_INVOKABLE virtual bool loadCurrentSession();

    /**
     * @brief isValid
     * @return
     */
    Q_INVOKABLE virtual bool isValid();

    /**
     * @brief operator =
     * @param v
     * @return
     */
    MULoginProfile&operator=(const MULoginProfile&v);
    MULoginProfile&operator=(const QVariant&v);

    void clear();

private:
    void*p=nullptr;
signals:
    void loaded();
    void uuidChanged();
    void hsh_accountChanged();
    void nameChanged();
    void documentChanged();
    void dt_birthChanged();
    void emailChanged();
    void phone_numberChanged();
    void validated_Changed();

};
