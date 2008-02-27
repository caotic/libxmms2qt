
#include "bindata.h"
#include "client.h"

XmmsResult
Bindata::retrieve (const QString &hash)
{
	XmmsMessage msg (XMMS_IPC_OBJECT_BINDATA, XMMS_IPC_CMD_GET_DATA);
	msg.add (hash);
	return m_client->queueMsg (msg);
}
