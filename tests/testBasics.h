#include <QObject>
#include <QtTest/QtTest>
#include <QVariantList>

#include "client.h"

#define TVERIFY(statement, description) \
do {\
    if (statement) {\
        if (!QTest::qVerify(true, #statement, (description), __FILE__, __LINE__)) {\
			m_loop.exit();\
            return true;\
		}\
    } else {\
        if (!QTest::qVerify(false, #statement, (description), __FILE__, __LINE__)) {\
			m_loop.exit();\
            return true;\
		}\
    }\
} while (0)


class TestBasics : public QObject
{
	Q_OBJECT
	public:
		TestBasics () : QObject (), m_client (NULL, "test") {};
		
	public slots:
		void connected (bool);
		bool cbClearPL (const QVariantList &);
		bool cbAddUrl (const QVariantList &);
				
	private slots:
		/* testConnect */
		void testConnect ();
		
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
