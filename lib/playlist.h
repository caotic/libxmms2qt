#ifndef __PLAYLIST_H__
#define __PLAYLIST_H__

class Playlist;

#include <QObject>
#include "object.h"
#include "result.h"

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

#endif
