#pragma once

#include <QGuiApplication>
#include <QObject>
#include <QtQml>
#include "./mu_global.h"

#define MU_Application(engine)\
    QQmlApplicationEngine e;\
    auto&engine=MUApplication::i().engine(e);\

//!
//! \brief MUApplicationMethodInit
//!
typedef std::function<void()> MUApplicationMethodInit;

//!
//! \brief The MUApplication class
//!
class Q_MU_EXPORT MUApplication : public QObject
{
    Q_OBJECT
    QML_ELEMENT
public:
    //!
    //! \brief MUApplication
    //! \param parent
    //!
    Q_INVOKABLE explicit MUApplication(QObject *parent = nullptr);

    //!
    //! \brief MUApplication
    //! \param parent
    //!
    explicit MUApplication(const MUApplication &parent);

    //!
    //! \brief i
    //! \return
    //!
    static MUApplication&i();

    //!
    //! \brief engine
    //! \return
    //!
    static QQmlApplicationEngine&engine();
    QQmlApplicationEngine&engine(QQmlApplicationEngine&v);

    //!
    //! \brief initMethodOnLoadEngine
    //! \param method
    //!
    static void initMethodOnLoadEngine(MUApplicationMethodInit method);
signals:
    //!
    //! \brief notify
    //! \param type
    //! \param especification
    //! \param payload
    //!
    void notify(int type, int especification, const QVariant&payload);

    //!
    //! \brief engineInit
    //! \param v
    //!
    void engineInit(QQmlApplicationEngine&v);
};


Q_DECLARE_METATYPE(MUApplication)
