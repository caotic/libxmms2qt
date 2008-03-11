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

#include "config.h"
#include "client.h"

#include <QString>

namespace XMMSQt
{

	XmmsResult
	Config::getValue (QString key)
	{
		XmmsMessage msg (XMMS_IPC_OBJECT_CONFIG, XMMS_IPC_CMD_GETVALUE);
		msg.add (key);

		return m_client->queueMsg (msg);
	}

	XmmsResult
	Config::setValue (QString key, QString value)
	{
		XmmsMessage msg (XMMS_IPC_OBJECT_CONFIG, XMMS_IPC_CMD_SETVALUE);
		msg.add (key);
		msg.add (value);

		return m_client->queueMsg (msg);
	}

	XmmsResult
	Config::registerValue (QString key, QString defval)
	{
		XmmsMessage msg (XMMS_IPC_OBJECT_CONFIG, XMMS_IPC_CMD_REGVALUE);
		msg.add (key);
		msg.add (defval);

		return m_client->queueMsg (msg);
	}

	XmmsResult
	Config::listValues ()
	{
		XmmsMessage msg (XMMS_IPC_OBJECT_CONFIG, XMMS_IPC_CMD_LISTVALUES);

		return m_client->queueMsg (msg);
	}

	XmmsResult
	Config::broadcastValueChanged ()
	{
		XmmsMessage msg (XMMS_IPC_OBJECT_SIGNAL, XMMS_IPC_CMD_BROADCAST);
		msg.add (XMMS_IPC_SIGNAL_CONFIGVALUE_CHANGED);

		return m_client->queueMsg (msg);
	}

}
