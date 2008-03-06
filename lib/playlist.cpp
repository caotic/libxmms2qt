#include "playlist.h"

#include "client.h"
#include "medialib.h"

#include <QUrl>

XmmsResult
Playlist::currentPos (const QString &playlist)
{
	XmmsMessage msg (XMMS_IPC_OBJECT_PLAYLIST, XMMS_IPC_CMD_CURRENT_POS);
	msg.add (playlist);
	
	return m_client->queueMsg (msg);
}

XmmsResult
Playlist::listEntries (const QString &playlist)
{
	XmmsMessage msg (XMMS_IPC_OBJECT_PLAYLIST, XMMS_IPC_CMD_LIST);
	msg.add (playlist);
	return m_client->queueMsg (msg);
}

XmmsResult
Playlist::add (const QString &url, const QString &playlist)
{
	return addEncoded (Medialib::encodeUrl (url), playlist);
}

XmmsResult
Playlist::add (const QUrl &url, const QString &playlist)
{
	return addEncoded (Medialib::encodeUrl (url.toString ()), playlist);
}

XmmsResult
Playlist::add (quint32 id, const QString &playlist)
{
	XmmsMessage msg (XMMS_IPC_OBJECT_PLAYLIST, XMMS_IPC_CMD_ADD_ID);
	msg.add (playlist);
	msg.add (id);
	return m_client->queueMsg (msg);
}

XmmsResult
Playlist::addEncoded (const QString &url, const QString &playlist)
{
	XmmsMessage msg (XMMS_IPC_OBJECT_PLAYLIST, XMMS_IPC_CMD_ADD_URL);
	msg.add (playlist);
	msg.add (url);
	return m_client->queueMsg (msg);	
}

XmmsResult
Playlist::shuffle (const QString &playlist)
{
	XmmsMessage msg (XMMS_IPC_OBJECT_PLAYLIST, XMMS_IPC_CMD_SHUFFLE);
	msg.add (playlist);
	return m_client->queueMsg (msg);	
}

XmmsResult
Playlist::remove (quint32 id, const QString &playlist)
{
	XmmsMessage msg (XMMS_IPC_OBJECT_PLAYLIST, XMMS_IPC_CMD_REMOVE_ENTRY);
	msg.add (playlist);
	msg.add (id);
	return m_client->queueMsg (msg);	
}


XmmsResult 
Playlist::clear (const QString &playlist)
{
	XmmsMessage msg (XMMS_IPC_OBJECT_PLAYLIST, XMMS_IPC_CMD_CLEAR);
	msg.add (playlist);
	return m_client->queueMsg (msg);	
}


XmmsResult
Playlist::setNext (quint32 pos)
{
	XmmsMessage msg (XMMS_IPC_OBJECT_PLAYLIST, XMMS_IPC_CMD_SET_POS);
	msg.add (pos);
	return m_client->queueMsg (msg);	
}

XmmsResult 
Playlist::setNextRel (quint32 pos)
{
	XmmsMessage msg (XMMS_IPC_OBJECT_PLAYLIST, XMMS_IPC_CMD_SET_POS_REL);
	msg.add (pos);
	return m_client->queueMsg (msg);	
}

XmmsResult
Playlist::move (quint32 opos, quint32 npos, const QString &playlist)
{
	XmmsMessage msg (XMMS_IPC_OBJECT_PLAYLIST, XMMS_IPC_CMD_MOVE_ENTRY);
	msg.add (playlist);
	msg.add (opos);
	msg.add (npos);
	return m_client->queueMsg (msg);	
}

XmmsResult
Playlist::recursiveAdd (const QString &url, const QString &playlist)
{
	XmmsMessage msg (XMMS_IPC_OBJECT_PLAYLIST, XMMS_IPC_CMD_RADD);
	msg.add (playlist);
	msg.add (Medialib::encodeUrl (url));
	return m_client->queueMsg (msg);	
}

XmmsResult
Playlist::activePlaylist () const
{
	XmmsMessage msg (XMMS_IPC_OBJECT_PLAYLIST, XMMS_IPC_CMD_CURRENT_ACTIVE);
	return m_client->queueMsg (msg);
}

XmmsResult
Playlist::loadPlaylist (const QString &name) const
{
	XmmsMessage msg (XMMS_IPC_OBJECT_PLAYLIST, XMMS_IPC_CMD_LOAD);
	msg.add (name);
	return m_client->queueMsg (msg);
}

XmmsResult
Playlist::broadcastPlaylistChanged ()
{
	XmmsMessage msg (XMMS_IPC_OBJECT_SIGNAL, XMMS_IPC_CMD_BROADCAST);
	msg.add (XMMS_IPC_SIGNAL_PLAYLIST_CHANGED);
	return m_client->queueMsg (msg);
}

XmmsResult
Playlist::broadcastPlaylistCurrentPos ()
{
	XmmsMessage msg (XMMS_IPC_OBJECT_SIGNAL, XMMS_IPC_CMD_BROADCAST);
	msg.add (XMMS_IPC_SIGNAL_PLAYLIST_CURRENT_POS);
	return m_client->queueMsg (msg);
}

XmmsResult
Playlist::broadcastPlaylistLoaded ()
{
	XmmsMessage msg (XMMS_IPC_OBJECT_SIGNAL, XMMS_IPC_CMD_BROADCAST);
	msg.add (XMMS_IPC_SIGNAL_PLAYLIST_LOADED);
	return m_client->queueMsg (msg);
}
