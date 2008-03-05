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
				
	private slots:
		/* Connect to server */
		void initTestCase ();		
		
		/* playlist tests */
		void testPlaylistClear ();
		void testPlaylistAddUrl ();
		void testPlaylistClear2 ();
		void testPlaylistAddId ();
		void testPlaylistRemove ();
		/*void testPlaylistMove ();*/
	
	private:
		quint32 m_id;
		XmmsClient m_client;
		QEventLoop m_loop;
};

#endif
