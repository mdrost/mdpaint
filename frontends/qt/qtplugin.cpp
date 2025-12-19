#include "qtplugin.h"

#include "qtbackendfactory.h"
#include "qtfrontend.h"

// public
mdpQtPlugin::mdpQtPlugin(int& argc, char** const argv) :
    m_argc(argc),
    m_argv(argv)
{
}

// public virtual
mdpQtPlugin::~mdpQtPlugin() /* override */
{
}

// public virtual
void mdpQtPlugin::initialize() /* override */
{
    m_application = std::make_unique<QApplication>(m_argc, m_argv);
    //QTranslator translator;
    //const QStringList uiLanguages = QLocale::system().uiLanguages();
    //for (const QString &locale : uiLanguages) {
    //    const QString baseName = QStringLiteral("mdpaint_") + QLocale(locale).name();
    //    if (translator.load(QStringLiteral(":/i18n/") + baseName)) {
    //        app.installTranslator(&translator);
    //        break;
    //    }
    //}
}

// public virtual
void mdpQtPlugin::terminate() /* override */
{
    m_application.reset();
}

// public virtual
std::unique_ptr<mdpFrontend> mdpQtPlugin::createFrontend() /* override */
{
    return std::make_unique<mdpQtFrontend>();
}

// public virtual
std::unique_ptr<mdpBackendFactory> mdpQtPlugin::createBackendFactory() /* override */
{
    return std::make_unique<mdpQtBackendFactory>();
}

std::unique_ptr<mdpPlugin> mdpCreatePlugin(int& argc, char** const argv)
{
    return std::make_unique<mdpQtPlugin>(argc, argv);
}
