#ifndef NETWORK_H
#define NETWORK_H

#include <QObject>
#include <QString>

class Network
{
public:
    Network();
    Network(const QString &name, const QString &mac);

    QString name() const;
    QString mac() const;

private:
    QString m_name;
    QString m_mac;
};

Q_DECLARE_METATYPE(Network)

#endif // NETWORK_H
