
#include "bindata.h"
#include "client.h"

XmmsResult
Bindata::retrieve (const QString &hash)
{
	XmmsMessage msg (XMMS_IPC_OBJECT_BINDATA, XMMS_IPC_CMD_GET_DATA);
	msg.add (hash);
	return m_client->queueMsg (msg);
}

XmmsResult
Bindata::add (const QByteArray &data)
{
	XmmsMessage msg (XMMS_IPC_OBJECT_BINDATA, XMMS_IPC_CMD_ADD_DATA);
	msg.add (data);

	return m_client->queueMsg (msg);
}

XmmsResult
Bindata::remove (const QString &hash)
{
	XmmsMessage msg (XMMS_IPC_OBJECT_BINDATA, XMMS_IPC_CMD_REMOVE_DATA);
	msg.add (hash);

	return m_client->queueMsg (msg);
}

XmmsResult
Bindata::list ()
{
	XmmsMessage msg (XMMS_IPC_OBJECT_BINDATA, XMMS_IPC_CMD_LIST_DATA);
	
	return m_client->queueMsg (msg);
}
