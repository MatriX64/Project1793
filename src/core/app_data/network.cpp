#include "network.h"

Network::Network()
{

}

Network::Network(const QString &name, const QString &mac) : m_name(name),
                                                            m_mac(mac)
{

}

QString Network::name() const
{
    return m_name;
}

QString Network::mac() const
{
    return m_mac;
}
