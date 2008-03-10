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

#include <QObject>
#include <QTcpSocket>

#include "message.h"
#include "result.h"

class XMMSQt::XmmsClient;

#ifndef __XMMS_CLIENT_H__
#define __XMMS_CLIENT_H__

#include "playlist.h"
#include "medialib.h"
#include "playback.h"
#include "bindata.h"
#include "config.h"

#undef __DEBUG_IPC__

#ifdef __DEBUG_IPC__
#define DBGIPC(fmt, ...) qDebug("DEBUG IPC: " fmt, ## __VA_ARGS__)
#else
#define DBGIPC(fmt, ...)
#endif

namespace XMMSQt
{

	class XmmsClient : public QObject
	{
		Q_OBJECT
		public:
			XmmsClient (QObject *parent, const QString &name);
			void doConnect (const QString &, quint32);
					
			void setResult (const XmmsResult &res) {
				DBGIPC ("adding %d", res.cookie ());
				m_resmap[res.cookie()] = res;
			};

			XmmsResult queueMsg (const XmmsMessage &msg, quint32 restartsignal = 0);

			QString name () const { return m_name; }

			/* the sub objects here */
			Playlist playlist;
			Medialib medialib;
			Playback playback;
			Bindata bindata;
			Config config;
			
		private:
			QString m_name;
			quint32 m_cookie;
			XmmsMessage m_readmsg;
			
			void hello ();
			void parseMessage ();
			QTcpSocket m_socket;
			
			QMap<quint32, XmmsResult> m_resmap;
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
