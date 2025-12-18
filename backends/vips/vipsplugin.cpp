#include "vipsplugin.h"

#include "vipsbackendfactory.h"

#include <vips/vips.h>

// public
mdpVipsPlugin::mdpVipsPlugin(int& argc, char** const argv) :
    m_argc(argc),
    m_argv(argv)
{
}

// public virtual
mdpVipsPlugin::~mdpVipsPlugin() /* override */
{
}

// public virtual
void mdpVipsPlugin::initialize() /* override */
{
    VIPS_INIT(m_argv[0]);
}

// public virtual
void mdpVipsPlugin::terminate() /* override */
{
    vips_shutdown();
}

// public virtual
std::unique_ptr<mdpFrontend> mdpVipsPlugin::createFrontend() /* override */
{
    return nullptr;
}

// public virtual
std::unique_ptr<mdpBackendFactory> mdpVipsPlugin::createBackendFactory() /* override */
{
    return std::make_unique<mdpVipsBackendFactory>();
}

std::unique_ptr<mdpPlugin> mdpCreatePlugin(int& argc, char** const argv)
{
    return std::make_unique<mdpVipsPlugin>(argc, argv);
}
