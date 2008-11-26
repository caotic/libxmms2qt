
#include <xmmsc/xmmsc_idnumbers.h>

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
	waitForAnswer ();
}

bool
TestBindata::cbAdd (QString hash)
{
	m_serverhash = hash;

	TVERIFY (hash.toAscii () ==
	    QCryptographicHash::hash (m_testdata, QCryptographicHash::Md5).toHex (),
		"Returned String doesn't match md5 hash of data");

	waitDone ();
	return true;
}

void
TestBindata::list ()
{
	if (XMMS_IPC_PROTOCOL_VERSION < 11) {
		QSKIP("Bindata list not supported on DrK", SkipSingle);
	}
	m_client.bindata.list ()(this, SLOT (cbList (QVariantList)), SLOT(cbFail (QString)));

	waitForAnswer ();
}

bool
TestBindata::cbList (QVariantList list)
{
	QVariant hash (m_serverhash);

	TVERIFY (list.contains (hash), "Server doesn't have the file we sent");

	waitDone ();
	return true;
}

void
TestBindata::retrieve ()
{
	m_client.bindata.retrieve (m_serverhash)
	                          (this, SLOT (cbRetrieve (QByteArray)));

	waitForAnswer ();
}

bool
TestBindata::cbRetrieve (QByteArray serverdata)
{
	TVERIFY (m_testdata == serverdata,
	         "Our local file is different from the retrieved one");

	waitDone ();
	return true;
}


void
TestBindata::remove ()
{
	m_client.bindata.remove (m_serverhash) (this, SLOT (cbRemove ()));

	waitForAnswer ();
}

bool
TestBindata::cbRemove ()
{
#if XMMS_IPC_VERSION >=11
	m_client.bindata.list ()(this, SLOT (cbRemove2 (QVariantList)));
#else
	waitDone ();
#endif
	return true;
}

bool
TestBindata::cbRemove2 (QVariantList list)
{
	QVariant hash (m_serverhash);

	TVERIFY (!list.contains (hash), "Server still contains Bindata");

	waitDone ();
	return true;
}
