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

#include "playlist.h"

#include "client.h"
#include "medialib.h"
#include "coll.h"
#include "collection.h"

#include <QUrl>

namespace XMMSQt
{

	Result
	Playlist::currentPos (const QString &playlist)
	{
		Message msg (XMMS_IPC_OBJECT_PLAYLIST, XMMS_IPC_CMD_CURRENT_POS);
		msg.add (playlist);

		return m_client->queueMsg (msg);
	}

	Result
	Playlist::listEntries (const QString &playlist)
	{
		Message msg (XMMS_IPC_OBJECT_PLAYLIST, XMMS_IPC_CMD_LIST);
		msg.add (playlist);
		return m_client->queueMsg (msg);
	}

	Result
	Playlist::add (const QString &url, const QString &playlist)
	{
		return addEncoded (Medialib::encodeUrl (url), playlist);
	}

	Result
	Playlist::add (const QUrl &url, const QString &playlist)
	{
		return addEncoded (Medialib::encodeUrl (url.toString ()), playlist);
	}

	Result
	Playlist::add (quint32 id, const QString &playlist)
	{
		Message msg (XMMS_IPC_OBJECT_PLAYLIST, XMMS_IPC_CMD_ADD_ID);
		msg.add (playlist);
		msg.add (id);
		return m_client->queueMsg (msg);
	}

	Result
	Playlist::add (const Coll::Idlist &list, const QString &playlist)
	{
#if XMMS_IPC_PROTOCOL_VERSION >= 11
		Message msg (XMMS_IPC_OBJECT_PLAYLIST, XMMS_IPC_CMD_ADD_IDLIST);
		msg.add (playlist);
		msg.add (list);
		return m_client->queueMsg (msg);
#else
		// TODO:Think of something for DrK
		return Result ("Playlist::add (Coll::Idlist, QString) not supported on DrK");
#endif
	}

	Result
	Playlist::add (const Coll::Coll &coll, const QStringList &order,
	               const QString &playlist)
	{
		Message msg (XMMS_IPC_OBJECT_PLAYLIST, XMMS_IPC_CMD_ADD_COLL);
		msg.add (playlist);
		msg.add (coll);
		msg.add (order);
		return m_client->queueMsg (msg);
	}

	Result
	Playlist::addEncoded (const QString &url, const QString &playlist)
	{
		Message msg (XMMS_IPC_OBJECT_PLAYLIST, XMMS_IPC_CMD_ADD_URL);
		msg.add (playlist);
		msg.add (url);
		return m_client->queueMsg (msg);
	}

	Result
	Playlist::insert (const QString &url, quint32 pos, const QString &playlist)
	{
		return insertEncoded (Medialib::encodeUrl (url), pos, playlist);
	}

	Result
	Playlist::insert (const QUrl &url, quint32 pos, const QString &playlist)
	{
		return insertEncoded (Medialib::encodeUrl (url.toString ()), pos,
		                      playlist);
	}

	Result
	Playlist::insert (quint32 id, quint32 pos, const QString &playlist)
	{
		Message msg (XMMS_IPC_OBJECT_PLAYLIST, XMMS_IPC_CMD_INSERT_ID);
		msg.add (playlist);
		msg.add (pos);
		msg.add (id);
		return m_client->queueMsg (msg);
	}

	Result
	Playlist::insert (const Coll::Coll &coll, quint32 pos,
	                  const QStringList &order,
	                  const QString &playlist)
	{
		 Message msg (XMMS_IPC_OBJECT_PLAYLIST, XMMS_IPC_CMD_INSERT_COLL);
		 msg.add (playlist);
		 msg.add (pos);
		 msg.add (coll);
		 msg.add (order);
		 return m_client->queueMsg (msg);
	}

	Result
	Playlist::insertEncoded (const QString &url, quint32 pos,
	                         const QString &playlist)
	{
		Message msg (XMMS_IPC_OBJECT_PLAYLIST, XMMS_IPC_CMD_INSERT_URL);
		msg.add (playlist);
		msg.add (pos);
		msg.add (url);
		return m_client->queueMsg (msg);
	}


	Result
	Playlist::shuffle (const QString &playlist)
	{
		Message msg (XMMS_IPC_OBJECT_PLAYLIST, XMMS_IPC_CMD_SHUFFLE);
		msg.add (playlist);
		return m_client->queueMsg (msg);
	}

	Result
	Playlist::remove (quint32 pos, const QString &playlist)
	{
		Message msg (XMMS_IPC_OBJECT_PLAYLIST, XMMS_IPC_CMD_REMOVE_ENTRY);
		msg.add (playlist);
		msg.add (pos);
		return m_client->queueMsg (msg);
	}


	Result
	Playlist::clear (const QString &playlist)
	{
		Message msg (XMMS_IPC_OBJECT_PLAYLIST, XMMS_IPC_CMD_CLEAR);
		msg.add (playlist);
		return m_client->queueMsg (msg);
	}


	Result
	Playlist::setNext (quint32 pos)
	{
		Message msg (XMMS_IPC_OBJECT_PLAYLIST, XMMS_IPC_CMD_SET_POS);
		msg.add (pos);
		return m_client->queueMsg (msg);
	}

	Result
	Playlist::setNextRel (qint32 pos)
	{
		Message msg (XMMS_IPC_OBJECT_PLAYLIST, XMMS_IPC_CMD_SET_POS_REL);
		msg.add (pos);
		return m_client->queueMsg (msg);
	}

	Result
	Playlist::move (quint32 opos, quint32 npos, const QString &playlist)
	{
		Message msg (XMMS_IPC_OBJECT_PLAYLIST, XMMS_IPC_CMD_MOVE_ENTRY);
		msg.add (playlist);
		msg.add (opos);
		msg.add (npos);
		return m_client->queueMsg (msg);
	}

	Result
	Playlist::recursiveAdd (const QString &url, const QString &playlist)
	{
		Message msg (XMMS_IPC_OBJECT_PLAYLIST, XMMS_IPC_CMD_RADD);
		msg.add (playlist);
		msg.add (Medialib::encodeUrl (url));
		return m_client->queueMsg (msg);
	}

	Result
	Playlist::activePlaylist () const
	{
		Message msg (XMMS_IPC_OBJECT_PLAYLIST, XMMS_IPC_CMD_CURRENT_ACTIVE);
		return m_client->queueMsg (msg);
	}

	Result
	Playlist::loadPlaylist (const QString &name) const
	{
		Message msg (XMMS_IPC_OBJECT_PLAYLIST, XMMS_IPC_CMD_LOAD);
		msg.add (name);
		return m_client->queueMsg (msg);
	}

	Result
	Playlist::createPlaylist (const QString &name) const
	{
		Coll::Coll plcoll (Coll::IDLIST);
		return m_client->collection.save (plcoll, name, Collection::PLAYLISTS);
	}

	Result
	Playlist::removePlaylist (const QString &name) const
	{
		return m_client->collection.remove (name, Collection::PLAYLISTS);
	}

	Result
	Playlist::renamePlaylist (const QString &oldname, const QString &newname) const
	{
		return m_client->collection.rename (oldname, newname,
		                                    Collection::PLAYLISTS);
	}

	Result
	Playlist::listPlaylists () const
	{
		return m_client->collection.list (Collection::PLAYLISTS);
	}


	Result
	Playlist::broadcastPlaylistChanged ()
	{
		Message msg (XMMS_IPC_OBJECT_SIGNAL, XMMS_IPC_CMD_BROADCAST);
		msg.add (XMMS_IPC_SIGNAL_PLAYLIST_CHANGED);
		return m_client->queueMsg (msg);
	}

	Result
	Playlist::broadcastPlaylistCurrentPos ()
	{
		Message msg (XMMS_IPC_OBJECT_SIGNAL, XMMS_IPC_CMD_BROADCAST);
		msg.add (XMMS_IPC_SIGNAL_PLAYLIST_CURRENT_POS);
		return m_client->queueMsg (msg);
	}

	Result
	Playlist::broadcastPlaylistLoaded ()
	{
		Message msg (XMMS_IPC_OBJECT_SIGNAL, XMMS_IPC_CMD_BROADCAST);
		msg.add (XMMS_IPC_SIGNAL_PLAYLIST_LOADED);
		return m_client->queueMsg (msg);
	}

}
