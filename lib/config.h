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

#ifndef __CONFIG_H__
#define __CONFIG_H__

class QString;

#include <QObject>
#include "object.h"
#include "result.h"

namespace XMMSQt
{

	class Config : public BaseObject
	{
		Q_OBJECT
		public:
			Config (Client *client) : BaseObject (client)
			{
			}

			Result getValue (QString key);

			Result listValues ();

			Result broadcastValueChanged ();

		public slots:
			Result registerValue (QString name, QString defval);

			Result setValue (QString name, QString value);
	};

}

#endif
