#ifndef AMNEZIA_APPLICATION_H
#define AMNEZIA_APPLICATION_H

#include <QApplication>
#include <QGuiApplication>

#include <QCommandLineParser>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "settings.h"
#include "vpnconnection.h"

#include "configurators/vpn_configurator.h"

#include "ui/controllers/connectionController.h"
#include "ui/controllers/exportController.h"
#include "ui/controllers/importController.h"
#include "ui/controllers/installController.h"
#include "ui/controllers/pageController.h"
#include "ui/controllers/settingsController.h"
#include "ui/controllers/sitesController.h"
#include "ui/models/containers_model.h"
#include "ui/models/languageModel.h"
#include "ui/models/protocols/cloakConfigModel.h"
#include "ui/notificationhandler.h"
#ifdef Q_OS_WINDOWS
    #include "ui/models/protocols/ikev2ConfigModel.h"
#endif
#include "ui/models/protocols/openvpnConfigModel.h"
#include "ui/models/protocols/shadowsocksConfigModel.h"
#include "ui/models/protocols/wireguardConfigModel.h"
#include "ui/models/protocols_model.h"
#include "ui/models/servers_model.h"
#include "ui/models/services/sftpConfigModel.h"
#include "ui/models/sites_model.h"

#define amnApp (static_cast<AmneziaApplication *>(QCoreApplication::instance()))

#if defined(Q_OS_ANDROID) || defined(Q_OS_IOS)
    #define AMNEZIA_BASE_CLASS QApplication
#else
    #define AMNEZIA_BASE_CLASS SingleApplication
    #define QAPPLICATION_CLASS QApplication
    #include "singleapplication.h"
#endif

class AmneziaApplication : public AMNEZIA_BASE_CLASS
{
    Q_OBJECT
public:
#if defined(Q_OS_ANDROID) || defined(Q_OS_IOS)
    AmneziaApplication(int &argc, char *argv[]);
#else
    AmneziaApplication(int &argc, char *argv[], bool allowSecondary = false,
                       SingleApplication::Options options = SingleApplication::User, int timeout = 1000,
                       const QString &userData = {});
#endif
    virtual ~AmneziaApplication();

    void init();
    void registerTypes();
    void loadFonts();
    void loadTranslator();
    void updateTranslator(const QLocale &locale);
    bool parseCommands();

    QQmlApplicationEngine *qmlEngine() const;

signals:
    void translationsUpdated();

private:
    void initModels();
    void initControllers();

    QQmlApplicationEngine *m_engine {};
    std::shared_ptr<Settings> m_settings;
    std::shared_ptr<VpnConfigurator> m_configurator;

    ContainerProps *m_containerProps {};
    ProtocolProps *m_protocolProps {};

    QTranslator *m_translator;
    QCommandLineParser m_parser;

    QSharedPointer<ContainersModel> m_containersModel;
    QSharedPointer<ServersModel> m_serversModel;
    QScopedPointer<LanguageModel> m_languageModel;
    QScopedPointer<ProtocolsModel> m_protocolsModel;
    QSharedPointer<SitesModel> m_sitesModel;

    QScopedPointer<OpenVpnConfigModel> m_openVpnConfigModel;
    QScopedPointer<ShadowSocksConfigModel> m_shadowSocksConfigModel;
    QScopedPointer<CloakConfigModel> m_cloakConfigModel;
    QScopedPointer<WireGuardConfigModel> m_wireguardConfigModel;
#ifdef Q_OS_WINDOWS
    QScopedPointer<Ikev2ConfigModel> m_ikev2ConfigModel;
#endif

    QScopedPointer<SftpConfigModel> m_sftpConfigModel;

    QSharedPointer<VpnConnection> m_vpnConnection;
    QScopedPointer<NotificationHandler> m_notificationHandler;

    QScopedPointer<ConnectionController> m_connectionController;
    QScopedPointer<PageController> m_pageController;
    QScopedPointer<InstallController> m_installController;
    QScopedPointer<ImportController> m_importController;
    QScopedPointer<ExportController> m_exportController;
    QScopedPointer<SettingsController> m_settingsController;
    QScopedPointer<SitesController> m_sitesController;
};

#endif // AMNEZIA_APPLICATION_H
