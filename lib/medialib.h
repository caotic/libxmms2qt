#ifndef __MEDIALIB_H__
#define __MEDIALIB_H__

class Medialib;

#include <QObject>
#include "object.h"
#include "result.h"

#include <QStringList>
class QString;

class Medialib : public BaseObject
{
	public:
		Medialib (XmmsClient *client) : BaseObject (client)
		{
		};
		
		XmmsResult info (const quint32 &id);

		XmmsResult broadcastEntryAdded ();
		XmmsResult broadcastEntryChanged ();

		static QString encodeUrl (const QString &, const QStringList &args = QStringList ());

	public slots:
		XmmsResult add (const QUrl &, const QStringList &args = QStringList ()) const;
		XmmsResult add (const QString &, const QStringList &args = QStringList ()) const;
		XmmsResult addEncoded (const QString &) const;
		XmmsResult addPath (const QUrl &) const;
		XmmsResult addPath (const QString &) const;
		XmmsResult addPathEncoded (const QString &) const;

		XmmsResult rehash (quint32 id = 0) const;
		XmmsResult remove (quint32) const;

		XmmsResult entryPropertySet (quint32 id, const QString &key,
		                             const QString &value) const;
		XmmsResult entryPropertySet (quint32 id, const QString &key,
		                             const QString &value,
									 const QString &source) const;
		XmmsResult entryPropertySet (quint32 id, const QString &key,
		                             qint32 value) const;
		XmmsResult entryPropertySet (quint32 id, const QString &key,
		                             qint32 value, const QString &source) const;
		XmmsResult entryPropertyRemove (quint32 id, const QString &key) const;
		XmmsResult entryPropertyRemove (quint32 id, const QString &key,
		                                const QString &source) const;
};

#endif