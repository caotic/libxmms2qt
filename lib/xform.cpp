#include "xform.h"
#include "client.h"
#include "medialib.h"

#include <QUrl>
#include <QString>

XmmsResult
Xform::browse (const QUrl &url) const
{
	return browseEncoded (Medialib::encodeUrl (url.toString ()));
}

XmmsResult
Xform::browse (const QString &url) const
{
	return browseEncoded (Medialib::encodeUrl (url));
}

XmmsResult
Xform::browseEncoded (const QString &url) const
{
	if (url.isEmpty ()) {
		// TODO better errorhandling
		qWarning ("Xform::browseEncoded called with empty argument");
		return XmmsResult ();
	}

	XmmsMessage msg (XMMS_IPC_OBJECT_XFORM, XMMS_IPC_CMD_BROWSE);
	msg.add (url);

	return m_client->queueMsg (msg);
}
