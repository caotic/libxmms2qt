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

#include "xform.h"
#include "client.h"
#include "medialib.h"

#include <QUrl>
#include <QString>

namespace XMMSQt
{

	Result
	Xform::browse (const QUrl &url) const
	{
		return browseEncoded (Medialib::encodeUrl (url.toString ()));
	}

	Result
	Xform::browse (const QString &url) const
	{
		return browseEncoded (Medialib::encodeUrl (url));
	}

	Result
	Xform::browseEncoded (const QString &url) const
	{
		if (url.isEmpty ()) {
			// TODO better errorhandling
			qWarning ("Xform::browseEncoded called with empty argument");
			return Result ();
		}

		Message msg (XMMS_IPC_OBJECT_XFORM, XMMS_IPC_CMD_BROWSE);
		msg.add (url);

		return m_client->queueMsg (msg);
	}

}
