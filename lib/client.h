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

#ifndef __XMMSQT_CLIENT_H__
#define __XMMSQT_CLIENT_H__

#include <QObject>
#include <QTcpSocket>

namespace XMMSQt
{
	class Client;
}

#include "message.h"
#include "result.h"

#include "playlist.h"
#include "medialib.h"
#include "playback.h"
#include "bindata.h"
#include "config.h"
#include "collection.h"

#undef __DEBUG_IPC__

#ifdef __DEBUG_IPC__
#define DBGIPC(fmt, ...) qDebug("DEBUG IPC: " fmt, ## __VA_ARGS__)
#else
#define DBGIPC(fmt, ...)
#endif

namespace XMMSQt
{

	class Client : public QObject
	{
		Q_OBJECT
		public:
			Client (QObject *parent, const QString &name);
			void doConnect (const QString &, quint32);

			void setResult (const Result &res) {
				DBGIPC ("adding %d", res.cookie ());
				m_resmap[res.cookie()] = res;
			};

			Result queueMsg (const Message &msg, quint32 restartsignal = 0);

			QString name () const { return m_name; }

			/* the sub objects here */
			Playlist playlist;
			Medialib medialib;
			Playback playback;
			Bindata bindata;
			Config config;
			Collection collection;

		private:
			QString m_name;
			quint32 m_cookie;
			Message m_readmsg;

			void hello ();
			void parseMessage ();
			QTcpSocket m_socket;

			QMap<quint32, Result> m_resmap;
		signals:
			void connected (bool);

		private slots:
			void socketError (QAbstractSocket::SocketError);
			void socketRead ();
			void socketConnected ();
			void bytesWritten (qint64);

	};

}

#endif
