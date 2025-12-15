#ifndef MDP_CAIRO_API_H
#define MDP_CAIRO_API_H

#include <mdpaint/api.h>

#ifdef MDP_CAIRO_EXPORTS
# define MDP_CAIRO_API MDP_INTERFACE_API_EXPORT
#else
# define MDP_CAIRO_API MDP_INTERFACE_API_IMPORT
#endif

#endif // MDP_CAIRO_API_H
