#include "stats.h"
#include "client.h"

XmmsResult
Stats::mainStats () const
{
	XmmsMessage msg (XMMS_IPC_OBJECT_MAIN, XMMS_IPC_CMD_STATS);

	return m_client->queueMsg (msg);
}

XmmsResult
Stats::listPlugins (const xmms_plugin_type_t &type) const
{
	XmmsMessage msg (XMMS_IPC_OBJECT_MAIN, XMMS_IPC_CMD_PLUGIN_LIST);
	msg.add (type);

	return m_client->queueMsg (msg);
}

XmmsResult
Stats::broadcastMediainfoReaderStatus () const
{
	XmmsMessage msg (XMMS_IPC_OBJECT_SIGNAL, XMMS_IPC_CMD_BROADCAST);
	msg.add (XMMS_IPC_SIGNAL_MEDIAINFO_READER_STATUS);

	return m_client->queueMsg (msg);
}

XmmsResult
Stats::signalMediainfoReaderUnindexed () const
{
	XmmsMessage msg (XMMS_IPC_OBJECT_SIGNAL, XMMS_IPC_CMD_SIGNAL);
	msg.add (XMMS_IPC_SIGNAL_MEDIAINFO_READER_UNINDEXED);

	return m_client->queueMsg (msg);
}
