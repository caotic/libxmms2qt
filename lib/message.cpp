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

#include "message.h"

#include <QFile>
#include <QStringList>
#include <qendian.h>

#include "propdict.h"
#include "client.h"
#include "result.h"

#include <xmmsc/xmmsc_idnumbers.h>

namespace XMMSQt
{

	XmmsMessage::XmmsMessage (quint32 object, quint32 cmd)
	{
		m_object = object;
		m_cmd = cmd;
		m_headercomplete = false;
		m_stream = new QDataStream (&m_bytearray, QIODevice::ReadWrite);
	}

	bool
	XmmsMessage::processHeader (const QByteArray &b)
	{
		
		if (b.size () != 16) {
			qWarning ("Didn't get 16 bytes from parent!");
			return false;
		}
			
		QDataStream r (b);
		if (!headerComplete ()) {
			r >> m_object;
			r >> m_cmd;
			r >> m_cookie;
			r >> m_length;
			m_headercomplete = true;
			DBGIPC ("header is complete! the message is %d", m_length);
			return true;
		}
		return false;
	}


	bool
	XmmsMessage::process (QIODevice *r)
	{	
		if (m_bytearray.size () < m_length) {
			int readsize = m_length - m_bytearray.size ();
			QByteArray b = r->read (readsize);
			DBGIPC ("read %d wanted %d", b.size (), readsize);
			m_bytearray += b;
		}
		
		if (m_bytearray.size () == m_length) {
	#ifdef __DEBUG_IPC_TO_FILE__
			QFile fp("/tmp/dbg");
			fp.open (QIODevice::WriteOnly);
			fp.write (m_bytearray);
			fp.close ();
	#endif
			return true;
		} else {
			return false;
		}
	}

	void
	XmmsMessage::add (quint32 value)
	{
		*m_stream << value;
	}

	void
	XmmsMessage::add (qint32 value)
	{
		*m_stream << value;
	}

	void
	XmmsMessage::add (const QString &value)
	{
		QByteArray b = value.toUtf8 ();
		/* for some reason our protocol want's us to send the NULL also */
		b.append ('\0');
		add (b.size ());
		m_stream->writeRawData (b.data (), b.size ());
	}

	void
	XmmsMessage::add (qreal value)
	{
		Q_UNUSED (value);
		qWarning ("Writing float to message, fixme!");
	//	m_stream.writeRawData (qToBigEndian (qreal, value), sizeof (qreal));
	}

	void
	XmmsMessage::add (const QStringList &list)
	{
		add (list.size ());
		for (int i = 0; i < list.size (); i ++)
		{
			add (list.at (i));
		}
	}

	void
	XmmsMessage::add (const QByteArray &value)
	{
		add(value.size ());
		m_stream->writeRawData(value.data (), value.size());
	}

	QByteArray
	XmmsMessage::finish (quint32 cookie) const
	{
		QByteArray retarray;
		QDataStream ret (&retarray, QIODevice::WriteOnly);
		ret.setByteOrder (QDataStream::BigEndian);

		ret << m_object;
		ret << m_cmd;
		ret << cookie;
		ret << m_bytearray.size ();
		ret.writeRawData (m_bytearray.data (), m_bytearray.size ());

		return retarray;
	}

	QVariant
	XmmsMessage::getValue ()
	{
		qint32 type;
		*m_stream >> type;
		switch (type) {
			case XMMS_OBJECT_CMD_ARG_UINT32:
				quint32 ui;
				*m_stream >> ui;
				return QVariant (ui);
			case XMMS_OBJECT_CMD_ARG_INT32:
				qint32 i;
				*m_stream >> i;
				return QVariant (i);
			case XMMS_OBJECT_CMD_ARG_STRING:
				{
					QString s = getString (false);
					return QVariant (s);
				}
			default:
				qWarning ("XmmsMessage::getValue(): Type not handled: %u", type);
				return QVariant ();
		}
		return QVariant ();
	}

	quint32
	XmmsMessage::getUInt32 ()
	{
		qint32 type;
		*m_stream >> type;
		if (type != XMMS_OBJECT_CMD_ARG_UINT32) {
			qWarning ("wanted type %d but got %d", XMMS_OBJECT_CMD_ARG_UINT32, type);
			return 0;
		}
		quint32 r;
		*m_stream >> r;
		return r;
	}

	PropDict
	XmmsMessage::getDict ()
	{
		PropDict ret;
		
		qint32 type;
		*m_stream >> type;
		
		if (type == XMMS_OBJECT_CMD_ARG_DICT) {
			DBGRES ("'normal' dict found");
			// Dict and PropDict have different serialization forms
			quint32 size;
			*m_stream >> size;
			for (quint32 i = 0; i < size; i ++)
			{
				QString key = getString (false);
				QVariant value = getValue ();
				ret.add (key, value);
			}
			// The serialization of dict differs from the serialization of
			// PropDict and VariantList. Leaveing this code in here in case
			// that changes in the future
			/* QVariantList l = getList (false);
			for (int i = 0; i < l.size (); i ++)
			{
				QString key = l.at (i ++).toString ();
				QVariant value = l.at (i);
				ret.add (key, value);
			} */
		} else if (type == XMMS_OBJECT_CMD_ARG_PROPDICT) {
			DBGRES ("'prop' dict found");
			QVariantList l = getList (false);
			
			DBGRES ("list is %d", l.size ());
			for (int i = 0; i < l.size (); i ++)
			{
				QString source = l.at (i ++).toString ();
				QString key = l.at (i ++).toString ();
				QVariant value = l.at (i);
				ret.add (key, value, source);
			}
		}
		
		return ret;
	}

	QVariantList
	XmmsMessage::getList (const bool &checktype)
	{
		if (checktype) {
			qint32 type;
			*m_stream >> type;
			if (type != XMMS_OBJECT_CMD_ARG_LIST) {
				qWarning ("wanted type %d but got %d", XMMS_OBJECT_CMD_ARG_LIST, type);
				return QList<QVariant> ();
			}
		}
		
		qint32 size;
		*m_stream >> size;
		
		QVariantList ret;
		for (int i = 0; i < size; i ++)
		{
			ret.append (getValue ());
		}
		
		return ret;
	}

	qint32
	XmmsMessage::getInt32 ()
	{
		qint32 type;
		*m_stream >> type;
		if (type != XMMS_OBJECT_CMD_ARG_INT32) {
			qWarning ("wanted type %d but got %d", XMMS_OBJECT_CMD_ARG_INT32, type);
			return 0;
		}
		qint32 r;
		*m_stream >> r;
		return r;
	}

	qreal
	XmmsMessage::getReal ()
	{
		qWarning ("getting qReal, not supported");
		return 0;
	}

	QString
	XmmsMessage::getString (const bool &checktype)
	{
		if (checktype) {
			qint32 type;
			*m_stream >> type;
			if (type != XMMS_OBJECT_CMD_ARG_STRING) {
				qWarning ("wanted type %d but got %d", XMMS_OBJECT_CMD_ARG_STRING, type);
				return QString ();
			}
		}
		quint32 len;
		*m_stream >> len;
		if (len > fullLength ()) {
			qWarning ("broken lenght, wanted %d but we only have %d", len, fullLength ());
			return QByteArray ();
		}
		char *str = (char *) malloc (len + 1);
		m_stream->readRawData (str, len);
		QString r = QString::fromUtf8 (str);
		delete str;
		
		return r;
	}

	QByteArray
	XmmsMessage::getBindata ()
	{
		qint32 type;
		*m_stream >> type;
		if (type != XMMS_OBJECT_CMD_ARG_BIN) {
			qWarning ("wanted type %d but got %d", XMMS_OBJECT_CMD_ARG_BIN, type);
			return QByteArray ();
		}
		
		quint32 len;
		*m_stream >> len;
		if (len > fullLength ()) {
			qWarning ("broken lenght, wanted %d but we only have %d", len, fullLength ());
			return QByteArray ();
		}
		char *buf = (char *) malloc (len);
		m_stream->readRawData (buf, len);
		QByteArray r (buf, len);
		return r;
	}

}
