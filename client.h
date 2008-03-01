#include <QObject>
#include <QTcpSocket>

#include "message.h"
#include "result.h"

class XmmsClient;

#ifndef __XMMS_CLIENT_H__
#define __XMMS_CLIENT_H__

#include "playlist.h"
#include "medialib.h"
#include "playback.h"
#include "bindata.h"
#include "config.h"

#define __DEBUG_IPC__

#ifdef __DEBUG_IPC__
#define DBGIPC(fmt, ...) qDebug("DEBUG IPC: " fmt, ## __VA_ARGS__)
#else
#define DBGIPC(fmt, ...)
#endif

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

#endif
