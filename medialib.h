#ifndef __MEDIALIB_H__
#define __MEDIALIB_H__

class Medialib;

#include <QObject>
#include "object.h"
#include "result.h"

class Medialib : public BaseObject
{
	public:
		Medialib (XmmsClient *client) : BaseObject (client)
		{
		};
		
		XmmsResult info (const quint32 &id);
};

#endif