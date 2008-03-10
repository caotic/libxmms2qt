#include <QObject>
#include <QtTest/QtTest>
#include <QVariantList>

#include "client.h"

#include "test_common.h"
#include "test_class.h"

#ifndef __TEST_ERROR_H__
#define __TEST_ERROR_H__

class TestColl : public TestClass
{
	Q_OBJECT
	public:
		TestColl () : TestClass () {};
		
	public slots:
		bool cbQueryIds (const QList<quint32> &);
		
	private slots:
		void queryIds ();
};

#endif
