#include "test_coll.h"

bool
TestColl::cbList (const QVariantList &lst)
{
	for (int i = 0; i < lst.size (); i++)
	{
		qDebug () << lst.at (i).toString ();
	}
	m_loop.exit ();
	return true;
}

void
TestColl::list ()
{
	m_client.collection.list (Collection::COLLECTIONS) (this, SLOT (cbList (const QVariantList &)));
	m_loop.exec ();
}

bool
TestColl::cbQueryIds (const QVariantList &val)
{
	qDebug ("list = %d", val.size ());
	m_loop.exit ();
	return true;
}

void
TestColl::queryIds ()
{
	QSKIP("testcase is broken, need a specific collection", SkipSingle);
	Coll::Reference ref ("dismantled", Collection::COLLECTIONS);
	m_client.collection.queryIds (ref) (this, SLOT (cbQueryIds (const QVariantList &)));
	m_loop.exec ();
}