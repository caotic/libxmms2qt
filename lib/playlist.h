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

namespace XMMSQt
{

	class Playlist : public BaseObject
	{
		public:
			Playlist (Client *client) : BaseObject (client)
			{
			};
			
			Result currentPos (const QString &pl = "_active");
			Result listEntries (const QString &pl = "_active");
			Result add (const QString &url, const QString &pl = "_active");
			Result add (const QUrl &url, const QString &pl = "_active");
			Result add (quint32 id, const QString &pl = "_active");
			Result addEncoded (const QString &url, const QString &pl = "_active");
			Result shuffle (const QString &playlist = "_active");
			Result remove (quint32 id, const QString &playlist = "_active");
			Result clear (const QString &playlist = "_active");
			Result setNext (quint32 pos);
			Result setNextRel (quint32 pos);
			Result move (quint32 opos, quint32 npos, const QString &playlist = "_active");
			Result recursiveAdd (const QString &url, const QString &playlist = "_active");

			Result activePlaylist () const;
			Result loadPlaylist (const QString &name) const;

			Result broadcastPlaylistChanged ();
			Result broadcastPlaylistCurrentPos ();
			Result broadcastPlaylistLoaded ();
	};

}

#endif
