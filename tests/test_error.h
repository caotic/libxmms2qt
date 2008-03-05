
#include <QObject>
#include <QtTest/QtTest>
#include <QVariantList>

#include "client.h"

#include "test_common.h"
#include "test_class.h"
#include "propdict.h"

#ifndef __TEST_ERROR_H__
#define __TEST_ERROR_H__

class TestError : public TestClass
{
	Q_OBJECT
	public:
		TestError () : TestClass () {};
		
	public slots:
		void cbError (const QString &);
		bool cbNormal (const PropDict &);

		void cbError2 (const QString &);
		bool cbNormal2 ();
		

	private slots:
		void errorShouldBeCalled ();
		void errorShouldNotBeCalled ();
};

#endif
