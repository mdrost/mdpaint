#ifndef MDP_QT_API_H
#define MDP_QT_API_H

#include <mdpaint/api.h>

#ifdef MDP_QT_BUILD_MODULE
# ifdef MDP_QT_EXPORTS
#  define MDP_QT_API MDP_INTERFACE_API_EXPORT
# else
#  define MDP_QT_API MDP_INTERFACE_API_IMPORT
# endif
#else
# define MDP_QT_API
#endif

#endif // MDP_QT_API_H
