#ifndef NETWORKLISTMODEL_H
#define NETWORKLISTMODEL_H

#include <QAbstractListModel>
#include <QList>

#include "network.h"

class WPSNetworkListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit WPSNetworkListModel(QObject *parent = 0);

public:
    enum NetworkRoles {
        NetworkName = Qt::UserRole + 1,
        NetworkMac
    };

    void addNetwork(const Network &network);
    void clearList();

    int rowCount(const QModelIndex & parent = QModelIndex()) const;

    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

protected:
    QHash<int, QByteArray> roleNames() const;

private:
    QList<Network> networkList;
};

#endif // NETWORKLISTMODEL_H
