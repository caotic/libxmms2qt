#include "test_error.h"

bool
TestError::cbNormal (const PropDict &dict)
{
	Q_UNUSED (dict);
	QTest::qFail ("We should never have reached this point!", __FILE__, __LINE__);
	m_loop.exit ();
	return true;
}

void
TestError::cbError (const QString &error)
{
	QCOMPARE (error, QString ("No such entry, 0"));
	m_loop.exit ();
}

void
TestError::errorShouldBeCalled ()
{
	/* should fail */
	m_client.medialib.info (0) (this, SLOT (cbNormal (PropDict)), SLOT (cbError (QString)));
	m_loop.exec ();
}

bool
TestError::cbNormal2 ()
{
	m_loop.exit ();
	return true;
}

void
TestError::cbError2 (const QString &error)
{
	qDebug ("The error string: %s", qPrintable (error));
	QTest::qFail ("We should never have reached this point!", __FILE__, __LINE__);
	m_loop.exit ();
}

void
TestError::errorShouldNotBeCalled ()
{
	/* should fail */
	m_client.medialib.remove (0) (this, SLOT (cbNormal2 ()), SLOT (cbError2 (QString)));
	m_loop.exec ();
}
