#ifndef GENERATORMANAGERPLUGIN_GLOBAL_H
#define GENERATORMANAGERPLUGIN_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(GENERATORMANAGERPLUGIN_LIBRARY)
#  define GENERATORMANAGERPLUGINSHARED_EXPORT Q_DECL_EXPORT
#else
#  define GENERATORMANAGERPLUGINSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // GENERATORMANAGERPLUGIN_GLOBAL_H
