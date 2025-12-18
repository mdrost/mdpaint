#ifndef MDP_CAIROPLUGIN_H
#define MDP_CAIROPLUGIN_H

#include "cairoapi.h"

#include <mdpaint/plugin.h>

class mdpCairoPlugin : public mdpPlugin
{
public:

    explicit mdpCairoPlugin(int &argc, char **argv);

    ~mdpCairoPlugin() override;

    void initialize() override;

    void terminate() override;

    [[nodiscard]]
    std::unique_ptr<mdpFrontend> createFrontend() override;

    [[nodiscard]]
    std::unique_ptr<mdpBackendFactory> createBackendFactory() override;

private:
    int& m_argc;
    char** m_argv;
};

#if defined(_WIN32)
namespace std
{
extern template class unique_ptr<mdpPlugin>;
}
#endif

extern "C"
[[nodiscard]]
MDP_CAIRO_API
std::unique_ptr<mdpPlugin> mdpCreatePlugin(int& argc, char** argv);

#endif // MDP_CAIROPLUGIN_H
