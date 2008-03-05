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

bool
XmmsTestClient::pmtime (quint32 tme)
{
	qDebug ("pmtime %d", tme);
	return true;
}

void
XmmsTestClient::connected (bool ok)
{
	if (!ok) {
		qDebug ("we failed!");
		exit (0);
	}
	//m_client.playlist.list () (this, SLOT(apa (const QVariantList &)));
	//m_client.playback.signalPlaytime () (this, SLOT(pmtime (quint32)));
	//m_client.bindata.retrieve ("411a8e6f7c956c8eb564e24143753c32") (this, SLOT (bindata (const QByteArray &)));
	//m_client.playlist.add("file:///tmp/foobar korv åäö.mp3");

	QFile f("xmms2qt");
	f.open (QIODevice::ReadOnly);
	QByteArray t = f.readAll ();
	m_client.bindata.add (t)(this, SLOT(fileAdded(QString)));
	f.close ();
}

bool
XmmsTestClient::fileAdded(QString hash)
{
	qDebug () << "File added: " << hash;


	m_client.bindata.list ()(this, SLOT(printList(QVariantList)));
	m_client.bindata.retrieve (hash)(this, SLOT(bindata (QByteArray)));

	m_client.bindata.remove (hash) (this, SLOT(removed ()));
	return true;
}

bool
XmmsTestClient::printList(QVariantList list)
{
	QVariant v;
	foreach (v, list) {
		qDebug () << "List" << v.toString ();
	}
	return true;
}

bool
XmmsTestClient::bindata(QByteArray data)
{
    QFile f("xmms2qt");
	f.open (QIODevice::ReadOnly);
	QByteArray t = f.readAll ();
	f.close ();
	if (t == data) {
		qDebug () << "Bindata matches";
	} else {
		qWarning () << "Bindata wrong!";
	}
	
	return true;
}

bool
XmmsTestClient::removed ()
{
	qDebug () << "removed";

	return true;
}

int main (int argc, char **argv)
{
	QCoreApplication app (argc, argv);
	XmmsTestClient client;
	app.exec ();
}
