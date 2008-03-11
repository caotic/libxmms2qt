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

#include "medialib.h"

#include "client.h"

#include <QString>
#include <QUrl>

namespace XMMSQt
{

	Result
	Medialib::add (const QUrl &url, const QStringList &args) const
	{
		return addEncoded (encodeUrl (url.toString (), args));
	}

	Result
	Medialib::add (const QString &url, const QStringList &args) const
	{
		return addEncoded (encodeUrl (url, args));
	}

	Result
	Medialib::addEncoded (const QString &url) const
	{
		Message msg (XMMS_IPC_OBJECT_MEDIALIB, XMMS_IPC_CMD_ADD_URL);
		msg.add (url);

		return m_client->queueMsg (msg);
	}

	Result
	Medialib::addPath (const QUrl &path) const
	{
		return addPathEncoded (encodeUrl (path.toString ()));
	}

	Result
	Medialib::addPath (const QString &path) const
	{
		return addPathEncoded (encodeUrl (path));
	}

	Result
	Medialib::addPathEncoded (const QString &path) const
	{
		Message msg (XMMS_IPC_OBJECT_MEDIALIB, XMMS_IPC_CMD_PATH_IMPORT);
		msg.add (path);

		return m_client->queueMsg (msg);
	}

	Result
	Medialib::info (const quint32 &id)
	{
		Message msg (XMMS_IPC_OBJECT_MEDIALIB, XMMS_IPC_CMD_INFO);
		msg.add (id);

		return m_client->queueMsg (msg);
	}

	Result
	Medialib::id (const QUrl &url) const
	{
		return id (url.toString ());
	}

	Result
	Medialib::id (const QString &url) const
	{
		// TODO: Check if the server really wants an unencoded url
		// looking at the c lib it seems so
		Message msg (XMMS_IPC_OBJECT_MEDIALIB, XMMS_IPC_CMD_GET_ID);
		msg.add (url);

		return m_client->queueMsg (msg);
	}

	Result
	Medialib::rehash (quint32 id) const
	{
		Message msg (XMMS_IPC_OBJECT_MEDIALIB, XMMS_IPC_CMD_REHASH);
		msg.add (id);

		return m_client->queueMsg (msg);
	}

	Result
	Medialib::remove (quint32 id) const
	{
		Message msg (XMMS_IPC_OBJECT_MEDIALIB, XMMS_IPC_CMD_REMOVE_ID);
		msg.add (id);

		return m_client->queueMsg (msg);
	}

	Result
	Medialib::move (quint32 id, const QUrl &url) const
	{
		return move (id, url.toString ());
	}

	Result
	Medialib::move (quint32 id, const QString &url) const
	{
		Message msg (XMMS_IPC_OBJECT_MEDIALIB, XMMS_IPC_CMD_MOVE_URL);
		msg.add (id);
		msg.add (url);

		return m_client->queueMsg (msg);
	}

	Result
	Medialib::setEntryProperty (quint32 id, const QString &key,
								const QString &value) const
	{
		QString source = "client/" + m_client->name ();
		return setEntryProperty (id, key, value, source);
	}

	Result
	Medialib::setEntryProperty (quint32 id, const QString &key,
								const QString &value, const QString &source) const
	{
		Message msg (XMMS_IPC_OBJECT_MEDIALIB, XMMS_IPC_CMD_PROPERTY_SET_STR);
		msg.add (id);
		msg.add (source);
		msg.add (key);
		msg.add (value);

		return m_client->queueMsg (msg);
	}

	Result
	Medialib::setEntryProperty (quint32 id, const QString &key, qint32 value) const
	{
		QString source = "client/" + m_client->name ();
		return setEntryProperty (id, key, value, source);
	}

	Result
	Medialib::setEntryProperty (quint32 id, const QString &key, qint32 value,
								 const QString &source) const
	{
		Message msg (XMMS_IPC_OBJECT_MEDIALIB, XMMS_IPC_CMD_PROPERTY_SET_INT);
		msg.add (id);
		msg.add (source);
		msg.add (key);
		msg.add (value);

		return m_client->queueMsg (msg);
	}

	Result
	Medialib::removeEntryProperty (quint32 id, const QString &key) const
	{
		QString source = "client/" + m_client->name ();
		return removeEntryProperty (id, key, source);
	}

	Result
	Medialib::removeEntryProperty (quint32 id, const QString &key,
								   const QString &source) const
	{
		Message msg (XMMS_IPC_OBJECT_MEDIALIB, XMMS_IPC_CMD_PROPERTY_REMOVE);
		msg.add (id);
		msg.add (source);
		msg.add (key);

		return m_client->queueMsg (msg);
	}

	Result
	Medialib::broadcastEntryAdded ()
	{
		Message msg (XMMS_IPC_OBJECT_SIGNAL, XMMS_IPC_CMD_BROADCAST);
		msg.add (XMMS_IPC_SIGNAL_MEDIALIB_ENTRY_ADDED);

		return m_client->queueMsg (msg);
	}

	Result
	Medialib::broadcastEntryChanged ()
	{
		Message msg (XMMS_IPC_OBJECT_SIGNAL, XMMS_IPC_CMD_BROADCAST);
		msg.add (XMMS_IPC_SIGNAL_MEDIALIB_ENTRY_UPDATE);

		return m_client->queueMsg (msg);
	}

	#define GOODCHAR(a) ((((a) >= 'a') && ((a) <= 'z')) || \
						 (((a) >= 'A') && ((a) <= 'Z')) || \
						 (((a) >= '0') && ((a) <= '9')) || \
						 ((a) == ':') || \
						 ((a) == '/') || \
						 ((a) == '-') || \
						 ((a) == '.') || \
						 ((a) == '_'))

	/* TODO: need to add support for arguments here */
	QString
	Medialib::encodeUrl (const QString &src, const QStringList &args)
	{
		if (args.size () > 0) {
			qDebug ("Medialib: Sorry adding files with arguments is not supported yet");
		}

		QString ret;
		static const char hex[17] = "0123456789abcdef";

		for (int i = 0; i < src.size (); i ++)
		{
			char chr = src.at (i).toLatin1 ();
			if (GOODCHAR (chr)) {
				ret += chr;
			} else if (chr == ' ') {
				ret += '+';
			} else {
				ret += '%';
				ret += hex[((chr & 0xf0) >> 4)];
				ret += hex[(chr & 0x0f)];
			}
		}

		return ret;
	}

}
