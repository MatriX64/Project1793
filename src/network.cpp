#include "include/network.h"

Network::Network()
{

}

Network::Network(const QString &name) : m_name(name)
{

}

QString Network::name() const
{
    return m_name;
}
