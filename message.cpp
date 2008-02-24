#include "message.h"

#include <QFile>
#include <QStringList>
#include <qendian.h>

#include <xmmsc/xmmsc_idnumbers.h>

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
		qDebug ("header is complete! the message is %d", m_length);
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
		qDebug ("read %d wanted %d", b.size (), readsize);
		m_bytearray += b;
	}
	
	if (m_bytearray.size () == m_length) {
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
			QString s;
			*m_stream >> s;
			return QVariant (s);
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

QVariantList
XmmsMessage::getList ()
{
	qint32 type;
	*m_stream >> type;
	if (type != XMMS_OBJECT_CMD_ARG_LIST) {
		qWarning ("wanted type %d but got %d", XMMS_OBJECT_CMD_ARG_LIST, type);
		return QList<QVariant> ();
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
XmmsMessage::getString ()
{
	qint32 type;
	*m_stream >> type;
	if (type != XMMS_OBJECT_CMD_ARG_STRING) {
		qWarning ("wanted type %d but got %d", XMMS_OBJECT_CMD_ARG_STRING, type);
		return QString ();
	}
	char *str;
	*m_stream >> str;
	QString r = QString::fromUtf8 (str);
	delete str;
	
	return r;
}