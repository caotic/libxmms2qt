
#include <QObject>
#include <QPointer>

#include "message.h"

#ifndef __XMMS_RESULT_H__
#define __XMMS_RESULT_H__

#include "propdict.h"

#undef __DEBUG_RESULT__

#ifdef __DEBUG_RESULT__
#define DBGRES(fmt, ...) qDebug("DEBUG RESULT: " fmt, ## __VA_ARGS__)
#else
#define DBGRES(fmt, ...)
#endif

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
			m_errobject = src.m_errobject;
			m_errslot = src.m_errslot;
			m_client = src.client ();
			m_message = src.message ();
			m_restartsignal = src.m_restartsignal;
			m_broadcast = src.m_broadcast;
		};
		
		XmmsResult (XmmsClient *, int cookie);
		
		XmmsResult () : QObject () {};
		
		XmmsResult &
		operator= (const XmmsResult &src)
		{
			m_cookie = src.cookie ();
			m_object = src.object ();
			m_slot = src.slot ();
			m_errobject = src.m_errobject;
			m_errslot = src.m_errslot;
			m_client = src.client ();
			m_message = src.message ();
			m_restartsignal = src.m_restartsignal;
			m_broadcast = src.m_broadcast;
			return *this;
		};
		
		void operator() (QObject *object, const char *slot);
		void operator() (QObject *object, const char *slot, const char *errslot);
		void operator() (QObject *object, const char *slot, QObject *errobject, const char *errslot);

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
		
		void setRestartSignal (quint32 rsignal)
		{
			DBGRES ("got restart signal %d", rsignal);
			m_restartsignal = rsignal;
		};
		
		void setBroadcast (bool b)
		{
			m_broadcast = b;
		};
		
		void exec (const XmmsMessage &);
		
	private:
		int m_cookie;
		
		const char *m_slot;
		QPointer<QObject> m_object;

		const char *m_errslot;
		QPointer<QObject> m_errobject;

		XmmsClient *m_client;
		XmmsMessage m_message;
		
		void setSlots (QObject *object, const char *slot, QObject *errobject, const char *errslot);
		
	protected:
		quint32 m_restartsignal;
		bool m_broadcast;
};

#endif
