#include <QCoreApplication>
#include "testclient.h"
#include "client.h"

XmmsTestClient::XmmsTestClient () : QObject (), m_client (this, "xmms2qttest")
{
	m_client.doConnect ("127.0.0.1", 9667);
	connect (&m_client, SIGNAL (connected (bool)), this, SLOT (connected (bool)));
}

bool
XmmsTestClient::apa (quint32 pos)
{
	qDebug ("the callback was called with %d as pos", pos);
	
	return true;
}

void
XmmsTestClient::connected (bool ok)
{
	if (!ok) {
		qDebug ("we failed!");
		exit (0);
	}
	m_client.playlistCurrentPos () (this, SLOT(apa (quint32)));
}

int main (int argc, char **argv)
{
	QCoreApplication app (argc, argv);
	XmmsTestClient client;
	app.exec ();
}