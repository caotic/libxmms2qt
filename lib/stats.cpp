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

#include "stats.h"
#include "client.h"
#include <xmmsc/xmmsc_idnumbers.h>

namespace XMMSQt
{

	Result
	Stats::mainStats () const
	{
		Message msg (XMMS_IPC_OBJECT_MAIN, XMMS_IPC_CMD_STATS);

		return m_client->queueMsg (msg);
	}

	Result
	Stats::listPlugins (const xmms_plugin_type_t &type) const
	{
		Message msg (XMMS_IPC_OBJECT_MAIN, XMMS_IPC_CMD_PLUGIN_LIST);
		msg.add (type);

		return m_client->queueMsg (msg);
	}

	Result
	Stats::broadcastMediainfoReaderStatus () const
	{
		Message msg (XMMS_IPC_OBJECT_SIGNAL, XMMS_IPC_CMD_BROADCAST);
		msg.add (XMMS_IPC_SIGNAL_MEDIAINFO_READER_STATUS);

		return m_client->queueMsg (msg);
	}

	Result
	Stats::signalMediainfoReaderUnindexed () const
	{
		Message msg (XMMS_IPC_OBJECT_SIGNAL, XMMS_IPC_CMD_SIGNAL);
		msg.add (XMMS_IPC_SIGNAL_MEDIAINFO_READER_UNINDEXED);

		return m_client->queueMsg (msg);
	}

}
