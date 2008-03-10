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