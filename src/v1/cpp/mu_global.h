#pragma once

#include <QObject>
#include <QTranslator>
#include "./mu_const.h"
#include "./mu_types.h"

#ifndef QT_STATIC
#  if defined(QT_BUILD_SQL_LIB)
#    define Q_MU_EXPORT Q_DECL_EXPORT
#  else
#    define Q_MU_EXPORT Q_DECL_IMPORT
#  endif
#else
#  define Q_MU_EXPORT
#endif
