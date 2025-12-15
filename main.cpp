#include "mainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>


#include <vips/vips.h>

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = QStringLiteral("mdpaint_") + QLocale(locale).name();
        if (translator.load(QStringLiteral(":/i18n/") + baseName)) {
            app.installTranslator(&translator);
            break;
        }
    }

    //InitializeMagick(NULL);
    VIPS_INIT(argv[0]);

    mdpMainWindow mainWindow;
    mainWindow.setObjectName(QStringLiteral("mainWindow"));
    mainWindow.show();
    int result = app.exec();

    vips_shutdown();
    //DestroyMagick();

    return result;
}
