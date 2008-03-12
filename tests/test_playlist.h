#include <QObject>
#include <QtTest/QtTest>
#include <QVariantList>

#include "client.h"
#include "test_common.h"
#include "test_class.h"

#ifndef __TEST_PLAYLIST_H__
#define __TEST_PLAYLIST_H__

const QString testPl ("xmmsclientqt");

class TestPlaylist : public TestClass
{
	Q_OBJECT
	public:
		TestPlaylist () : TestClass () {};
		
	public slots:
		bool cbListPlaylists (const QVariantList &);
		bool cbActivePlaylist (const QString &);
		bool cbCreatePlaylist ();
		bool cbCreatePlaylist2 (const QVariantList &);
		bool cbLoadPlaylist (const QString &);

		bool cbClearPL (const QVariantList &);
		bool cbAddUrl (const QVariantList &);
		bool cbAddMove (const QVariantList &);
		bool cbMove (const QVariantList &);
		bool cbRadd (const QVariantList &);

		bool cbRemovePlaylist ();
		bool cbRemovePlaylist2 (const QVariantList &);
	private slots:
		void listPlaylists ();
		void activePlaylist ();
		void createPlaylist ();
		void loadPlaylist ();
		/* playlist tests */
		void addUrl ();
		void clear ();
		void addId ();
		void remove ();
		void prepareMove ();
		void move ();
		void shuffle ();
		void radd ();
		/*void testPlaylistMove ();*/
		void removeActivePlaylist ();
		void removePlaylist ();
	
	private:
		quint32 m_id;
		bool testPlExists;
		QString m_activePlaylist;
};

#endif
