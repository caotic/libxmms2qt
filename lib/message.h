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

#ifndef __XMMS_MESSAGE_H__
#define __XMMS_MESSAGE_H__

#include <QDataStream>
#include <QVariant>
#include <QList>

#include "propdict.h"
#include "coll.h"

static const qint32 TYPE_UNDEFINED = -1;

namespace XMMSQt
{

	class Message {
	public:
		Message (quint32 object = 0, quint32 cmd = 0);
		~Message ()
		{
			delete m_stream;
		};

		Message (const Message &src) : m_bytearray (src.m_bytearray) {
			m_cookie = src.cookie ();
			m_length = src.m_length;
			m_headercomplete = src.m_headercomplete;
			m_stream = new QDataStream (m_bytearray);
		};

		Message & operator= (const Message &src)
		{
			m_cookie = src.cookie ();
			m_length = src.m_length;
			m_headercomplete = src.m_headercomplete;
			m_bytearray = src.m_bytearray;
			if (m_stream) {
				delete m_stream;
			}
			m_stream = new QDataStream (m_bytearray);
			return *this;
		};

		void add (qint32);
		void add (quint32);
		void add (qreal);
		void add (const QString &);
		void add (const QStringList &);
		void add (const QByteArray &);
		void add (const Coll::Coll &);

		void addData (const QByteArray &);

		quint32 getUInt32 ();
		qint32 getInt32 ();
		qreal getReal ();
		QString getString (const bool &checktype = true);
		QVariant getValue ();
		QVariantList getList (const bool &checktype = true);
		QVariantMap getDict (qint32 type = TYPE_UNDEFINED);
		PropDict getPropDict (qint32 type = TYPE_UNDEFINED);
		QByteArray getBindata ();
		Coll::Coll *getColl ();

		QByteArray finish (quint32 cookie) const;
		bool process (QIODevice *);
		bool processHeader (const QByteArray &);
		bool headerComplete () {
			return m_headercomplete;
		};

		quint32 cookie () const {
			return m_cookie;
		};

		quint32 fullLength () const {
			return m_length + 16; /* header is 16 */
		};

		QByteArray buf () const {
			return m_bytearray;
		};

		quint32 cmd () const {
			return m_cmd;
		};

		quint32 object () const {
			return m_object;
		};

	private:
		quint32 m_object;
		quint32 m_cmd;
		quint32 m_cookie;
		qint32 m_length;
		bool m_headercomplete;
		QByteArray m_bytearray;
		QByteArray m_readbuffer;

		QDataStream *m_stream;

	};

}

#endif
