/** 
 *  This file is a part of Esperanza, an XMMS2 Client.
 *
 *  Copyright (C) 2005-2007 XMMS2 Team
 *
 *  This program is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License
 *  as published by the Free Software Foundation; either version 2
 *  of the License, or (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 */


#ifndef __CACHE_H__
#define __CACHE_H__

namespace XMMSQt {
	class Cache;
}

#include "propdict.h"

#include <QObject>
#include <QHash>

#if 0
#include "client.h"

#include <QIcon>
#include <QPixmap>
#include <QHash>
#include <QList>
#include <QVariant>
#include <QPixmapCache>
#endif

namespace XMMSQt
{
	class Client;

	class Cache : public QObject
	{
		Q_OBJECT
		public:
			Cache (Client *);

			PropDict get_info (const quint32 &id);
/*
			QIcon get_icon (uint32_t id);
			QPixmap get_pixmap (uint32_t id);
			QVariant extra_info_get (uint32_t, const QString &);

			void extra_info_set (uint32_t, const QString &, const QVariant &);
*/
			void invalidate (const quint32 &id) {m_info.remove (id);}
			void invalidate_all () {m_info.clear ();}
/*
			bool extra_info_has (uint32_t id, const QString &s) {
				if (m_extra_info.contains (id))
					if (m_extra_info[id].contains (s))
						return true;
				return false;
			};

*/
		signals:
			void entryChanged (quint32);
			void entryRemoved (quint32);

			void playtime (quint32);

		protected slots:
			void got_connection (bool);

			bool handle_medialib_info (const PropDict &info);
//			bool handle_medialib_info_error (const QString &, quint32);
			bool handle_mlib_entry_changed (const quint32 &id);

			bool handle_playtime (const quint32 &);

		private:
/*

			bool handle_bindata (const Xmms::bin &, const QString &);

			bool handle_playtime (const unsigned int &tme);
*/
			QHash< quint32, PropDict > m_info;
/*
			QHash < QString, QList <uint32_t> > m_icon_map;
			QHash < int, QHash < QString, QVariant > > m_extra_info;

*/
			Client *m_client;

	};

}
#endif
