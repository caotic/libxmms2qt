#include "playback.h"
#include "client.h"

XmmsResult
Playback::signalPlaytime ()
{
	XmmsMessage msg (XMMS_IPC_OBJECT_SIGNAL, XMMS_IPC_CMD_SIGNAL);
	msg.add (XMMS_IPC_SIGNAL_OUTPUT_PLAYTIME);
	return m_client->queueMsg (msg, XMMS_IPC_SIGNAL_OUTPUT_PLAYTIME);
}

XmmsResult
Playback::broadcastCurrentId ()
{
	XmmsMessage msg (XMMS_IPC_OBJECT_SIGNAL, XMMS_IPC_CMD_BROADCAST);
	msg.add (XMMS_IPC_SIGNAL_OUTPUT_CURRENTID);
	return m_client->queueMsg (msg);
}

XmmsResult
Playback::start ()
{
	XmmsMessage msg (XMMS_IPC_OBJECT_OUTPUT, XMMS_IPC_CMD_START);

	return m_client->queueMsg (msg);
}

XmmsResult
Playback::pause ()
{
	XmmsMessage msg (XMMS_IPC_OBJECT_OUTPUT, XMMS_IPC_CMD_PAUSE);

	return m_client->queueMsg (msg);
}

XmmsResult
Playback::stop ()
{
	XmmsMessage msg (XMMS_IPC_OBJECT_OUTPUT, XMMS_IPC_CMD_STOP);

	return m_client->queueMsg (msg);
}
