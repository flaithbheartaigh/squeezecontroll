/*
    Copyright (C) 2010 Michael Rahr

    This file is part of SqueezeRemote.

    SqueezeRemote is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License.

    SqueezeRemote is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with SqueezeRemote.  If not, see <http://www.gnu.org/licenses/>.
*/


#ifndef SQUEEZELISTNER_H
#define SQUEEZELISTNER_H

#include <QObject>
#include <QTcpSocket>
#include <QtDebug>
#include <QMessageBox>
#include <QFile>
#include "database_struct.h"

class squeezeListner : public QObject
{
Q_OBJECT
public:
    squeezeListner(QObject *parent,QString mIpaddr,QString mPortNr);
    ~squeezeListner();
    void subscribeTo(QString subscribe);
    bool connectTo(QString mIpaddr,QString mPortNr);

private:
    void displayError(QAbstractSocket::SocketError socketError);
    QTcpSocket *tcpSocket;
    QString ip_addr;
    QString port_nr;
    bool connected;

private slots:
    void readData1();
    void disConnected();
signals:
    void sendStatus(QString datastring);


};

#endif // SQUEEZELISTNER_H
