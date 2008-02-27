#include <QCoreApplication>
#include "testclient.h"
#include "client.h"

XmmsTestClient::XmmsTestClient () : QObject (), m_client (this, "xmms2qttest")
{
	m_client.doConnect ("127.0.0.1", 9667);
	connect (&m_client, SIGNAL (connected (bool)), this, SLOT (connected (bool)));
}

bool
XmmsTestClient::apa (const QVariantList &list)
{
    m_entries = list.size ();
	for (int i = 0; i < list.size (); i ++)
	{
		m_client.medialib.info (list.at (i).toUInt ()) (this, SLOT (minfo(const PropDict &)));
	}
	return true;
}

bool
XmmsTestClient::minfo (const PropDict &dict)
{
	qDebug ("%s - %s", qPrintable (dict["artist"].toString ()), qPrintable (dict["title"].toString ()));
    m_entries --;
    if (m_entries == 0) {
        QCoreApplication::instance()->exit (1);
    }
	return true;
}

void
XmmsTestClient::connected (bool ok)
{
	if (!ok) {
		qDebug ("we failed!");
		exit (0);
	}
	m_client.playlist.list () (this, SLOT(apa (const QVariantList &)));
}

int main (int argc, char **argv)
{
	QCoreApplication app (argc, argv);
	XmmsTestClient client;
	app.exec ();
}
