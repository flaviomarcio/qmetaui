#ifndef MUApplication_H
#define MUApplication_H

#include <QGuiApplication>
#include <QObject>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "./mu_global.h"

#define MU_Application(engine)\
    QQmlApplicationEngine e;\
    auto&engine=MUApplication::i().engine(e);\

typedef std::function<void()> MUApplicationMethodInit;

class Q_MU_EXPORT MUApplication : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief MUApplication
     * @param parent
     */
    explicit MUApplication(QObject *parent = nullptr);

    /**
     * @brief MUApplication
     * @param parent
     */
    explicit MUApplication(const MUApplication &parent);

    /**
     * @brief i
     * @return
     */
    static MUApplication&i();

    /**
     * @brief engine
     * @return
     */
    static QQmlApplicationEngine&engine();
    QQmlApplicationEngine&engine(QQmlApplicationEngine&v);

    /**
     * @brief registerInitMethod
     */
    static void initMethodOnLoadEngine(MUApplicationMethodInit method);
signals:
    /**
     * @brief notify
     * @param type
     * @param especification
     * @param payload
     */
    void notify(int type, int especification, const QVariant&payload);
    void engineInit(QQmlApplicationEngine&v);
};


Q_DECLARE_METATYPE(MUApplication)

#endif // MUApplication_H
