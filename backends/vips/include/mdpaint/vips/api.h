#ifndef MDP_VIPS_API_H
#define MDP_VIPS_API_H

#include <mdpaint/api.h>

#ifdef MDP_VIPS_BUILD_SHARED
# ifdef MDP_VIPS_EXPORTS
#  define MDP_VIPS_API MDP_INTERFACE_API_EXPORT
# else
#  define MDP_VIPS_API MDP_INTERFACE_API_IMPORT
# endif
#else
# define MDP_VIPS_API
#endif

#endif // MDP_VIPS_API_H
