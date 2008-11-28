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

#ifndef __PLAYLIST_H__
#define __PLAYLIST_H__

#include <QObject>
#include "object.h"
#include "result.h"
#include "coll.h"

namespace XMMSQt
{

	/** @class Playlist playlist.h "FIXME:insert path"
	 *  @brief This class controls the playlist
	 */
	class Playlist : public BaseObject
	{
		public:
			Playlist (Client *client) : BaseObject (client)
			{
			};

			/** Get the current position in a playlist.
			 *
			 *  @param pl the playlist to consider (if omitted,
			 *            act on the current playlist)
			 *
			 *  @return QMap containing the name of the playlist as QString in
			 *               'name' and the current postition in that playlist
			 *                as unsigned integer in 'position'
			 */
			Result currentPos (const QString &pl = "_active");

			/** Get the entries in a playlist
			 *
			 *  @param pl the playlist to consider (if omitted,
			 *            act on the current playlist)
			 *
			 *  @return A QList of medialib IDs
			 */
			Result listEntries (const QString &pl = "_active");


			Result add (const QString &url, const QString &pl = "_active");
			Result add (const QUrl &url, const QString &pl = "_active");
			Result add (quint32 id, const QString &pl = "_active");
			// This method is not supported on DrK
			Result add (const Coll::Idlist &list,
			            const QString &pl = "_active");
			Result add (const Coll::Coll &coll, const QStringList &order,
			            const QString &pl = "_active");
			Result addEncoded (const QString &url,
			                   const QString &pl = "_active");


			Result insert (const QString &url, quint32 pos,
			               const QString &pl = "_active");
			Result insert (const QUrl &url, quint32 pos,
			               const QString &pl = "_active");
			Result insert (quint32 id, quint32 pos,
			               const QString &pl = "_active");
			Result insert (const Coll::Coll &coll, quint32 pos,
			               const QStringList &order,
			               const QString &pl = "_active");
			Result insertEncoded (const QString &url, quint32 pos,
			                      const QString &pl = "_active");


			/** Shuffles a playlist
			 *
			 *  @param playlist the playlist to modify (if omitted
			 *                  act on the current playlist)
			 */
			Result shuffle (const QString &playlist = "_active");

			/** Remove an entry from a playlist
			 *
			 *  @param pos The position that should be removed from the playlist
			 *  @param playlist The playlist to modify (if omitted,
			 *                  act on the current playlist)
			 */
			Result remove (quint32 pos, const QString &playlist = "_active");

			/** Remove all entries from a playlist
			 *
			 *  @paran playlist The playlist to modify (if omitted,
			 *                  act on the current playlist)
			 */
			Result clear (const QString &playlist = "_active");

			Result setNext (quint32 pos);
			Result setNextRel (qint32 pos);
			Result move (quint32 opos, quint32 npos,
			             const QString &playlist = "_active");
			Result recursiveAdd (const QString &url,
			                     const QString &playlist = "_active");


			/** Get the name of the currently active playlist
			 *
			 *  @return the name of the currently actibe playlist as a QString
			 */
			Result activePlaylist () const;

			/** Set a playlist from the medialib as active playlist
			 *
			 *  @param name The playlist to set as active playlist
			 */
			Result loadPlaylist (const QString &name) const;

			/** Create a new playlist in the medialib
			 *
			 *  @param name The name of the new playlist
			 */
			Result createPlaylist (const QString &name) const;

			/** Remove a playlist from the medialib
			 *  This only removes the playlist, the medialib entries will
			 *  not be changed
			 *
			 *  @param name The playlist that should be removed
			 */
			Result removePlaylist (const QString &name) const;

			/** Rename a playlist
			 *
			 *  @param oldname The name of a playlist in the medialib
			 *  @param newname The new name of the playlist
			 */
			Result renamePlaylist (const QString &oldname,
			                       const QString &newname) const;

			/** Get a list of the playlists in the medialib
			 *
			 *  @return QStringList containing the playlist names
			 */
			Result listPlaylists () const;

			Result broadcastPlaylistChanged ();
			Result broadcastPlaylistCurrentPos ();
			Result broadcastPlaylistLoaded ();
	};

}

#endif
