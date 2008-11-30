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


#include "cache.h"
#include "client.h"

#if 0
#include <QIcon>
#include <QPixmap>
#include <QHash>
#include <QList>
#include <QVariant>
#include <QPixmapCache>
#include <QSettings>
#endif

namespace XMMSQt
{


	Cache::Cache (Client *client) : QObject (client)
	{
		m_client = client;

//		QSettings s;
		connect (client, SIGNAL (connected (bool)),
		         this, SLOT (got_connection (bool)));
//		QPixmapCache::setCacheLimit (s.value ("core/pixmapcache",
//		                                       12040).toInt ());
	}


	void
	Cache::got_connection (bool connected)
	{
		if (!connected)
			return;

		m_client->medialib.broadcastEntryChanged () (this, SLOT (handle_mlib_entry_changed(quint32)));
		m_client->playback.signalPlaytime () (this, SLOT (handle_playtime (quint32)));
		m_client->playback.getPlaytime () (this, SLOT (handle_playtime (quint32)));
	}

	PropDict
	Cache::get_info (const quint32 &id)
	{
		if (!m_info.contains (id)) {
			m_client->medialib.info (id) (this, SLOT (handle_medialib_info (PropDict)));
// FIXME: To make error handling possible, the result class needs the ability to
//        provide custom parameters
//											 boost::bind (&XClientCache::handle_medialib_info_error, this, _1, id));
			m_info[id] = PropDict ();
		}

		return m_info[id];
	}

	bool
	Cache::handle_medialib_info (const PropDict &info)
	{
		qint32 id = info["id"].toInt ();

#if 0
		if (hash.contains ("picture_front")) {
			m_icon_map[hash["picture_front"].toString ()].append (id);
		}
#endif
		m_info.insert (id, info);
		emit entryChanged (id);

		return true;
	}

#if 0
	bool
	XClientCache::handle_medialib_info_error (const QString &error, quint32 id)
	{
		/* we probably couldn't find that entry, let's remove it */
		m_info.remove (id);
		emit entryRemoved (id);
		return true;
	}
#endif

	bool
	Cache::handle_mlib_entry_changed (const uint32_t &id)
	{
		m_client->medialib.info (id) (this, SLOT (handle_medialib_info (PropDict)));
		return true;
	}


#if 0
	void
	XClientCache::extra_info_set (uint32_t id, const QString &name,
								   const QVariant &value)
	{
		m_extra_info[id][name] = value;
	}

	QVariant
	XClientCache::extra_info_get (uint32_t id, const QString &name)
	{
		return m_extra_info[id][name];
	}

	bool
	XClientCache::handle_bindata (const Xmms::bin &data, const QString &id)
	{
		QPixmap i;
		i.loadFromData (data.c_str (), data.size());

		if (i.isNull ()) {
			return true;
		}

		/* conserve memory client side */
		if (i.width () < 300) {
			i = i.scaledToWidth (300, Qt::SmoothTransformation);
		}

		QPixmapCache::insert (id, i);

		QList<uint32_t> ids = m_icon_map[id];
		for (int i = 0; i < ids.size (); i++) {
			emit entryChanged (ids.at (i));
		}

		return true;
	}

	QIcon
	XClientCache::get_icon (uint32_t id)
	{
		return QIcon (get_pixmap (id));
	}

	QPixmap
	XClientCache::get_pixmap (uint32_t id)
	{
		if (m_info[id].contains ("picture_front")) {
			QString hash = m_info[id]["picture_front"].toString ();
			QPixmap p;

			if (!QPixmapCache::find (hash, p)) {
				m_client->bindata ()->retrieve (hash.toStdString ()) (
											boost::bind (&XClientCache::handle_bindata, this, _1, hash));
				QPixmapCache::insert (hash, QPixmap ());
			}
			
			return p;
		}
		return QPixmap (":images/noalbum.png");
	}


#endif
	bool
	Cache::handle_playtime (const quint32 &time)
	{
		emit playtime(time);
		return true;
	}

}
