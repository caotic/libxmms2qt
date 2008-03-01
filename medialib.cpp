#include "medialib.h"

#include "client.h"

XmmsResult
Medialib::info (const quint32 &id)
{
	XmmsMessage msg (XMMS_IPC_OBJECT_MEDIALIB, XMMS_IPC_CMD_INFO);
	msg.add (id);
	
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
Medialib::encodeUrl (const QString &src)
{
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
