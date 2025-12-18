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
int mdpQtFrontend::run() /* override */
{
    mdpQtMainWindow mainWindow;
    mainWindow.setObjectName(QStringLiteral("mainWindow"));
    mainWindow.show();
    int result = qApp->exec();
    return result;
}
