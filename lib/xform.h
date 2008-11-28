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

#ifndef __XFORM_H__
#define __XFORM_H__

#include "object.h"
#include "result.h"

class QString;
class QUrl;

namespace XMMSQt
{

	/** @class Xform xform,h "FIXME:path"
	 *  @brief This class is used to browse the servers filesystem
	 */
	class Xform : public BaseObject
	{
		public:
			Xform (Client *client) : BaseObject (client)
			{
			}

			Result browse (const QUrl &url) const;
			Result browse (const QString &url) const;
			Result browseEncoded (const QString &url) const;
	};

}

#endif
