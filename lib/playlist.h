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
			Playlist (XmmsClient *client) : BaseObject (client)
			{
			};
			
			XmmsResult currentPos (const QString &pl = "_active");
			XmmsResult listEntries (const QString &pl = "_active");
			XmmsResult add (const QString &url, const QString &pl = "_active");
			XmmsResult add (const QUrl &url, const QString &pl = "_active");
			XmmsResult add (quint32 id, const QString &pl = "_active");
			XmmsResult addEncoded (const QString &url, const QString &pl = "_active");
			XmmsResult shuffle (const QString &playlist = "_active");
			XmmsResult remove (quint32 id, const QString &playlist = "_active");
			XmmsResult clear (const QString &playlist = "_active");
			XmmsResult setNext (quint32 pos);
			XmmsResult setNextRel (quint32 pos);
			XmmsResult move (quint32 opos, quint32 npos, const QString &playlist = "_active");
			XmmsResult recursiveAdd (const QString &url, const QString &playlist = "_active");

			XmmsResult activePlaylist () const;
			XmmsResult loadPlaylist (const QString &name) const;

			XmmsResult broadcastPlaylistChanged ();
			XmmsResult broadcastPlaylistCurrentPos ();
			XmmsResult broadcastPlaylistLoaded ();
	};

}

#endif
