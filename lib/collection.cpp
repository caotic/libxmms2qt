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

#include "collection.h"

namespace XMMSQt
{

	const Collection::Namespace Collection::ALL         = XMMS_COLLECTION_NS_ALL;
	const Collection::Namespace Collection::COLLECTIONS = XMMS_COLLECTION_NS_COLLECTIONS;
	const Collection::Namespace Collection::PLAYLISTS   = XMMS_COLLECTION_NS_PLAYLISTS;

	Collection::~Collection()
	{
		XmmsMessage &msg;
	}

	XmmsResult
	Collection::get (const QString &name, Namespace nsname) const
	{
	}

	XmmsResult
	Collection::list (Namespace nsname) const
	{
	}

	XmmsResult
	Collection::save (const Coll::Coll& coll, const QString &name,
	                  Namespace nsname) const
	{
	}

	XmmsResult
	Collection::remove (const QString &name, Namespace nsname) const
	{
	}

	XmmsResult
	Collection::find (quint32 id, Namespace nsname) const
	{
	}

	XmmsResult
	Collection::rename(const QString &from_name,
	                   const QString &to_name,
	                   Namespace nsname) const
	{
	}

	XmmsResult
	Collection::idlistFromPlaylistFile (const QString &path) const
	{
	}

	XmmsResult
	Collection::queryIds (const Coll::Coll& coll,
	                      const QStringList &order,
	                      quint32 limit_len,
	                      quint32 limit_start) const
	{
	}

	XmmsResult
	Collection::queryInfos (const Coll::Coll& coll,
	                        const QStringList &fetch,
	                        const QStringList &order,
	                        quint32 limit_len,
	                        quint32 limit_start,
	                        const QStringList &group
	                      ) const
	{
	}

	XmmsResult
	Collection::parse (const QString &pattern) const
	{
	}

	XmmsResult
	Collection::broadcastCollectionChanged () const
	{
	}

}
