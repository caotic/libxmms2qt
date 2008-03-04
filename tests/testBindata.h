
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


class TestBindata : public QObject
{
	Q_OBJECT
	public:
		TestBindata () : QObject (), m_client (NULL, "test") {};
		
	public slots:
		void connected (bool);

		bool cbAddBindata (QString hash);
		bool cbListBindata (QVariantList);
		bool cbRetrieveBindata (QByteArray);

		/* waits for remove to return and feches list */
		bool cbRemoveBindata ();
		/* tests if has is still in bindata list */
		bool cbRemoveBindata2 (QVariantList);

	private slots:
		/* Connect to server */
		void initTestCase ();

		/* bindata tests */
		void addBindata ();
		void listBindata ();
		void retrieveBindata ();

		void removeBindata ();

	private:
		XmmsClient m_client;
		QEventLoop m_loop; // used to seralize the tests.

		QByteArray m_testdata; // we cache the testdata, to compare it later
		QString m_serverhash;
};
