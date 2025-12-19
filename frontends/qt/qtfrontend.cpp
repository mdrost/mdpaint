#include "qtfrontend.h"

#include "qtmainwindow.h"

#include <QApplication>

// public
mdpQtFrontend::mdpQtFrontend()
{
}

// public virtual
mdpQtFrontend::~mdpQtFrontend() /* override */
{
}

// public virtual
int mdpQtFrontend::run(const std::vector<const mdpBackendFactory*>& backendFactories) /* override */
{
    mdpQtMainWindow mainWindow(backendFactories);
    mainWindow.setObjectName(QStringLiteral("mainWindow"));
    mainWindow.show();
    int result = qApp->exec();
    return result;
}
