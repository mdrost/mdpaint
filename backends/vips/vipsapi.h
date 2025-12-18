#ifndef MDP_VIPSAPI_H
#define MDP_VIPSAPI_H

#include <mdpaint/api.h>

#ifdef MDP_VIPS_BUILD_MODULE
# ifdef MDP_VIPS_EXPORTS
#  define MDP_VIPS_API MDP_INTERFACE_API_EXPORT
# else
#  define MDP_VIPS_API MDP_INTERFACE_API_IMPORT
# endif
#else
# define MDP_VIPS_API
#endif

#endif // MDP_VIPSAPI_H
