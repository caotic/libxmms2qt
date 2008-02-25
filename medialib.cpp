#include "medialib.h"

#include "client.h"

XmmsResult
Medialib::info (const quint32 &id)
{
	XmmsMessage msg (XMMS_IPC_OBJECT_MEDIALIB, XMMS_IPC_CMD_INFO);
	msg.add (id);
	
	return m_client->queueMsg (msg);
}
