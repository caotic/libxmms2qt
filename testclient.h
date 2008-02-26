#include <QObject>

#ifndef TESTCLIENT
#define TESTCLIENT

#include "client.h"

class XmmsTestClient : public QObject
{
	Q_OBJECT
	public:
		XmmsTestClient ();
	public slots:
		void connected (bool);
		bool apa (const QVariantList &);
		bool minfo (const PropDict &);
	private:
		XmmsClient m_client;
        int m_entries;
};


#endif

