#include <QObject>

#ifndef __PLAYBACK_H__
#define __PLAYBACK_H__

class Playback;

#include <QObject>
#include "object.h"
#include "result.h"

class Playback : public BaseObject
{
	public:
		Playback (XmmsClient *client) : BaseObject (client)
		{
		};
		
		XmmsResult signalPlaytime ();
        XmmsResult broadcastCurrentId ();
};

#endif