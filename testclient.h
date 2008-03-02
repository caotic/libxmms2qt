#include <QObject>

#ifndef TESTCLIENT
#define TESTCLIENT

#include "client.h"

#include <QFile>
#include <QByteArray>
#include <QVariantList>

class XmmsTestClient : public QObject
{
	Q_OBJECT
	public:
		XmmsTestClient ();
	public slots:
		void connected (bool);
		bool apa (const QVariantList &);
		bool minfo (const PropDict &);
		bool pmtime (quint32);
		bool bindata (QByteArray);
		bool removed ();
		bool printList (QVariantList);
		bool fileAdded (QString);
	private:
		XmmsClient m_client;
		int m_entries;
};


#endif

