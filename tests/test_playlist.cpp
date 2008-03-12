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

void
TestPlaylist::listPlaylists ()
{
	// For now we skip playlist creation if our test playlist, if it already
	// exists. Will be replaced with somethin better later
	testPlExists = false;

	m_client.playlist.listPlaylists ()
		(this, SLOT (cbListPlaylists (const QVariantList &)),
		 SLOT (cbFail (QString)));
	m_loop.exec ();
}

bool
TestPlaylist::cbListPlaylists (const QVariantList &list)
{
	if (list.contains (testPl)) {
		testPlExists = true;
		if (list[0] != testPl) {
			m_activePlaylist = list [0].toString ();
		} else if (list.size () > 1) {
			m_activePlaylist = list [1].toString ();
		} else {
			qWarning ("You should have at least one other playlist than the xmmsclientqt test playlist");
		}
	}
	// TODO: Test if there really has to exist at least one playlist
	TVERIFY (list.size () > 0, "At least one Playlist should exists");
	m_loop.exit ();
	return true;
}

void
TestPlaylist::activePlaylist ()
{
	m_client.playlist.activePlaylist ()
		(this, SLOT (cbActivePlaylist (const QString &)), SLOT (cbFail ()));
	m_loop.exec ();
}

bool
TestPlaylist::cbActivePlaylist (const QString &pl)
{
	if (pl != testPl) {
		m_activePlaylist = pl;
	}
	TVERIFY (!pl.isEmpty (), "Returned empty string");
	m_loop.exit ();
	return true;
}

void
TestPlaylist::createPlaylist ()
{
	if (testPlExists) {
		QSKIP ("Our test playlist already exists", SkipSingle);
	}
	m_client.playlist.createPlaylist (testPl)
		(this, SLOT (cbCreatePlaylist ()), SLOT (cbFail ()));
	m_loop.exec ();
}

bool
TestPlaylist::cbCreatePlaylist ()
{
	m_client.playlist.listPlaylists ()
	        (this, SLOT (cbCreatePlaylist2 (const QVariantList &)),
			 SLOT (cbFail (QString)));
	return true;
}

bool
TestPlaylist::cbCreatePlaylist2 (const QVariantList &list)
{
	TVERIFY (list.contains (testPl), "Playlist not in list");
	m_loop.exit ();
	return true;
}

void
TestPlaylist::loadPlaylist ()
{
	// those two methods should be executed in the eventloop
	m_client.playlist.loadPlaylist (testPl);
	m_client.playlist.activePlaylist ()
		(this, SLOT (cbLoadPlaylist (const QString &)), SLOT (cbFail (QString)));
	m_loop.exec ();
}

bool
TestPlaylist::cbLoadPlaylist (const QString &pl)
{
	TVERIFY (pl == testPl, "Our playlist wasn't loaded");
	m_loop.exit ();
	return true;
}

void
TestPlaylist::removeActivePlaylist ()
{
	QEXPECT_FAIL("", "Active playlist should not be removed", Continue);
	m_client.playlist.removePlaylist (testPl)
		(this, SLOT (cbRemovePlaylist ()), SLOT (cbPass ()));
	m_loop.exec ();
}

void
TestPlaylist::removePlaylist ()
{
	m_client.playlist.loadPlaylist (m_activePlaylist);
	m_client.playlist.removePlaylist (testPl)
		(this, SLOT (cbRemovePlaylist ()), SLOT (cbFail ()));
	m_loop.exec ();
}

bool
TestPlaylist::cbRemovePlaylist ()
{
	m_client.playlist.listPlaylists ()
	        (this, SLOT (cbRemovePlaylist2 (const QVariantList &)),
			 SLOT (cbFail (QString)));
	return true;

}

bool
TestPlaylist::cbRemovePlaylist2 (const QVariantList &list)
{
	TVERIFY (!list.contains (testPl), "Server still has out playlist");
	m_loop.exit ();
	return true;
}
