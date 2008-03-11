#include <QObject>
#include <QtTest/QtTest>
#include <QVariantList>

#include "client.h"

#include "test_common.h"
#include "test_class.h"

#ifndef __TEST_COLL_H__
#define __TEST_COLL_H__

class TestColl : public TestClass
{
	Q_OBJECT
	public:
		TestColl () : TestClass () {};
		
	public slots:
		bool cbList (const QVariantList &);
		bool cbQueryIds (const QVariantList &);
		
	private slots:
		void list ();
		void queryIds ();
};

#endif
