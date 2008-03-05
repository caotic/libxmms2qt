
#include "test_bindata.h"
#include <QtTest/QtTest>

#include <QFile>
#include <QCryptographicHash>

void
TestBindata::connected (bool b)
{
	QVERIFY2 (b, "The connect signal returned error");
	m_loop.exit ();
}

void
TestBindata::initTestCase ()
{
	m_client.doConnect ("127.0.0.1", 9667);
	connect (&m_client, SIGNAL (connected (bool)), this, SLOT (connected (bool)));
	m_loop.exec ();
}




void
TestBindata::addBindata()
{
	// usually we should add a Pixmap here
	QFile f("files/testfile.mp3");
	f.open (QIODevice::ReadOnly);
	m_testdata = f.readAll ();
	m_client.bindata.add (m_testdata) (this, SLOT (cbAddBindata (QString)));
	f.close ();
	m_loop.exec ();
}

bool
TestBindata::cbAddBindata (QString hash)
{
	m_serverhash = hash;

	TVERIFY (hash.toAscii () ==
	    QCryptographicHash::hash (m_testdata, QCryptographicHash::Md5).toHex (),
		"Returned String doesn't match md5 hash of data");

	m_loop.exit ();
	return true;
}

void
TestBindata::listBindata ()
{
	m_client.bindata.list ()(this, SLOT (cbListBindata (QVariantList)));

	m_loop.exec ();
}

bool
TestBindata::cbListBindata (QVariantList list)
{
	QVariant hash (m_serverhash);

	TVERIFY (list.contains (hash), "Server doesn't have the file we sent");

	m_loop.exit ();
	return true;
}

void
TestBindata::retrieveBindata ()
{
	m_client.bindata.retrieve (m_serverhash)
	                          (this, SLOT (cbRetrieveBindata (QByteArray)));

	m_loop.exec ();
}

bool
TestBindata::cbRetrieveBindata (QByteArray serverdata)
{
	TVERIFY (m_testdata == serverdata,
	         "Our local file is different from the retrieved one");

	m_loop.exit ();
	return true;
}


void
TestBindata::removeBindata ()
{
	m_client.bindata.remove (m_serverhash) (this, SLOT (cbRemoveBindata ()));

	m_loop.exec ();
}

bool
TestBindata::cbRemoveBindata ()
{
	m_client.bindata.list ()(this, SLOT (cbRemoveBindata2 (QVariantList)));

	return true;
}

bool
TestBindata::cbRemoveBindata2 (QVariantList list)
{
	QVariant hash (m_serverhash);

	TVERIFY (!list.contains (hash), "Server still contains Bindata");

	m_loop.exit ();
	return true;
}
