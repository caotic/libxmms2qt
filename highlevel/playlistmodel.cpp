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

#include "playlistmodel.h"
#include "client.h"
#include "cache.h"

namespace XMMSQt
{

	PlaylistModel::PlaylistModel (QObject *parent, Client *client, Cache *cache)
		: QStandardItemModel (parent)
	{
		m_client = client;
		m_name = "_active";
		m_delegate = NULL;

		if (cache) {
			m_cache = cache;
		} else {
			m_cache = new Cache (m_client);
		}

		QStringList h (tr ("Playlist"));
		setHorizontalHeaderLabels (h);

		connect (client, SIGNAL (connected (bool)),
		         this, SLOT (gotConnection (bool)));
		connect (m_cache, SIGNAL (entryChanged (quint32)),
		         this, SLOT (entryChanged (quint32)));
		connect (parent, SIGNAL (pvGeneralSizeHint (const QSize &)),
		         this, SLOT (cbGeneralSizeHint (const QSize &)));

		//gotConnection (client);
//		m_script = new Script (this);
//		m_has_script = m_script->init ();

//		connect (m_script, SIGNAL (newScript (bool)),
//		         this, SLOT (cbNewScript (bool)));
	}

	/** XMMS2 connection */
	void
	PlaylistModel::gotConnection (bool b)
	{
		if (!b)
			return;

		m_client->playlist.activePlaylist () (this, SLOT (handleCurrentPls (QString)));
		m_client->playlist.listEntries (m_name) (this, SLOT (handleList (QVariantList)));

#if (XMMS_IPC_PROTOCOL_VERSION > 10)
		m_client->playlist.currentPos () (this, SLOT (handleUpdatePos (QVariantMap)));
		m_client->playlist.broadcastPlaylistCurrentPos () (this, SLOT (handleUpdatePos (QVariantMap)));
#else
		m_client->playlist.currentPos () (this, SLOT (handleUpdatePos (quint32)));
		m_client->playlist.broadcastPlaylistCurrentPos () (this, SLOT (handleUpdatePos (quint32)));
#endif

		m_client->playlist.broadcastPlaylistChanged () (this, SLOT (handleChange (QVariantMap)));
		m_client->playlist.broadcastPlaylistLoaded () (this, SLOT (handlePlsLoaded (QString)));
	}


	bool
	PlaylistModel::setDelegate (PlaylistModelDelegate *delegate)
	{
		// Only allow to set a delegate if none is set at the moment
		if (m_delegate)
			return false;

		m_delegate = delegate;
		return true;
	}

	PlaylistModelDelegate *
	PlaylistModel::delegate ()
	{
		return m_delegate;
	}

	void
	PlaylistModel::updateItem (const QModelIndex &idx)
	{
		emit dataChanged (idx, idx);
	}

#if 0
	void
	PlaylistModel::cbNewScript (bool ok)
	{
		m_has_script = ok;

		if (ok) {
			qDebug ("new script installed");
		}

		/* must be a better way to do this ... */
		for (int i = 0; i < rowCount (); i ++) {
			PlaylistModelItem *it = item (i);
			if (it->data (ReadyRole).toBool ()) {
				QHash<QString, QVariant> d = m_client->cache ()->get_info (it->id ());
				setMetaData (it, d);
			}
		}
	}
#endif

	void
	PlaylistModel::cbGeneralSizeHint (const QSize &s)
	{
		m_sizehint = s;
	}

	bool
	PlaylistModel::handleCurrentPls (const QString &name)
	{
		if (m_name == "_active") {
			m_name = name;
		}

		return true;
	}

	bool
	PlaylistModel::handleList (const QVariantList &list)
	{
		/* start by removing all data */
		clear ();

		int pos = 0;
		foreach (QVariant id, list) {
			PlaylistModelItem *entry = new PlaylistModelItem (id.toUInt ());
			setItem (pos, entry);
			pos ++;
		}
		return true;
	}

	bool
	PlaylistModel::handleChange (const QVariantMap &chg)
	{
		qint32 change = chg.value ("type").toInt ();
		qint32 pos = 0, npos = 0;
		quint32 id = 0;
		QString s;

		if (chg.contains ("position")) {
			pos = chg.value ("position").toInt ();
		}

		if (chg.contains ("id")) {
			id = chg.value ("id").toUInt ();
		}

		if (chg.contains ("name")) {
			s = chg.value ("name").toString ();
		}

		if (s != m_name) {
			return true;
		}

		QModelIndex idx = QModelIndex ();


		PlaylistModelItem *item;

		switch (change) {
			case XMMS_PLAYLIST_CHANGED_ADD:
				item = new PlaylistModelItem (id);
				appendRow (item);
				break;
			case XMMS_PLAYLIST_CHANGED_INSERT:
				item = new PlaylistModelItem (id);
				insertRow (pos, item);
				break;
			case XMMS_PLAYLIST_CHANGED_MOVE:
				npos = chg.value ("newposition").toInt ();

				item = dynamic_cast<PlaylistModelItem *> (takeRow (pos)[0]);
				insertRow (npos, item);

				//emit entryMoved (index (pos, 0), index (npos, 0));

				break;
			case XMMS_PLAYLIST_CHANGED_REMOVE:
				item = dynamic_cast<PlaylistModelItem *> (takeRow (pos)[0]);
//				m_client->cache ()->invalidate (item->id ());
				delete item;
				break;
			case XMMS_PLAYLIST_CHANGED_SHUFFLE:
			case XMMS_PLAYLIST_CHANGED_SORT:
			case XMMS_PLAYLIST_CHANGED_CLEAR:
//				m_client->cache ()->invalidate_all ();
				m_client->playlist.listEntries () (this, SLOT (handleList (QVariantList)));
				break;
		}

		return true;
	}

	bool
	PlaylistModel::handleUpdatePos (const QVariantMap &posdict)
	{
		QString changedPl = posdict.value ("name").toString ();
		if (changedPl == m_name) {
			quint32 pos = posdict.value ("position").toUInt ();
			return handleUpdatePos (pos);
		}
		return true;
	}

	// compatibility method for old xmms2d
	bool
	PlaylistModel::handleUpdatePos (const quint32 &pos)
	{
		PlaylistModelItem *it = item (pos);
		if (!it) {
			qDebug ("%d", pos);
			return true;
		}
		it->setData (QVariant (true), CurrentRole);
		return true;
	}

	bool
	PlaylistModel::handlePlsLoaded (const QString &name)
	{
		m_client->playlist.listEntries (name) (this, SLOT (handleList (QVariantList)));
		m_name = name;
		return true;
	}

	QVariant
	PlaylistModel::data (const QModelIndex &idx, int role) const
	{
		PlaylistModel *fake = const_cast<PlaylistModel*> (this);

		if (role == Qt::SizeHintRole) {
			QVariant ret;
			if (!m_sizehint.isValid ()) {
				return QVariant ();
			}
			return QVariant (m_sizehint);
		}

		if (role == Qt::DisplayRole && !QStandardItemModel::data (idx, ReadyRole).toBool ()) {
			PlaylistModelItem *it = fake->item (idx.row ());
			PropDict d = m_cache->get_info (it->id ());

			fake->setMetaData (it, d);
		}

		if (role == CoverRole) {
			qDebug ("cover role for %d", idx.row ());
#if 0
			QIcon ico = m_client->cache ()->get_icon (idx.data (MedialibIdRole).toUInt ());
#else
			QIcon ico;
#endif
			if (ico.isNull ()) {
				return QVariant ();
			}
			return QVariant (ico);
		}

		return QStandardItemModel::data (idx, role);
	}

	PlaylistModelItem *
	PlaylistModel::item (quint32 row)
	{
		PlaylistModelItem *ret = dynamic_cast<PlaylistModelItem *> (QStandardItemModel::item (row));
		return ret;
	}

	void
	PlaylistModel::setMetaData (PlaylistModelItem *it, const PropDict &data)
	{
		QString display;
		QString extras;

#if 0
		if (m_has_script) {
			display = m_script->entryFormat (data);
			extras = m_script->extrasFormat (data);
		}
#endif

		if (m_delegate) {
			display = m_delegate->formatEntry (data);
			extras = m_delegate->formatExtras (data);
		}

		if (display.isNull ()) {
			if (data.contains ("artist")) {
				display += data["artist"].toString ();
			} if (data.contains ("title")) {
				display += " - ";
				display += data["title"].toString ();
			}
		}

		if (extras.isNull ()) {
//			extras = "Edit playlist.js to add info here...";
			extras = "No extra info available...";
		}

		it->setData (QVariant (display), Qt::DisplayRole);
		it->setData (QVariant (extras), ExtraRole);
		it->setData (QVariant (true), ReadyRole);

		/* If I don't do this fulhack the View won't ask for CoverRole .... */
#if 0
		QIcon ico = m_client->cache ()->get_icon (it->id ());
#else
		QIcon ico;
#endif
		if (!ico.isNull ()) {
			it->setData (QVariant (true), CoverRole);
		}
	}

	void
	PlaylistModel::entryChanged (quint32 id)
	{
		qDebug ("%d changed", id);
		QList<PlaylistModelItem *> l = getItemById (id);
		PropDict d = m_cache->get_info (id);
		for (int i = 0; i < l.size (); i ++) {
			setMetaData (l.at (i), d);
		}
	}

	QList<PlaylistModelItem *>
	PlaylistModel::getItemById (quint32 id)
	{
		/* this function could be made a lot faster */
		QList<PlaylistModelItem *> ret;
		for (int i = 0; i < rowCount (); i ++) {
			PlaylistModelItem *it = item (i);
			if (it->id () == id) {
				ret.append (it);
			}
		}

		return ret;
	}

}
