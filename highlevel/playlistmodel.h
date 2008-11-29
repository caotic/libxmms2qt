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

#ifndef __PLAYLISTMODEL_H__
#define __PLAYLISTMODEL_H__

#include "client.h"

#include <QObject>

#include <QList>
#include <QVariant>
#include <QStandardItemModel>

//#include "script.h"


namespace XMMSQt {
	class PlaylistModelItem;

	class PlaylistModel : public QStandardItemModel
	{
		Q_OBJECT
		public:
			PlaylistModel (QObject *parent, Client *);
			QVariant data (const QModelIndex &, int role = Qt::DisplayRole) const;
			void updateItem (const QModelIndex &);

			enum Roles {
				CoverRole = Qt::UserRole,
				ExtraRole,
				MedialibIdRole,
				CurrentRole,
				ReadyRole
			};

		private slots:
			void gotConnection (bool);
			void entryChanged (quint32);

			bool handleList (const QVariantList &list);
			bool handleChange (const QVariantMap &chg);
			bool handlePlsLoaded (const QString &);
			bool handleCurrentPls (const QString &);
			bool handleUpdatePos (const QVariantMap &);
			// Compatibility to older xmms2d
			bool handleUpdatePos (const quint32 &);

			PlaylistModelItem *item (quint32 row);
			void cbGeneralSizeHint (const QSize &);
	//		void cbNewScript (bool);

		private:
			void setMetaData (PlaylistModelItem *, const QHash<QString,
							  QVariant> &);
			QList<PlaylistModelItem *> getItemById (quint32);


			QString m_name;
			Client *m_client;
			QModelIndex m_current_idx;
			QSize m_sizehint;
//			Script *m_script;
			bool m_has_script;
	};

	class PlaylistModelItem : public QStandardItem
	{
		public:
			PlaylistModelItem (quint32 id) : QStandardItem ()
			{
				setData (QVariant (id), PlaylistModel::MedialibIdRole);
				setData (QVariant (false), PlaylistModel::ReadyRole);
				setEditable (false);
			};

			quint32 id () const {
				return data (PlaylistModel::MedialibIdRole).toUInt ();
			};
	};

	}

#endif
