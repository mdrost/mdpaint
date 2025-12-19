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
#endif

#include <mdpaint/plugin.h>

#define BOOST_DLL_USE_STD_FS
#include <boost/dll/runtime_symbol_info.hpp>
#include <boost/dll/shared_library.hpp>
#include <boost/json.hpp>

#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <ranges>
#include <string>
#include <vector>

#if defined(_WIN32)
int WINAPI wWinMain(const HINSTANCE hInstance, const HINSTANCE hPrevInstance, const PWSTR pCmdLine, const int nCmdShow)
#elif defined(__linux__)
int main(int argc, char* argv[])
#endif
{
#if defined(_WIN32)
    int& argc = __argc;
    char** argv = __argv;
#endif

    boost::dll::shared_library frontendLibrary;
    std::unique_ptr<mdpPlugin> frontendPlugin;
    std::unique_ptr<mdpFrontend> frontend;
    std::unique_ptr<mdpBackendFactory> frontendBackendFactory;
    std::vector<boost::dll::shared_library> backendLibraries;
    std::vector<std::unique_ptr<mdpPlugin>> backendPlugins;
    std::vector<std::unique_ptr<mdpBackendFactory>> backendBackendFactories;
    std::vector<const mdpBackendFactory*> backendFactories;
    {
        const std::filesystem::path pluginsDir = boost::dll::program_location().remove_filename();
        {
            std::vector<boost::json::value> pluginJsons;
            const std::filesystem::path frontendsDir = pluginsDir / "frontends";
            for (const std::filesystem::directory_entry& dirEntry : std::filesystem::directory_iterator(frontendsDir)) {
                const std::filesystem::path filePath = dirEntry.path();
                const std::string fileName = filePath.filename().string();
                if (!fileName.starts_with("mdpaint") || !fileName.ends_with(".json")) {
                    continue;
                }
                std::ifstream pluginFile(filePath);
                if (!pluginFile) {
                    // TODO
                    continue;
                }
                std::string pluginStr((std::istreambuf_iterator<char>(pluginFile)), std::istreambuf_iterator<char>());
                boost::system::error_code ec;
                boost::json::value pluginJson = boost::json::parse(pluginStr, ec);
                if (ec) {
                    continue;
                }
                pluginJsons.push_back(pluginJson);
            }

            // TODO: sort pluginJsons here

            std::exception_ptr exception;
            for (boost::json::value& pluginJson : pluginJsons) {
                bool throw_to_exit = false;
                try {
                    const boost::json::object* pluginJsonObject;
                    if (boost::system::result<const boost::json::object&> result = pluginJson.try_as_object()) {
                        pluginJsonObject = &*result;
                    }
                    else {
                        continue;
                    }
                    const boost::json::value* pluginJsonPath;
                    if (boost::system::result<const boost::json::value&> result = pluginJsonObject->try_at("path")) {
                        pluginJsonPath = &*result;
                    }
                    else {
                        continue;
                    }
                    std::filesystem::path pluginPath;
                    if (boost::system::result<const boost::json::string&> result = pluginJsonPath->try_as_string()) {
                        pluginPath = std::filesystem::path(std::string_view(*result));
                    }
                    else {
                        continue;
                    }
                    if (pluginPath.is_relative()) {
                        pluginPath = frontendsDir / pluginPath;
                    }
                    std::error_code ec;
                    boost::dll::shared_library candidateFrontendLibrary(pluginPath, ec);
                    if (ec) {
                        continue;
                    }
                    mdpCreatePluginFunction createFrontendPlugin = candidateFrontendLibrary.get<std::remove_pointer_t<mdpCreatePluginFunction>>("mdpCreatePlugin");
                    if (createFrontendPlugin == nullptr) {
                        continue;
                    }
                    std::unique_ptr<mdpPlugin> candidateFrontendPlugin = createFrontendPlugin(argc, argv);
                    if (candidateFrontendPlugin == nullptr) {
                        continue;
                    }
                    candidateFrontendPlugin->initialize();
                    try {
                        frontend = candidateFrontendPlugin->createFrontend();
                        try {
                            if (frontend == nullptr) {
                                continue;
                            }
                            frontendPlugin = std::move(candidateFrontendPlugin);
                            frontendLibrary = std::move(candidateFrontendLibrary);
                        }
                        catch (...) {
                            throw_to_exit = true;
                            throw;
                        }
                    }
                    catch (...) {
                        candidateFrontendPlugin->terminate();
                        throw;
                    }
                    break;
                }
                catch (...) {
                    if (throw_to_exit) {
                        throw;
                    }
                    else if (exception == nullptr) {
                        exception = std::current_exception();
                    }
                }
            }
            if (frontend == nullptr) {
                if (exception != nullptr) {
                    std::rethrow_exception(exception);
                }
                return EXIT_FAILURE;
            }
        }
        {
            bool throw_to_exit = false;
            try {
                frontendBackendFactory = frontendPlugin->createBackendFactory();
                try {
                    if (frontendBackendFactory != nullptr) {
                        backendFactories.push_back(frontendBackendFactory.get());
                    }
                }
                catch (...) {
                    throw_to_exit = true;
                    throw;
                }
            }
            catch (...) {
                if (throw_to_exit) {
                    throw;
                }
            }
        }
        {
            std::vector<boost::json::value> pluginJsons;
            const std::filesystem::path backendsDir = pluginsDir / "backends";
            for (const std::filesystem::directory_entry& dirEntry : std::filesystem::directory_iterator(backendsDir)) {
                const std::filesystem::path filePath = dirEntry.path();
                const std::string fileName = filePath.filename().string();
                if (!fileName.starts_with("mdpaint") || !fileName.ends_with(".json")) {
                    continue;
                }
                std::ifstream pluginFile(filePath);
                if (!pluginFile) {
                    // TODO
                    continue;
                }
                std::string pluginStr((std::istreambuf_iterator<char>(pluginFile)), std::istreambuf_iterator<char>());
                boost::system::error_code ec;
                boost::json::value pluginJson = boost::json::parse(pluginStr, ec);
                if (ec) {
                    continue;
                }
                pluginJsons.push_back(pluginJson);
            }

            for (boost::json::value& pluginJson : pluginJsons) {
                bool throw_to_exit = false;
                try {
                    const boost::json::object* pluginJsonObject;
                    if (boost::system::result<const boost::json::object&> result = pluginJson.try_as_object()) {
                        pluginJsonObject = &*result;
                    }
                    else {
                        continue;
                    }
                    const boost::json::value* pluginJsonPath;
                    if (boost::system::result<const boost::json::value&> result = pluginJsonObject->try_at("path")) {
                        pluginJsonPath = &*result;
                    }
                    else {
                        continue;
                    }
                    std::filesystem::path pluginPath;
                    if (boost::system::result<const boost::json::string&> result = pluginJsonPath->try_as_string()) {
                        pluginPath = std::filesystem::path(std::string_view(*result));
                    }
                    else {
                        continue;
                    }
                    if (pluginPath.is_relative()) {
                        pluginPath = backendsDir / pluginPath;
                    }
                    std::error_code ec;
                    boost::dll::shared_library backendLibrary(pluginPath, ec);
                    if (ec) {
                        continue;
                    }
                    mdpCreatePluginFunction createBackendPlugin = backendLibrary.get<std::remove_pointer_t<mdpCreatePluginFunction>>("mdpCreatePlugin");
                    if (createBackendPlugin == nullptr) {
                        continue;
                    }
                    std::unique_ptr<mdpPlugin> backendPlugin = createBackendPlugin(argc, argv);
                    if (backendPlugin == nullptr) {
                        continue;
                    }
                    backendPlugin->initialize();
                    try {
                        std::unique_ptr<mdpBackendFactory> backendFactory = backendPlugin->createBackendFactory();
                        try {
                            if (backendFactory == nullptr) {
                                continue;
                            }
                            backendFactories.push_back(backendFactory.get());
                            backendBackendFactories.push_back(std::move(backendFactory));
                            backendPlugins.push_back(std::move(backendPlugin));
                            backendLibraries.push_back(std::move(backendLibrary));
                        }
                        catch (...) {
                            throw_to_exit = true;
                            throw;
                        }
                    }
                    catch (...) {
                        backendPlugin->terminate();
                        throw;
                    }
                }
                catch (...) {
                    if (throw_to_exit) {
                        throw;
                    }
                }
            }
        }
    }

    int result;
    std::exception_ptr exception;
    try {
        result = frontend->run(backendFactories);
    }
    catch (...) {
        exception = std::current_exception();
    }

    for (auto backend : std::views::reverse(std::views::zip(backendLibraries, backendPlugins, backendBackendFactories))) {
        try {
            boost::dll::shared_library& backendLibrary = std::get<0>(backend);
            std::unique_ptr<mdpPlugin>& backendPlugin = std::get<1>(backend);
            std::unique_ptr<mdpBackendFactory>& backendFactory = std::get<2>(backend);
            backendFactory.reset();
            backendPlugin->terminate();
            backendPlugin.reset();
            backendLibrary.unload();
        }
        catch (...) {
            if (exception == nullptr) {
                exception = std::current_exception();
            }
        }
    }
    try {
        frontendBackendFactory.reset();
        frontend.reset();
        frontendPlugin->terminate();
        frontendPlugin.reset();
        frontendLibrary.unload();
    }
    catch (...) {
        if (exception == nullptr) {
            exception = std::current_exception();
        }
    }
    if (exception != nullptr) {
        std::rethrow_exception(exception);
    }

    return result;
}
