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
		bool apa (quint32);
	private:
		XmmsClient m_client;
};


#endif

