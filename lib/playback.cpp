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

#include "playback.h"
#include "client.h"

namespace XMMSQt
{

	Result
	Playback::getPlaytime ()
	{
		Message msg (XMMS_IPC_OBJECT_OUTPUT, XMMS_IPC_CMD_CPLAYTIME);

		return m_client->queueMsg (msg);
	}

	Result
	Playback::signalPlaytime ()
	{
		Message msg (XMMS_IPC_OBJECT_SIGNAL, XMMS_IPC_CMD_SIGNAL);
		msg.add (XMMS_IPC_SIGNAL_OUTPUT_PLAYTIME);
		return m_client->queueMsg (msg, XMMS_IPC_SIGNAL_OUTPUT_PLAYTIME);
	}

	Result
	Playback::getCurrentId ()
	{
		Message msg (XMMS_IPC_OBJECT_OUTPUT, XMMS_IPC_CMD_CURRENTID);

		return m_client->queueMsg (msg);
	}

	Result
	Playback::broadcastCurrentId ()
	{
		Message msg (XMMS_IPC_OBJECT_SIGNAL, XMMS_IPC_CMD_BROADCAST);
		msg.add (XMMS_IPC_SIGNAL_OUTPUT_CURRENTID);
		return m_client->queueMsg (msg);
	}

	Result
	Playback::getStatus ()
	{
		Message msg (XMMS_IPC_OBJECT_OUTPUT, XMMS_IPC_CMD_OUTPUT_STATUS);

		return m_client->queueMsg (msg);
	}

	Result
	Playback::broadcastStatus ()
	{
		Message msg (XMMS_IPC_OBJECT_SIGNAL, XMMS_IPC_CMD_BROADCAST);
		msg.add (XMMS_IPC_SIGNAL_PLAYBACK_STATUS);

		return m_client->queueMsg (msg);
	}

	Result
	Playback::getVolume ()
	{
		Message msg (XMMS_IPC_OBJECT_OUTPUT, XMMS_IPC_CMD_VOLUME_GET);

		return m_client->queueMsg (msg);
	}

	Result
	Playback::setVolume (QString channel, quint32 volume)
	{
		Message msg (XMMS_IPC_OBJECT_OUTPUT, XMMS_IPC_CMD_VOLUME_SET);
		msg.add (channel);
		msg.add (volume);

		return m_client->queueMsg (msg);
	}

	Result
	Playback::broadcastVolume ()
	{
		Message msg (XMMS_IPC_OBJECT_SIGNAL, XMMS_IPC_CMD_BROADCAST);
		msg.add (XMMS_IPC_SIGNAL_OUTPUT_VOLUME_CHANGED);

		return m_client->queueMsg (msg);
	}

	Result
	Playback::start ()
	{
		Message msg (XMMS_IPC_OBJECT_OUTPUT, XMMS_IPC_CMD_START);

		return m_client->queueMsg (msg);
	}

	Result
	Playback::pause ()
	{
		Message msg (XMMS_IPC_OBJECT_OUTPUT, XMMS_IPC_CMD_PAUSE);

		return m_client->queueMsg (msg);
	}

	Result
	Playback::stop ()
	{
		Message msg (XMMS_IPC_OBJECT_OUTPUT, XMMS_IPC_CMD_STOP);

		return m_client->queueMsg (msg);
	}

	Result
	Playback::tickle ()
	{
		Message msg (XMMS_IPC_OBJECT_OUTPUT, XMMS_IPC_CMD_DECODER_KILL);

		return m_client->queueMsg (msg);
	}

	Result
	Playback::seekMs (quint32 milliseconds)
	{
		Message msg (XMMS_IPC_OBJECT_OUTPUT, XMMS_IPC_CMD_SEEKMS);
		msg.add (milliseconds);

		return m_client->queueMsg (msg);

	}

	Result
	Playback::seekMsRel (qint32 milliseconds)
	{
		Message msg (XMMS_IPC_OBJECT_OUTPUT, XMMS_IPC_CMD_SEEKMS_REL);
		msg.add (milliseconds);

		return m_client->queueMsg (msg);
	}

	Result
	Playback::seekSamples (quint32 samples)
	{
		Message msg (XMMS_IPC_OBJECT_OUTPUT, XMMS_IPC_CMD_SEEKSAMPLES);
		msg.add (samples);

		return m_client->queueMsg (msg);
	}

	Result
	Playback::seekSamplesRel (qint32 samples)
	{
		Message msg (XMMS_IPC_OBJECT_OUTPUT, XMMS_IPC_CMD_SEEKSAMPLES_REL);
		msg.add (samples);

		return m_client->queueMsg (msg);
	}

}
