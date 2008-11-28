#include <QtTest/QtTest>
#include <QObject>
#include <QEventLoop>
#include <QTimer>

#include "client.h"

#ifndef __TEST_CLASS_H__
#define __TEST_CLASS_H__

using namespace XMMSQt;

class TestClass : public QObject
{
	Q_OBJECT
	public:
		TestClass () : QObject (), m_client (NULL, "test") {};

		inline void waitForAnswer (int timeout=250)
		{
			m_timer.start (timeout);
			m_loop.exec ();
		};

		inline void waitDone ()
		{
			m_timer.stop ();
			m_loop.exit ();
		};

	public slots:
		void connected (bool b)
		{
			Q_ASSERT_X (b, "connected", "failed to connect to server");
			waitDone ();
			QVERIFY (b); // don't execute any other command if connection fails
		};

		void cbFail (QString errMsg)
		{
			QFAIL (errMsg.toAscii ());
			waitDone ();
		};

		// Callback, if we expect a test to execute the error callback
		void cbPass (QString errMsg)
		{
			Q_UNUSED (errMsg);
			waitDone ();
		}

		void cbTimeout ()
		{
			waitDone ();
			QFAIL ("Timeout. The server took too long to respond or this testcase has a bug");
		}

	private slots:
		void initTestCase ()
		{
			connect(&m_timer, SIGNAL(timeout()), this, SLOT(cbTimeout()));
			m_client.doConnect ("127.0.0.1", 9667);
			connect (&m_client, SIGNAL (connected (bool)), this, SLOT (connected (bool)));
			waitForAnswer ();
		};
		
	protected:
		Client m_client;

	private:
		QEventLoop m_loop;
		QTimer m_timer;
};

#endif
