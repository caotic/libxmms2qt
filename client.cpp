#include "message.h"
#include "client.h"
#include "result.h"
#include <xmmsc/xmmsc_idnumbers.h>

#include <QIODevice>
#include <QFile>

XmmsClient::XmmsClient (QObject *parent, const QString &name) : QObject (parent), playlist (this), medialib (this)
{
	m_name = name;
	m_cookie = 0;
	m_readmsg = NULL;
}

void
XmmsClient::doConnect (const QString &host, quint32 port)
{
	m_socket.connectToHost (host, port);
	connect (&m_socket, SIGNAL (connected ()), this, SLOT (socketConnected ()));
	connect (&m_socket, SIGNAL (error (QAbstractSocket::SocketError)),
			 this, SLOT (socketError (QAbstractSocket::SocketError)));
	connect (&m_socket, SIGNAL (readyRead ()), this, SLOT (socketRead ()));
}

void
XmmsClient::socketConnected ()
{
	DBGIPC ("connected");
	hello ();
}

void
XmmsClient::socketError (QAbstractSocket::SocketError error)
{
	Q_UNUSED (error);
	emit connected (false);
	qWarning ("Error: %s", qPrintable (m_socket.errorString ()));
}

void
XmmsClient::socketRead ()
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
			m_readmsg = XmmsMessage ();
		}
	}
}

void
XmmsClient::parseMessage ()
{
	
	DBGIPC ("we have complete message with cookie %d cmd %d and object %d", m_readmsg.cookie (), m_readmsg.cmd (), m_readmsg.object ());
	
	if (m_readmsg.cmd () == XMMS_IPC_CMD_ERROR) {
		XmmsMessage m = m_readmsg;
		qWarning ("error on command %d", m.cookie ());
		/* we need a good way to handle this later ... */
		QString s = m.getString (false);
		qWarning ("Error: %s", qPrintable (s));
		return;
	}
	
	if (m_readmsg.cookie () == 0) {
		/* hello reply, let's fulhack it for now */
		DBGIPC ("got hello package!");
		emit connected (true);
		return;
	}
		
	if (m_resmap.contains (m_readmsg.cookie ())) {
		DBGIPC ("found a result");
		XmmsResult res = m_resmap.take (m_readmsg.cookie ());
		res.exec (m_readmsg);
	}
}

void
XmmsClient::hello ()
{
	XmmsMessage msg (XMMS_IPC_OBJECT_MAIN, XMMS_IPC_CMD_HELLO);
	msg.add (XMMS_IPC_PROTOCOL_VERSION);
	msg.add (m_name);
	queueMsg (msg);
}

XmmsResult
XmmsClient::queueMsg (const XmmsMessage &msg)
{
	QByteArray b = msg.finish (m_cookie);
	qint32 len = m_socket.write (b);
	if (len != b.size ()) {
		qWarning ("socket.write didn't accept all our output for message %d!", m_cookie);
	}
	
	return XmmsResult (this, m_cookie ++);
}