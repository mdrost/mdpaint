#ifndef MDP_PRIVATEAPI_H
#define MDP_PRIVATEAPI_H

// XXX: Keep this file in sync with <mdpaint/api.h>.

#if defined(_WIN32)
# define MDP_PRIVATE_API_EXPORT __declspec(dllexport)
# define MDP_PRIVATE_API_IMPORT __declspec(dllimport)
#elif defined(__GNUC__)
# define MDP_PRIVATE_API_EXPORT __attribute__((__visibility__("default")))
# define MDP_PRIVATE_API_IMPORT
#else
# define MDP_PRIVATE_API_EXPORT
# define MDP_PRIVATE_API_IMPORT
#endif

#ifdef MDP_PRIVATE_BUILD_SHARED
# ifdef MDP_PRIVATE_EXPORTS
#  define MDP_PRIVATE_API MDP_PRIVATE_API_EXPORT
# else
#  define MDP_PRIVATE_API MDP_PRIVATE_API_IMPORT
# endif
#else
# define MDP_PRIVATE_API
#endif

#endif // MDP_PRIVATEAPI_H
