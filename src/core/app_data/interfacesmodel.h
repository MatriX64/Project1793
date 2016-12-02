#ifndef INTERFACESMODEL_H
#define INTERFACESMODEL_H

#include <QAbstractListModel>
#include <QList>

#include <QDebug>

class InterfacesModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit InterfacesModel(QObject *parent = 0);

    enum InterfaceRoles {
        InterfaceName = Qt::UserRole + 1
    };

    void addInterface(const QString& interface);
    void clearList();

    int rowCount(const QModelIndex &parent = QModelIndex()) const;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

protected:
    QHash<int, QByteArray> roleNames() const;

private:
    QList<QString> interfacesList;

signals:

public slots:
};

#endif // INTERFACESMODEL_H
