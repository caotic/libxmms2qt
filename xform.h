#ifndef __XFORM_H__
#define __XFORM_H__

class Xform;

#include "object.h"
#include "result.h"

class QString;
class QUrl;

class Xform : public BaseObject
{
	public:
		Xform (XmmsClient *client) : BaseObject (client)
		{
		}

		XmmsResult browse (const QUrl &url) const;
		XmmsResult browse (const QString &url) const;
		XmmsResult browseEncoded (const QString &url) const;
};

#endif
