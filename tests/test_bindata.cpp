
#include "test_bindata.h"
#include <QtTest/QtTest>

#include <QFile>
#include <QCryptographicHash>

void
TestBindata::add ()
{
	// usually we should add a Pixmap here
	QFile f("files/testfile.mp3");
	f.open (QIODevice::ReadOnly);
	m_testdata = f.readAll ();
	m_client.bindata.add (m_testdata) (this, SLOT (cbAdd (QString)));
	f.close ();
	m_loop.exec ();
}

bool
TestBindata::cbAdd (QString hash)
{
	m_serverhash = hash;

	TVERIFY (hash.toAscii () ==
	    QCryptographicHash::hash (m_testdata, QCryptographicHash::Md5).toHex (),
		"Returned String doesn't match md5 hash of data");

	m_loop.exit ();
	return true;
}

void
TestBindata::list ()
{
	m_client.bindata.list ()(this, SLOT (cbList (QVariantList)));

	m_loop.exec ();
}

bool
TestBindata::cbList (QVariantList list)
{
	QVariant hash (m_serverhash);

	TVERIFY (list.contains (hash), "Server doesn't have the file we sent");

	m_loop.exit ();
	return true;
}

void
TestBindata::retrieve ()
{
	m_client.bindata.retrieve (m_serverhash)
	                          (this, SLOT (cbRetrieve (QByteArray)));

	m_loop.exec ();
}

bool
TestBindata::cbRetrieve (QByteArray serverdata)
{
	TVERIFY (m_testdata == serverdata,
	         "Our local file is different from the retrieved one");

	m_loop.exit ();
	return true;
}


void
TestBindata::remove ()
{
	m_client.bindata.remove (m_serverhash) (this, SLOT (cbRemove ()));

	m_loop.exec ();
}

bool
TestBindata::cbRemove ()
{
	m_client.bindata.list ()(this, SLOT (cbRemove2 (QVariantList)));

	return true;
}

bool
TestBindata::cbRemove2 (QVariantList list)
{
	QVariant hash (m_serverhash);

	TVERIFY (!list.contains (hash), "Server still contains Bindata");

	m_loop.exit ();
	return true;
}
