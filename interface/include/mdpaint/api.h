#ifndef MDP_INTERFACEAPI_H
#define MDP_INTERFACEAPI_H

#if defined(_WIN32)
# define MDP_INTERFACE_API_EXPORT __declspec(dllexport)
# define MDP_INTERFACE_API_IMPORT __declspec(dllimport)
#elif defined(__GNUC__)
# define MDP_INTERFACE_API_EXPORT __attribute__((__visibility__("default")))
# define MDP_INTERFACE_API_IMPORT
#else
# define MDP_INTERFACE_API_EXPORT
# define MDP_INTERFACE_API_IMPORT
#endif

#ifdef MDP_INTERFACE_BUILD_SHARED
# ifdef MDP_INTERFACE_EXPORTS
#  define MDP_INTERFACE_API MDP_INTERFACE_API_EXPORT
# else
#  define MDP_INTERFACE_API MDP_INTERFACE_API_IMPORT
# endif
#else
# define MDP_INTERFACE_API
#endif

#endif // MDP_INTERFACEAPI_H
