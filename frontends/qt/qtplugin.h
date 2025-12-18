#ifndef MDP_QTPLUGIN_H
#define MDP_QTPLUGIN_H

#include "qtapi.h"

#include <mdpaint/plugin.h>

#include <QApplication>

class mdpQtPlugin : public mdpPlugin
{
public:

    explicit mdpQtPlugin(int &argc, char **argv);

    ~mdpQtPlugin() override;

    void initialize() override;

    void terminate() override;

    [[nodiscard]]
    std::unique_ptr<mdpFrontend> createFrontend() override;

    [[nodiscard]]
    std::unique_ptr<mdpBackendFactory> createBackendFactory() override;

private:
    int& m_argc;
    char** m_argv;
    std::unique_ptr<QApplication> m_application;
};

#if defined(_WIN32)
namespace std
{
extern template class unique_ptr<mdpPlugin>;
}
#endif

extern "C"
[[nodiscard]]
MDP_QT_API
std::unique_ptr<mdpPlugin> mdpCreatePlugin(int& argc, char** argv);

#endif // MDP_QTPLUGIN_H
