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
			Medialib (Client *client) : BaseObject (client)
			{
			};

			Result info (const quint32 &id);

			Result id (const QUrl &) const;
			Result id (const QString &) const;

			Result broadcastEntryAdded ();
			Result broadcastEntryChanged ();

			static QString encodeUrl (const QString &,
			                          const QStringList &args = QStringList ());

			static QString decodeUrl (const QString &);

		public slots:
			Result add (const QUrl &, const QStringList &args = QStringList ()) const;
			Result add (const QString &,
			            const QStringList &args = QStringList ()) const;
			Result addEncoded (const QString &) const;
			Result addPath (const QUrl &) const;
			Result addPath (const QString &) const;
			Result addPathEncoded (const QString &) const;

			Result rehash (quint32 id = 0) const;
			Result remove (quint32) const;

			Result move (quint32 id, const QUrl &) const;
			Result move (quint32 id, const QString &) const;

			Result setEntryProperty (quint32 id, const QString &key,
			                         const QString &value) const;
			Result setEntryProperty (quint32 id, const QString &key,
			                         const QString &value,
			                         const QString &source) const;
			Result setEntryProperty (quint32 id, const QString &key,
			                         qint32 value) const;
			Result setEntryProperty (quint32 id, const QString &key,
			                         qint32 value, const QString &source) const;
			Result removeEntryProperty (quint32 id, const QString &key) const;
			Result removeEntryProperty (quint32 id, const QString &key,
			                            const QString &source) const;
	};

}

#endif
