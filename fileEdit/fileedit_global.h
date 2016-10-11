#ifndef FILEEDIT_GLOBAL_H
#define FILEEDIT_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef FILEEDIT_LIB
# define FILEEDIT_EXPORT Q_DECL_EXPORT
#else
# define FILEEDIT_EXPORT Q_DECL_IMPORT
#endif

#endif // FILEEDIT_GLOBAL_H
