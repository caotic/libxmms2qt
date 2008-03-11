/*  XMMS2 - X Music Multiplexer System
 *  Copyright (C) 2003-2008 XMMS2 Team
 *
 *  PLUGINS ARE NOT CONSIDERED TO BE DERIVED WORK !!!
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 */

#ifndef __MEDIALIB_H__
#define __MEDIALIB_H__

#include <QObject>
#include "object.h"
#include "result.h"

#include <QStringList>
class QString;

namespace XMMSQt
{

	class Medialib : public BaseObject
	{
		public:
			Medialib (XmmsClient *client) : BaseObject (client)
			{
			};

			XmmsResult info (const quint32 &id);

			XmmsResult id (const QUrl &) const;
			XmmsResult id (const QString &) const;

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

			XmmsResult move (quint32 id, const QUrl &) const;
			XmmsResult move (quint32 id, const QString &) const;

			XmmsResult setEntryProperty (quint32 id, const QString &key,
										 const QString &value) const;
			XmmsResult setEntryProperty (quint32 id, const QString &key,
										 const QString &value,
										 const QString &source) const;
			XmmsResult setEntryProperty (quint32 id, const QString &key,
										 qint32 value) const;
			XmmsResult setEntryProperty (quint32 id, const QString &key,
										 qint32 value, const QString &source) const;
			XmmsResult removeEntryProperty (quint32 id, const QString &key) const;
			XmmsResult removeEntryProperty (quint32 id, const QString &key,
											const QString &source) const;
	};

}

#endif
