#pragma once

#include <qglobal.h>

#if defined(BPMN_LIBRARY)
#  define BPMN_LIBRARY_EXPORT Q_DECL_EXPORT
#else
#  define BPMN_LIBRARY_EXPORT Q_DECL_IMPORT
#endif

