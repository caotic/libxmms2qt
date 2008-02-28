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
		typedef xmms_playback_status_t Status;

		static const Status STOPPED = XMMS_PLAYBACK_STATUS_STOP;
		static const Status PLAYING = XMMS_PLAYBACK_STATUS_PLAY;
		static const Status PAUSED  = XMMS_PLAYBACK_STATUS_PAUSE;

		Playback (XmmsClient *client) : BaseObject (client)
		{
		};
	
		XmmsResult getPlaytime ();
		XmmsResult getCurrentId ();
		XmmsResult getStatus ();
		// Returns a Hash/Dict, which Result can't handle yet 
		XmmsResult getVolume ();

		XmmsResult signalPlaytime ();
		XmmsResult broadcastCurrentId ();
		XmmsResult broadcastStatus ();
		XmmsResult broadcastVolume ();

	public slots:
		XmmsResult start ();
		XmmsResult pause ();
		XmmsResult stop ();
		XmmsResult tickle ();

		XmmsResult seekMs (quint32 milliseconds);
		XmmsResult seekMsRel (qint32 milliseconds);

		XmmsResult setVolume (QString channel, quint32 volume);
};

#endif
