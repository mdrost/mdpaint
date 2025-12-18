#ifndef MDP_VIPSPLUGIN_H
#define MDP_VIPSPLUGIN_H

#include "vipsapi.h"

#include <mdpaint/plugin.h>

class mdpVipsPlugin : public mdpPlugin
{
public:

    explicit mdpVipsPlugin(int &argc, char **argv);

    ~mdpVipsPlugin() override;

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
MDP_VIPS_API
std::unique_ptr<mdpPlugin> mdpCreatePlugin(int& argc, char** argv);

#endif // MDP_VIPSPLUGIN_H
