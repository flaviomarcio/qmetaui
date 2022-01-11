#ifndef MU_CONST_H
#define MU_CONST_H

#include <QDebug>

#define Q_MU_LOG false
#define Q_MU_LOG_VERBOSE false
#define Q_MU_LOG_SUPER_VERBOSE false

#define Q_RPC_LOOP_TIMEOUT(mSecs)\
auto&___##mSecs=mSecs;\
auto ___m_msecs_max_time##mSecs = QDateTime::currentDateTime().addMSecs(___##mSecs);\
while(QDateTime::currentDateTime()<___m_msecs_max_time##mSecs)

#define Q_ORM_LOOP_LIMIT(limit)\
for (int loop = 0; loop < limit; ++loop)

#define Q_CONST_V\
    const QVariant&v=QVariant()

#define mDebug()\
    qDebug()<<QString(__PRETTY_FUNCTION__).replace("virtual","").split("(").first().trimmed()<<":"

#define mCritical()\
    qCritical()<<QString(__PRETTY_FUNCTION__).replace("virtual","").split("(").first().trimmed()<<":"

#define mInfo()\
    qInfo()<<QString(__PRETTY_FUNCTION__).replace("virtual","").split("(").first().trimmed()<<":"

#define mWarning()\
    qWarning()<<QString(__PRETTY_FUNCTION__).replace("virtual","").split("(").first().trimmed()<<":"

#define orm_vl\
    QVariantList()

#define orm_sl\
    QStringList()

#endif // MU_CONST_H
