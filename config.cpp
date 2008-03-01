#include "config.h"
#include "client.h"

#include <QString>

XmmsResult
Config::getValue (QString key)
{
	XmmsMessage msg (XMMS_IPC_OBJECT_CONFIG, XMMS_IPC_CMD_GETVALUE);
	msg.add (key);

	return m_client->queueMsg (msg);
}

XmmsResult
Config::setValue (QString key, QString value)
{
	XmmsMessage msg (XMMS_IPC_OBJECT_CONFIG, XMMS_IPC_CMD_SETVALUE);
	msg.add (key);
	msg.add (value);

	return m_client->queueMsg (msg);
}

XmmsResult
Config::registerValue (QString key, QString defval)
{
	XmmsMessage msg (XMMS_IPC_OBJECT_CONFIG, XMMS_IPC_CMD_REGVALUE);
	msg.add (key);
	msg.add (defval);

	return m_client->queueMsg (msg);
}

XmmsResult
Config::listValues ()
{
	XmmsMessage msg (XMMS_IPC_OBJECT_CONFIG, XMMS_IPC_CMD_LISTVALUES);

	return m_client->queueMsg (msg);
}

XmmsResult
Config::broadcastValueChanged ()
{
	XmmsMessage msg (XMMS_IPC_OBJECT_SIGNAL, XMMS_IPC_CMD_BROADCAST);
	msg.add (XMMS_IPC_SIGNAL_CONFIGVALUE_CHANGED);

	return m_client->queueMsg (msg);
}
