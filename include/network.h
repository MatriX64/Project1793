#ifndef NETWORK_H
#define NETWORK_H

#include <QObject>
#include <QString>

class Network
{
public:
    Network();
    Network(const QString &name);

    QString name() const;

private:
    QString m_name;
};

Q_DECLARE_METATYPE(Network)

#endif // NETWORK_H
