#include <QObject>
#include <QtTest/QtTest>
#include <QVariantList>

#include "client.h"
#include "test_common.h"

#ifndef __TEST_PLAYLIST_H__
#define __TEST_PLAYLIST_H__

class TestPlaylist : public QObject
{
	Q_OBJECT
	public:
		TestPlaylist () : QObject (), m_client (NULL, "test") {};
		
	public slots:
		void connected (bool);
		bool cbClearPL (const QVariantList &);
		bool cbAddUrl (const QVariantList &);
		bool cbAddMove (const QVariantList &);
		bool cbMove (const QVariantList &);
		bool cbRadd (const QVariantList &);
				
	private slots:
		/* Connect to server */
		void initTestCase ();		
		
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
		XmmsClient m_client;
		QEventLoop m_loop;
};

#endif
