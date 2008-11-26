#include "test_coll.h"

bool
TestColl::cbList (const QVariantList &lst)
{
	for (int i = 0; i < lst.size (); i++)
	{
		qDebug () << lst.at (i).toString ();
	}
	waitDone ();
	return true;
}

void
TestColl::list ()
{
	m_client.collection.list (Collection::COLLECTIONS) (this, SLOT (cbList (const QVariantList &)));
	waitForAnswer ();
}

bool
TestColl::cbQueryIds (const QVariantList &val)
{
	qDebug ("list = %d", val.size ());
	waitDone ();
	return true;
}

void
TestColl::queryIds ()
{
	QSKIP("testcase is broken, need a specific collection", SkipSingle);
	Coll::Reference ref ("dismantled", Collection::COLLECTIONS);
	m_client.collection.queryIds (ref) (this, SLOT (cbQueryIds (const QVariantList &)));
	waitForAnswer ();
}
