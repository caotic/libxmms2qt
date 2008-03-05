
#include <QObject>
#include <QtTest/QtTest>
#include <QVariantList>

#include "client.h"

#include "test_common.h"

#ifndef __TEST_BINDATA_H__
#define __TEST_BINDATA_H__

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

#endif
