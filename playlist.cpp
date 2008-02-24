#include "playlist.h"

#include "client.h"

XmmsResult
Playlist::currentPos (const QString &playlist)
{
	XmmsMessage msg (XMMS_IPC_OBJECT_PLAYLIST, XMMS_IPC_CMD_CURRENT_POS);
	msg.add (playlist);
	
	return m_client->queueMsg (msg);
}

XmmsResult
Playlist::list (const QString &playlist)
{
	XmmsMessage msg (XMMS_IPC_OBJECT_PLAYLIST, XMMS_IPC_CMD_LIST);
	msg.add (playlist);
	return m_client->queueMsg (msg);
}
