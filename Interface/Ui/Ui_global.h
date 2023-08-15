#ifndef RIBBONUI_GLOBAL_H
#define RIBBONUI_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(UI_LIBRARY)
#  define UI_EXPORT Q_DECL_EXPORT
#else
#  define UI_EXPORT Q_DECL_IMPORT
#endif

#endif // RIBBONUI_GLOBAL_H
