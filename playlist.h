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
		XmmsResult list (const QString &pl = "_active");
};

#endif