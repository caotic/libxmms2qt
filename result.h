
#include <QObject>

#include "message.h"

#ifndef __XMMS_RESULT_H__
#define __XMMS_RESULT_H__

#include "propdict.h"

class XmmsClient;

class XmmsResult : public QObject
{
	Q_OBJECT
	public:
		XmmsResult (const XmmsResult &src) : QObject (src.parent ())
		{
			m_cookie = src.cookie ();
			m_object = src.object ();
			m_slot = src.slot ();
			m_client = src.client ();
			m_message = src.message ();
		};
		
		XmmsResult (XmmsClient *, int cookie);
		
		XmmsResult () : QObject () {};
		
		XmmsResult &
		operator= (const XmmsResult &src)
		{
			m_cookie = src.cookie ();
			m_object = src.object ();
			m_slot = src.slot ();
			m_client = src.client ();
			m_message = src.message ();
			return *this;
		};
		
		void operator() (QObject *object, const char *slot);

		int cookie () const { return m_cookie; };
		void setCookie (int c) {
			m_cookie = c;
		};
		
		const char *slot () const {
			return m_slot;
		};
		
		QObject *object () const {
			return m_object;
		};
		
		XmmsClient *client () const {
			return m_client;
		};
		
		XmmsMessage message () const {
			return m_message;
		};
		
		void exec (const XmmsMessage &);
		
	private:
		int m_cookie;
		const char *m_slot;
		QObject *m_object;
		XmmsClient *m_client;
		XmmsMessage m_message;
};

#endif
