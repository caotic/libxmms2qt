
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

		bool cbAdd (QString hash);
		bool cbList (QVariantList);
		bool cbRetrieve (QByteArray);

		/* waits for remove to return and feches list */
		bool cbRemove ();
		/* tests if has is still in bindata list */
		bool cbRemove2 (QVariantList);

	private slots:
		/* Connect to server */
		void initTestCase ();

		/* bindata tests */
		void add ();
		void list ();
		void retrieve ();

		void remove ();

	private:
		XmmsClient m_client;
		QEventLoop m_loop; // used to seralize the tests.

		QByteArray m_testdata; // we cache the testdata, to compare it later
		QString m_serverhash;
};

#endif
