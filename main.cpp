#if defined(_WIN32)
# define WIN32_LEAN_AND_MEAN
# define NOGDICAPMASKS
# define NOVIRTUALKEYCODES
# define NOWINMESSAGES
# define NOWINSTYLES
# define NOSYSMETRICS
# define NOMENUS
# define NOICONS
# define NOKEYSTATES
# define NOSYSCOMMANDS
# define NORASTEROPS
# define NOSHOWWINDOW
# define NOATOM
# define NOCLIPBOARD
# define NOCOLOR
# define NOCTLMGR
# define NODRAWTEXT
# define NOGDI
# define NOKERNEL
# define NOUSER
# define NONLS
# define NOMB
# define NOMEMMGR
# define NOMETAFILE
# define NOMINMAX
# define NOMSG
# define NOOPENFILE
# define NOSCROLL
# define NOSERVICE
# define NOSOUND
# define NOTEXTMETRIC
# define NOWH
# define NOWINOFFSETS
# define NOCOMM
# define NOKANJI
# define NOHELP
# define NOPROFILER
# define NODEFERWINDOWPOS
# define NOMCX
# define NOIME // ?
# define NORESOURCE // ?
# define WIN32_NO_STATUS
# include <Windows.h>
//# undef WIN32_NO_STATUS
//# include <winternl.h>
//# include <ntstatus.h>
#elif defined(__linux__)
#endif

#include <mdpaint/plugin.h>

#include <cstdlib>
#include <string>

#if defined(_WIN32)
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
#elif defined(__linux__)
int main(int argc, char* argv[])
#endif
{
#if defined(_WIN32)
    int argc = __argc;
    char **argv = __argv;
#endif
#if defined(_WIN32)
    std::wstring frontendPluginPath = L"frontends\\mdpaintqt.dll";
    HMODULE frontendPluginModule = LoadLibrary(frontendPluginPath.c_str());
    if (frontendPluginModule == NULL) {
        DWORD lastError = GetLastError();
        return EXIT_FAILURE;
    }
    mdpCreatePluginFunction mdpCreatePlugin = reinterpret_cast<mdpCreatePluginFunction>(GetProcAddress(frontendPluginModule, "mdpCreatePlugin"));
    if (mdpCreatePlugin == nullptr) {
        DWORD lastError = GetLastError();
        return EXIT_FAILURE;
    }
#elif defined(__linux__)
#endif
    std::unique_ptr<mdpPlugin> plugin = mdpCreatePlugin(argc, argv);
    if (plugin == nullptr) {
        return EXIT_FAILURE;
    }
    std::unique_ptr<mdpFrontend> frontend = plugin->createFrontend();
    if (frontend == nullptr) {
        return EXIT_FAILURE;
    }
    plugin->initialize();
    int result = frontend->run();
    plugin->terminate();

    return result;
}
