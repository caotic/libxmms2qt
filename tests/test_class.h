#include <QtTest/QtTest>
#include <QObject>
#include <QEventLoop>

#include "client.h"

#ifndef __TEST_CLASS_H__
#define __TEST_CLASS_H__

using namespace XMMSQt;

class TestClass : public QObject
{
	Q_OBJECT
	public:
		TestClass () : QObject (), m_client (NULL, "test") {};
	public slots:
		void connected (bool b)
		{
			Q_ASSERT_X (b, "connected", "failed to connect to server");
			m_loop.exit ();
		};

		void cbFail (QString errMsg)
		{
			m_loop.exit ();
			QFAIL (errMsg.toAscii ());
		};

		// Callback, if we expect a test to execute the error callback
		void cbPass (QString errMsg)
		{
			Q_UNUSED (errMsg);
			m_loop.exit ();
		}

	private slots:
		void initTestCase ()
		{
			m_client.doConnect ("127.0.0.1", 9667);
			connect (&m_client, SIGNAL (connected (bool)), this, SLOT (connected (bool)));
			m_loop.exec ();
		};
		
	protected:
		Client m_client;
		QEventLoop m_loop;
		
};

#endif
