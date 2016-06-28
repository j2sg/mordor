#ifndef MORDORCORE_GLOBAL_H
#define MORDORCORE_GLOBAL_H

#include <QtCore/QtGlobal>

#ifdef CORE_LIBRARY
#   define CORE_EXPORT Q_DECL_EXPORT
#else
#   define CORE_EXPORT Q_DECL_IMPORT
#endif

#endif // CORE_GLOBAL_H
