#ifndef __CONFIG_H__
#define __CONFIG_H__

class Config;
class XmmsClient;

class QString;

#include <QObject>
#include "object.h"
#include "result.h"

class Config : public BaseObject
{
	Q_OBJECT
	public:
		Config (XmmsClient *client) : BaseObject (client)
		{
		}

		XmmsResult getValue (QString key);

		XmmsResult listValues ();

		XmmsResult broadcastValueChanged();

	public slots:
		XmmsResult registerValue (QString name, QString defval);

		XmmsResult setValue (QString name, QString value);
};

#endif
