#include "interfacesmodel.h"

InterfacesModel::InterfacesModel(QObject *parent) : QAbstractListModel(parent)
{

}

void InterfacesModel::addInterface(const QString &interface)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    interfacesList << interface;
    endInsertRows();
}

void InterfacesModel::clearList()
{
    beginResetModel();
    interfacesList.clear();
    endResetModel();
}

int InterfacesModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return interfacesList.count();
}

QVariant InterfacesModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role == InterfaceName)
        return interfacesList.at(index.row());
    return QVariant();
}

QHash<int, QByteArray> InterfacesModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[InterfaceName] = "name";
    return roles;
}
