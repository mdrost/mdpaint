#include "cairoplugin.h"

#include "cairobackendfactory.h"

// public
mdpCairoPlugin::mdpCairoPlugin(int& argc, char** const argv)
{
}

// public virtual
mdpCairoPlugin::~mdpCairoPlugin() /* override */
{
}

// public virtual
void mdpCairoPlugin::initialize() /* override */
{
}

// public virtual
void mdpCairoPlugin::terminate() /* override */
{
}

// public virtual
std::unique_ptr<mdpFrontend> mdpCairoPlugin::createFrontend() /* override */
{
    return nullptr;
}

// public virtual
std::unique_ptr<mdpBackendFactory> mdpCairoPlugin::createBackendFactory() /* override */
{
    return std::make_unique<mdpCairoBackendFactory>();
}

std::unique_ptr<mdpPlugin> mdpCreatePlugin(int& argc, char** const argv)
{
    return std::make_unique<mdpCairoPlugin>(argc, argv);
}
