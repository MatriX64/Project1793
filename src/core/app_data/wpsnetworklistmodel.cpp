#include "wpsnetworklistmodel.h"


WPSNetworkListModel::WPSNetworkListModel(QObject *parent) : QAbstractListModel(parent)
{

}

void WPSNetworkListModel::addNetwork(const Network &network)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    networkList << network;
    endInsertRows();
}

void WPSNetworkListModel::clearList()
{
    beginRemoveRows(QModelIndex(), rowCount(), rowCount());
    networkList.clear();
    endRemoveRows();
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
    else if (role == NetworkMac)
        return network.mac();
    return QVariant();
}

QHash<int, QByteArray> WPSNetworkListModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[NetworkName] = "name";
    roles[NetworkMac] = "mac";
    return roles;
}
