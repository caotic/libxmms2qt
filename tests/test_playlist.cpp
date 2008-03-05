#include "test_playlist.h"
#include <QtTest/QtTest>

void
TestPlaylist::connected (bool b)
{
	Q_ASSERT_X (b, "connect", "The connect signal returned error");
	m_loop.exit ();
}

void
TestPlaylist::initTestCase ()
{
	m_client.doConnect ("127.0.0.1", 9667);
	connect (&m_client, SIGNAL (connected (bool)), this, SLOT (connected (bool)));
	m_loop.exec ();
}

void
TestPlaylist::testPlaylistClear ()
{
	m_client.playlist.clear ();
	m_client.playlist.listEntries () (this, SLOT (cbClearPL (const QVariantList &)));
	m_loop.exec (); /* wait for clear command */
}

bool
TestPlaylist::cbClearPL (const QVariantList &list)
{
	TVERIFY (list.size () == 0, "list should be 0");
	m_loop.exit ();
	return true;
}

void
TestPlaylist::testPlaylistAddUrl ()
{
	QString path;
	path += QDir::currentPath ();
	path += "/files/testfile.mp3";
	if (!QFile::exists (path)) {
		QSKIP ("This test requires the testfile that I expected to find.", SkipSingle);
	}
	path.prepend ("file://");
	m_client.playlist.add (path);
	m_client.playlist.listEntries () (this, SLOT (cbAddUrl (const QVariantList &)));
	m_loop.exec ();
}

bool
TestPlaylist::cbAddUrl (const QVariantList &list)
{
	TVERIFY (list.size () == 1, "list should be 0");
	/* save the medialib id of our test song */
	m_id = list.at (0).toUInt ();
	TVERIFY (m_id > 0, "medialib id should be bigger than 0!");
	m_loop.exit ();
	return true;
}

void
TestPlaylist::testPlaylistClear2 ()
{
	m_client.playlist.clear ();
	m_client.playlist.listEntries () (this, SLOT (cbClearPL (const QVariantList &)));
	m_loop.exec (); /* wait for clear command */
}

void
TestPlaylist::testPlaylistAddId ()
{
	m_client.playlist.add (m_id);
	m_client.playlist.listEntries () (this, SLOT (cbAddUrl (const QVariantList &)));
	m_loop.exec ();
}

void
TestPlaylist::testPlaylistRemove ()
{
	m_client.playlist.remove (0); /* remove first position */
	m_client.playlist.listEntries () (this, SLOT (cbClearPL (const QVariantList &)));
	m_loop.exec (); /* wait for list command */
}
