#include "test_playlist.h"
#include <QtTest/QtTest>

void
TestPlaylist::clear ()
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
TestPlaylist::addUrl ()
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
	TVERIFY (list.size () == 1, "list should be 1");
	/* save the medialib id of our test song */
	m_id = list.at (0).toUInt ();
	TVERIFY (m_id > 0, "medialib id should be bigger than 0!");
	m_loop.exit ();
	return true;
}

void
TestPlaylist::clear2 ()
{
	m_client.playlist.clear ();
	m_client.playlist.listEntries () (this, SLOT (cbClearPL (const QVariantList &)));
	m_loop.exec (); /* wait for clear command */
}

void
TestPlaylist::addId ()
{
	m_client.playlist.add (m_id);
	m_client.playlist.listEntries () (this, SLOT (cbAddUrl (const QVariantList &)));
	m_loop.exec ();
}

void
TestPlaylist::remove ()
{
	m_client.playlist.remove (0); /* remove first position */
	m_client.playlist.listEntries () (this, SLOT (cbClearPL (const QVariantList &)));
	m_loop.exec (); /* wait for list command */
}

bool
TestPlaylist::cbAddMove (const QVariantList &list)
{
	TVERIFY (list.size () == 2, "list size should be 2");
	m_id = list.at (0).toUInt ();
	m_loop.exit ();
	return true;
}

void
TestPlaylist::prepareMove ()
{
	QString path;
	path += QDir::currentPath ();
	path += "/files/testfile.mp3";
	QFile fp (path);
	if (!fp.exists (path)) {
		QSKIP ("This test requires the testfile that I expected to find.", SkipSingle);
	}
	path.prepend ("file://");
	m_client.playlist.add (path);
	
	path = QDir::currentPath ();
	path += "/files/testfile2.mp3";
	fp.copy (path);
	fp.close ();
	
	path.prepend ("file://");
	m_client.playlist.add (path);
	m_client.playlist.listEntries () (this, SLOT (cbAddMove (const QVariantList &)));
	m_loop.exec ();
}

bool
TestPlaylist::cbMove (const QVariantList &list)
{
	TVERIFY (list.size () == 2, "list should be 2 entries long");
	TVERIFY (m_id == list.at (1).toUInt (), "seems like the entry wasn't moved.");
	m_loop.exit ();
	return true;
}

void
TestPlaylist::move ()
{
	m_client.playlist.move (0, 1);
	m_client.playlist.listEntries () (this, SLOT (cbMove (const QVariantList &)));
	m_loop.exec ();
}

void
TestPlaylist::shuffle ()
{
	m_client.playlist.shuffle ();
	m_client.playlist.listEntries () (this, SLOT (cbAddMove (const QVariantList &)));
	m_loop.exec ();
}

bool
TestPlaylist::cbRadd (const QVariantList &list)
{
	TVERIFY (list.size () == 4, "list should be 4");
	m_loop.exit ();
	return true;
}

void
TestPlaylist::radd ()
{
	QString path ("file://");
	path += QDir::currentPath ();
	path += "/files";
	m_client.playlist.recursiveAdd (path);
	m_client.playlist.listEntries () (this, SLOT (cbRadd (const QVariantList &)));
	m_loop.exec ();
}
