#include <QObject>
#include <QTcpSocket>

#include "message.h"
#include "result.h"

#ifndef __XMMS_CLIENT_H__
#define __XMMS_CLIENT_H__

class XmmsClient : public QObject
{
	Q_OBJECT
	public:
		XmmsClient (QObject *parent, const QString &name);
		void doConnect (const QString &, quint32);
		
		XmmsResult playlistCurrentPos ();
		
		void setResult (const XmmsResult &res) {
			qDebug ("adding %d", res.cookie ());
			m_resmap[res.cookie()] = res;
		};
		
	private:
		QString m_name;
		quint32 m_cookie;
		XmmsMessage m_readmsg;
		
		void hello ();
		XmmsResult queueMsg (const XmmsMessage &);
		void parseMessage ();
		QTcpSocket m_socket;
		
		QMap<quint32, XmmsResult> m_resmap;
	signals:
		void connected (bool);
		
	private slots:
		void socketError (QAbstractSocket::SocketError);
		void socketRead ();
		void socketConnected ();

};

#endif
