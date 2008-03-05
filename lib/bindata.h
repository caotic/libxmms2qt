#include <QObject>
#include <QByteArray>

#ifndef __BINDATA_H__
#define __BINDATA_H__

class Bindata;

#include <QObject>
#include "object.h"
#include "result.h"

class Bindata : public BaseObject
{
	public:
		Bindata (XmmsClient *client) : BaseObject (client)
		{
		};

		XmmsResult add (const QByteArray &);

		XmmsResult retrieve (const QString &);

		XmmsResult list ();

	public slots:
		XmmsResult remove (const QString &);
};

#endif
