#include <QApplication>
#include <QFile>
#include <QDebug>
#include <QDBusConnection>

#include "mainwidget.h"

// let startdde know that we've already started.
void RegisterDdeSession()
{
    char *envName = "DDE_SESSION_PROCESS_COOKIE_ID";

    QByteArray cookie = qgetenv(envName);
    qunsetenv(envName);

    if (!cookie.isEmpty()) {
        QDBusInterface iface("com.deepin.SessionManager",
                             "/com/deepin/SessionManager",
                             "com.deepin.SessionManager",
                             QDBusConnection::sessionBus());
        iface.asyncCall("Register", QString(cookie));
    }
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setOrganizationName("deepin");
    a.setApplicationName("dde-dock");
    a.setApplicationDisplayName("Dock");

    if (QDBusConnection::sessionBus().registerService(DBUS_NAME)) {
        QFile file("://Resources/qss/default.qss");
        if (file.open(QFile::ReadOnly)) {
            QString styleSheet = QLatin1String(file.readAll());
            qApp->setStyleSheet(styleSheet);
            file.close();
        } else {
            qWarning() << "[Error:] Open  style file errr!";
        }


        MainWidget w;
        w.show();

        RegisterDdeSession();

        return a.exec();
    } else {
        qWarning() << "dde dock is running...";
        return 0;
    }
}
