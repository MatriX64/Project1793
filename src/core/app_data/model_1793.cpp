#include "model_1793.h"

Model_1793* Model_1793::model;

QMap<QString,QString> Model_1793::qmlTabView;
QList<QString>         Model_1793::modulesList;

Model_1793::Model_1793(QQmlApplicationEngine *engine, QObject *parent) : QObject(parent)
{
    qRegisterMetaType<Network>();

    model = this;

    engine->rootContext()->setContextProperty("wpsListModel", QVariant::fromValue(&networksList));
    engine->rootContext()->setContextProperty("interfacesListModel", QVariant::fromValue(&interfacesList));
}

Model_1793::~Model_1793()
{
    Logger_1793::write_log_file(LogInfoMsg, "Модель уничтожена");
}

void Model_1793::start()
{
    Logger_1793::write_log_file(LogInfoMsg, "Модель запущена");
}

void Model_1793::add_new_network(const Network &network)
{
    networksList.addNetwork(network);
}

void Model_1793::clear_WPS_networks_list()
{
    networksList.clearList();
}

void Model_1793::add_new_interface(const QString &interface)
{
    interfacesList.addInterface(interface);
}

void Model_1793::clear_interfaces_list()
{
    interfacesList.clearList();
}
