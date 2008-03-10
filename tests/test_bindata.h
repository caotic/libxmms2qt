
#include <QObject>
#include <QtTest/QtTest>
#include <QVariantList>

#include "client.h"

#include "test_common.h"
#include "test_class.h"

#ifndef __TEST_BINDATA_H__
#define __TEST_BINDATA_H__

using namespace XMMSQt;

class TestBindata : public TestClass
{
	Q_OBJECT
	public:
		TestBindata () : TestClass () {};
		
	public slots:
		bool cbAdd (QString hash);
		bool cbList (QVariantList);
		bool cbRetrieve (QByteArray);

		/* waits for remove to return and feches list */
		bool cbRemove ();
		/* tests if has is still in bindata list */
		bool cbRemove2 (QVariantList);

	private slots:
		/* bindata tests */
		void add ();
		void list ();
		void retrieve ();
		void remove ();

	private:
		QByteArray m_testdata; // we cache the testdata, to compare it later
		QString m_serverhash;
};

#endif
