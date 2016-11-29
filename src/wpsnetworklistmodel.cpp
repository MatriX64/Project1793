#include "include/wpsnetworklistmodel.h"


WPSNetworkListModel::WPSNetworkListModel(QObject *parent) : QAbstractListModel(parent)
{

}

void WPSNetworkListModel::addNetwork(const Network &network)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    networkList << network;
    endInsertRows();
}

int WPSNetworkListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return networkList.count();
}

QVariant WPSNetworkListModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= networkList.count())
        return QVariant();
    const Network &network = networkList[index.row()];
    if (role == NetworkName)
        return network.name();
    return QVariant();
}

QHash<int, QByteArray> WPSNetworkListModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[NetworkName] = "name";
    return roles;
}
