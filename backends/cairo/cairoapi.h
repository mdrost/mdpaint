#ifndef MDP_CAIROAPI_H
#define MDP_CAIROAPI_H

#include <mdpaint/api.h>

#ifdef MDP_CAIRO_BUILD_MODULE
# ifdef MDP_CAIRO_EXPORTS
#  define MDP_CAIRO_API MDP_INTERFACE_API_EXPORT
# else
#  define MDP_CAIRO_API MDP_INTERFACE_API_IMPORT
# endif
#else
# define MDP_CAIRO_API
#endif

#endif // MDP_CAIROAPI_H
