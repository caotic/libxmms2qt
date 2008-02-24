#ifndef __OBJECT_H__
#define __OBJECT_H__

class BaseObject;

#include <QObject>
#include <xmmsc/xmmsc_idnumbers.h>

class XmmsClient;

class BaseObject : public QObject
{
	Q_OBJECT
	public:
		BaseObject (XmmsClient *client) : QObject ()
		{
			m_client = client;
		};
		
	protected:
		XmmsClient *m_client;
};

#endif