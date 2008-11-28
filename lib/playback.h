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

#ifndef __PLAYBACK_H__
#define __PLAYBACK_H__

#include "object.h"
#include "result.h"

namespace XMMSQt
{

	class Playback : public BaseObject
	{
		Q_OBJECT
		public:
			typedef xmms_playback_status_t Status;

			static const Status STOPPED = XMMS_PLAYBACK_STATUS_STOP;
			static const Status PLAYING = XMMS_PLAYBACK_STATUS_PLAY;
			static const Status PAUSED  = XMMS_PLAYBACK_STATUS_PAUSE;

			Playback (Client *client) : BaseObject (client)
			{
			};

			Result getPlaytime ();
			Result getCurrentId ();
			Result getStatus ();
			Result getVolume ();

			Result signalPlaytime ();
			Result broadcastCurrentId ();
			Result broadcastStatus ();
			Result broadcastVolume ();

		public slots:
			Result start ();
			Result pause ();
			Result stop ();
			Result tickle ();

			Result seekMs (quint32 milliseconds);
			Result seekMsRel (qint32 milliseconds);

			Result seekSamples (quint32 samples);
			Result seekSamplesRel (qint32 samples);

			Result setVolume (QString channel, quint32 volume);
	};

}

#endif
