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

#ifndef __STATS_H__
#define __STATS_H__

#include "object.h"
#include "result.h"

namespace XMMSQt
{

	/** @class Stats stats.h "FIXME: add filepath"
	 *  @brief This class is used to get various status information from the
	 *         server.
	 */
	class Stats : public BaseObject {
		public:
			Stats (Client *client) : BaseObject (client)
			{
			}

			Result mainStats () const;

			Result listPlugins (const xmms_plugin_type_t &type) const;

			Result broadcastMediainfoReaderStatus () const;
			Result signalMediainfoReaderUnindexed () const;
	};

}

#endif
