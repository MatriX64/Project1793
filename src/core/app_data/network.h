/*
 * Copyright (c) 2016, MatriXSan <matrix3sai@gmail.com>
 *
 *  This file is part of Project1793.
 *
 *  Project1793 is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  Project1793 is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Project1793.  If not, see <http://www.gnu.org/licenses/>.
*/

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
