#include <QObject>

#ifndef __PLAYBACK_H__
#define __PLAYBACK_H__

class Playback;

#include <QObject>
#include "object.h"
#include "result.h"

class Playback : public BaseObject
{
	Q_OBJECT
	public:
		Playback (XmmsClient *client) : BaseObject (client)
		{
		};
		
		XmmsResult signalPlaytime ();
		XmmsResult broadcastCurrentId ();

	public slots:
		XmmsResult start ();
		XmmsResult pause ();
		XmmsResult stop ();
};

#endif
