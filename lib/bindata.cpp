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

#include "bindata.h"
#include "client.h"

namespace XMMSQt
{

	Result
	Bindata::retrieve (const QString &hash)
	{
		Message msg (XMMS_IPC_OBJECT_BINDATA, XMMS_IPC_CMD_GET_DATA);
		msg.add (hash);
		return m_client->queueMsg (msg);
	}

	Result
	Bindata::add (const QByteArray &data)
	{
		Message msg (XMMS_IPC_OBJECT_BINDATA, XMMS_IPC_CMD_ADD_DATA);
		msg.add (data);

		return m_client->queueMsg (msg);
	}

	Result
	Bindata::remove (const QString &hash)
	{
		Message msg (XMMS_IPC_OBJECT_BINDATA, XMMS_IPC_CMD_REMOVE_DATA);
		msg.add (hash);

		return m_client->queueMsg (msg);
	}

	Result
	Bindata::list ()
	{
#if XMMS_IPC_PROTOCOL_VERSION >= 11
		Message msg (XMMS_IPC_OBJECT_BINDATA, XMMS_IPC_CMD_LIST_DATA);

		return m_client->queueMsg (msg);
#else
		return Result ("Listing Bindata is not supported on DrK");
#endif
	}

}
