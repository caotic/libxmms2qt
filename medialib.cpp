#include "medialib.h"

#include "client.h"

#include <QString>
#include <QUrl>

XmmsResult
Medialib::add (const QUrl &url, const QStringList &args) const
{
	return addEncoded (encodeUrl (url.toString (), args));
}

XmmsResult
Medialib::add (const QString &url, const QStringList &args) const
{
	return addEncoded (encodeUrl (url, args));
}

XmmsResult
Medialib::addEncoded (const QString &url) const
{
	XmmsMessage msg (XMMS_IPC_OBJECT_MEDIALIB, XMMS_IPC_CMD_ADD_URL);
	msg.add (url);

	return m_client->queueMsg (msg);
}

XmmsResult
Medialib::addPath (const QUrl &path) const
{
	return addPathEncoded (encodeUrl (path.toString ()));
}

XmmsResult
Medialib::addPath (const QString &path) const
{
	return addPathEncoded (encodeUrl (path));
}

XmmsResult
Medialib::addPathEncoded (const QString &path) const
{
	XmmsMessage msg (XMMS_IPC_OBJECT_MEDIALIB, XMMS_IPC_CMD_PATH_IMPORT);
	msg.add (path);

	return m_client->queueMsg (msg);
}

XmmsResult
Medialib::info (const quint32 &id)
{
	XmmsMessage msg (XMMS_IPC_OBJECT_MEDIALIB, XMMS_IPC_CMD_INFO);
	msg.add (id);
	
	return m_client->queueMsg (msg);
}

XmmsResult
Medialib::rehash (quint32 id) const
{
	XmmsMessage msg (XMMS_IPC_OBJECT_MEDIALIB, XMMS_IPC_CMD_REHASH);
	msg.add (id);

	return m_client->queueMsg (msg);
}

XmmsResult
Medialib::remove (quint32 id) const
{
	XmmsMessage msg (XMMS_IPC_OBJECT_MEDIALIB, XMMS_IPC_CMD_REMOVE_ID);
	msg.add (id);

	return m_client->queueMsg (msg);
}

XmmsResult
Medialib::entryPropertySet (quint32 id, const QString &key,
                            const QString &value) const
{
	QString source = "client/" + m_client->name ();
	return entryPropertySet (id, key, value, source);
}

XmmsResult
Medialib::entryPropertySet (quint32 id, const QString &key,
                            const QString &value, const QString &source) const
{
	XmmsMessage msg (XMMS_IPC_OBJECT_MEDIALIB, XMMS_IPC_CMD_PROPERTY_SET_STR);
	msg.add (id);
	msg.add (source);
	msg.add (key);
	msg.add (value);

	return m_client->queueMsg (msg);
}

XmmsResult
Medialib::entryPropertySet (quint32 id, const QString &key, qint32 value) const
{
	QString source = "client/" + m_client->name ();
	return entryPropertySet (id, key, value, source);
}

XmmsResult
Medialib::entryPropertySet (quint32 id, const QString &key, qint32 value,
                             const QString &source) const
{
	XmmsMessage msg (XMMS_IPC_OBJECT_MEDIALIB, XMMS_IPC_CMD_PROPERTY_SET_INT);
	msg.add (id);
	msg.add (source);
	msg.add (key);
	msg.add (value);

	return m_client->queueMsg (msg);
}

XmmsResult
Medialib::entryPropertyRemove (quint32 id, const QString &key) const
{
	QString source = "client/" + m_client->name ();
	return entryPropertyRemove (id, key, source);
}

XmmsResult
Medialib::entryPropertyRemove (quint32 id, const QString &key,
                               const QString &source) const
{
	XmmsMessage msg (XMMS_IPC_OBJECT_MEDIALIB, XMMS_IPC_CMD_PROPERTY_REMOVE);
	msg.add (id);
	msg.add (source);
	msg.add (key);

	return m_client->queueMsg (msg);
}

XmmsResult
Medialib::broadcastEntryAdded ()
{
	XmmsMessage msg (XMMS_IPC_OBJECT_SIGNAL, XMMS_IPC_CMD_BROADCAST);
	msg.add (XMMS_IPC_SIGNAL_MEDIALIB_ENTRY_ADDED);

	return m_client->queueMsg (msg);
}

XmmsResult
Medialib::broadcastEntryChanged ()
{
	XmmsMessage msg (XMMS_IPC_OBJECT_SIGNAL, XMMS_IPC_CMD_BROADCAST);
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
