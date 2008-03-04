#ifndef __STATS_H__
#define __STATS_H__

class Stats;

#include "object.h"
#include "result.h"
#include <xmmsc/xmmsc_idnumbers.h>

class Stats : public BaseObject {
	public:
		Stats (XmmsClient *client) : BaseObject (client)
		{
		}

		XmmsResult mainStats () const;

		XmmsResult listPlugins (const xmms_plugin_type_t &type) const;

		XmmsResult broadcastMediainfoReaderStatus () const;
		XmmsResult signalMediainfoReaderUnindexed () const;
};


#endif
