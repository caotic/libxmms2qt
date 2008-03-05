#include <QObject>
#include <QtTest/QtTest>
#include <QVariantList>

#include "client.h"
#include "test_common.h"
#include "test_class.h"

#ifndef __TEST_PLAYLIST_H__
#define __TEST_PLAYLIST_H__

class TestPlaylist : public TestClass
{
	Q_OBJECT
	public:
		TestPlaylist () : TestClass () {};
		
	public slots:
		bool cbClearPL (const QVariantList &);
		bool cbAddUrl (const QVariantList &);
		bool cbAddMove (const QVariantList &);
		bool cbMove (const QVariantList &);
		bool cbRadd (const QVariantList &);
				
	private slots:
		/* playlist tests */
		void clear ();
		void addUrl ();
		void clear2 ();
		void addId ();
		void remove ();
		void prepareMove ();
		void move ();
		void shuffle ();
		void radd ();
		/*void testPlaylistMove ();*/
	
	private:
		quint32 m_id;
};

#endif
