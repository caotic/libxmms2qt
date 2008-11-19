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

#include "client.h"
#include "collection.h"

namespace XMMSQt
{

	const Collection::Namespace Collection::ALL         = XMMS_COLLECTION_NS_ALL;
	const Collection::Namespace Collection::COLLECTIONS = XMMS_COLLECTION_NS_COLLECTIONS;
	const Collection::Namespace Collection::PLAYLISTS   = XMMS_COLLECTION_NS_PLAYLISTS;

	Collection::~Collection()
	{
	}

	Result
	Collection::get (const QString &name, Namespace nsname) const
	{
		Message msg (XMMS_IPC_OBJECT_COLLECTION, XMMS_IPC_CMD_COLLECTION_GET);
		msg.add (name);
		msg.add (QString (nsname));
		return m_client->queueMsg (msg);
	}

	Result
	Collection::list (Namespace nsname) const
	{
		Message msg (XMMS_IPC_OBJECT_COLLECTION, XMMS_IPC_CMD_COLLECTION_LIST);
		msg.add (QString (nsname));
		return m_client->queueMsg (msg);
	}

	Result
	Collection::save (const Coll::Coll& coll, const QString &name,
	                  Namespace nsname) const
	{
		Message msg (XMMS_IPC_OBJECT_COLLECTION, XMMS_IPC_CMD_COLLECTION_SAVE);
		msg.add (name);
		msg.add (QString (nsname));
		msg.add (coll);
		return m_client->queueMsg (msg);
	}

	Result
	Collection::remove (const QString &name, Namespace nsname) const
	{
		Message msg (XMMS_IPC_OBJECT_COLLECTION, XMMS_IPC_CMD_COLLECTION_REMOVE);
		msg.add (name);
		msg.add (QString (nsname));
		return m_client->queueMsg (msg);
	}

	Result
	Collection::find (quint32 id, Namespace nsname) const
	{
		Message msg (XMMS_IPC_OBJECT_COLLECTION, XMMS_IPC_CMD_COLLECTION_FIND);
		msg.add (id);
		msg.add (QString (nsname));
		return m_client->queueMsg (msg);
	}

	Result
	Collection::rename (const QString &from_name,
	                    const QString &to_name,
	                    Namespace nsname) const
	{
		Message msg (XMMS_IPC_OBJECT_COLLECTION,
		             XMMS_IPC_CMD_COLLECTION_RENAME);
		msg.add (from_name);
		msg.add (to_name);
		msg.add (QString (nsname));
		return m_client->queueMsg (msg);
	}

	Result
	Collection::idlistFromPlaylistFile (const QString &path) const
	{
		Message msg (XMMS_IPC_OBJECT_COLLECTION, XMMS_IPC_CMD_IDLIST_FROM_PLS);
		msg.add (path);
		return m_client->queueMsg (msg);
	}

	Result
	Collection::queryIds (const Coll::Coll& coll,
	                      const QStringList &order,
	                      quint32 limit_len,
	                      quint32 limit_start) const
	{
		Message msg (XMMS_IPC_OBJECT_COLLECTION, XMMS_IPC_CMD_QUERY_IDS);
		msg.add (coll);
		msg.add (limit_len);
		msg.add (limit_start);
		msg.add (order);
		return m_client->queueMsg (msg);
	}

	Result
	Collection::queryInfos (const Coll::Coll& coll,
	                        const QStringList &fetch,
	                        const QStringList &order,
	                        quint32 limit_len,
	                        quint32 limit_start,
	                        const QStringList &group
	                      ) const
	{
		Message msg (XMMS_IPC_OBJECT_COLLECTION, XMMS_IPC_CMD_QUERY_INFOS);
		msg.add (coll);
		msg.add (limit_start);
		msg.add (limit_len);
		msg.add (order);
		msg.add (fetch);
		msg.add (group);
		return m_client->queueMsg (msg);
	}

/*	Result
	Collection::parse (const QString &pattern) const
	{

	}*/

	Result
	Collection::broadcastCollectionChanged () const
	{
		Message msg (XMMS_IPC_OBJECT_SIGNAL, XMMS_IPC_CMD_BROADCAST);
		msg.add (XMMS_IPC_SIGNAL_COLLECTION_CHANGED);

		return m_client->queueMsg (msg);
	}

}
