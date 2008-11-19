/*  XMMS2 - X Music Multiplexer System
 *  Copyright (C) 2003-2008 XMMS2 Team
 *
 *  PLUGINS ARE NOT CONSIDERED TO BE DERIVED WORK !!!
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 */

#include "message.h"
#include "client.h"
#include "result.h"
#include <xmmsc/xmmsc_idnumbers.h>

#include <QIODevice>
#include <QFile>

namespace XMMSQt
{

	Client::Client (QObject *parent, const QString &name)
		: QObject (parent), playlist (this), medialib (this), playback (this),
		  bindata (this), config (this), collection (this)
	{
		m_name = name;
		m_cookie = 0;
		m_readmsg = NULL;
	}

	void
	Client::doConnect (const QString &host, quint32 port)
	{
		m_socket.connectToHost (host, port);
		connect (&m_socket, SIGNAL (connected ()),
		         this, SLOT (socketConnected ()));
		connect (&m_socket, SIGNAL (error (QAbstractSocket::SocketError)),
				 this, SLOT (socketError (QAbstractSocket::SocketError)));
		connect (&m_socket, SIGNAL (readyRead ()), this, SLOT (socketRead ()));
		#ifdef __DEBUG_IPC__
		connect (&m_socket, SIGNAL (bytesWritten (qint64)),
		         this, SLOT (bytesWritten (qint64)));
		#endif
	}

	void
	Client::bytesWritten (qint64 b)
	{
		Q_UNUSED (b);
		DBGIPC ("we wrote %lld bytes", b);
	}

	void
	Client::socketConnected ()
	{
		DBGIPC ("connected");
		hello ();
	}

	void
	Client::socketError (QAbstractSocket::SocketError error)
	{
		Q_UNUSED (error);
		emit connected (false);
		qWarning ("Error: %s", qPrintable (m_socket.errorString ()));
	}

	void
	Client::socketRead ()
	{
		DBGIPC ("we have data on the socket!");

		while (!m_socket.atEnd ()) {
			if (!m_readmsg.headerComplete ()) {
				if (m_socket.peek (16).size () == 16) {
					m_readmsg.processHeader (m_socket.read (16));
				} else {
					return;
				}
			}

			if (m_readmsg.process (&m_socket)) {
				parseMessage ();

				/* reset it */
				m_readmsg = Message ();
			}
		}
	}

	void
	Client::parseMessage ()
	{

		DBGIPC ("we have complete message with cookie %d cmd %d and object %d",
		         m_readmsg.cookie (), m_readmsg.cmd (), m_readmsg.object ());

		if (m_readmsg.cookie () == 0) {
			/* hello reply, let's fulhack it for now */
			DBGIPC ("got hello package!");
			emit connected (true);
			return;
		}

		if (m_resmap.contains (m_readmsg.cookie ())) {
			DBGIPC ("found a result");
			Result res = m_resmap.take (m_readmsg.cookie ());
			res.exec (m_readmsg);
		}
	}

	void
	Client::hello ()
	{
		Message msg (XMMS_IPC_OBJECT_MAIN, XMMS_IPC_CMD_HELLO);
		msg.add (XMMS_IPC_PROTOCOL_VERSION);
		msg.add (m_name);
		queueMsg (msg);
	}

	Result
	Client::queueMsg (const Message &msg, quint32 restartsignal)
	{
		QByteArray b = msg.finish (m_cookie);
		qint32 len = m_socket.write (b);
		if (len != b.size ()) {
			qWarning ("socket.write didn't accept all our output for message %d!", m_cookie);
		}

		Result ret (this, m_cookie ++);
		if (msg.object () == XMMS_IPC_OBJECT_SIGNAL &&
		    msg.cmd () == XMMS_IPC_CMD_SIGNAL && restartsignal) {
			DBGIPC ("got signal, setting restart bit to %d", restartsignal);
			ret.setRestartSignal (restartsignal);
		} else if (msg.object () == XMMS_IPC_OBJECT_SIGNAL &&
		           msg.cmd () == XMMS_IPC_CMD_BROADCAST) {
			ret.setBroadcast (true);
		}

		return ret;
	}

}
