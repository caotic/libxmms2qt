
#include "result.h"
#include "client.h"
#include "playback.h"

#include <QMetaMethod>

XmmsResult::XmmsResult (XmmsClient *client, int cookie) : QObject ()
{
	m_cookie = cookie;
	m_object = NULL;
	m_slot = NULL;
	m_client = client;
	m_restartsignal = 0;
	m_broadcast = false;
}

void
XmmsResult::exec (const XmmsMessage &msg)
{
	m_message = msg;
		
	if (m_object && m_slot) {
		QByteArray sig (m_object->metaObject ()->normalizedSignature (m_slot).mid (1));
		DBGRES ("we have object and slot: %s, woot!", sig.constData ());

		qint32 methidx = m_object->metaObject ()->indexOfMethod (sig.constData ());
		if (methidx == -1) {
			qWarning ("the object doesn't have that slot!");
			qWarning ("Class %s has no slot '%s'",
			           m_object->metaObject ()->className (),
			           sig.constData ());
			return;
		}
		
		QMetaMethod meth = m_object->metaObject ()->method (methidx);

		const char *rettype = meth.typeName ();
		if (rettype != QLatin1String("bool")) {
			qWarning ("Wrong returntype: %s::%s must return 'bool'",
			m_object->metaObject ()->className (), sig.constData ());
		}


		QByteArray param;
		if (meth.parameterTypes ().size () > 0) {
			param = meth.parameterTypes ()[0];
		} else {
			param = "void";
		}

		sig = sig.left(sig.indexOf('('));
		bool ret;

		if (param == "void") {
			QMetaObject::invokeMethod (m_object, sig,
									   Q_RETURN_ARG (bool, ret));
		} else if (param == "quint32") {
			QMetaObject::invokeMethod (m_object, sig, 
									   Q_RETURN_ARG (bool, ret),
									   Q_ARG (quint32, m_message.getUInt32 ()));
		} else if (param == "QVariantList") {
			QMetaObject::invokeMethod (m_object, sig, 
									   Q_RETURN_ARG (bool, ret),
									   Q_ARG (QVariantList, m_message.getList ()));
		} else if (param == "PropDict") {
			QMetaObject::invokeMethod (m_object, sig,
									   Q_RETURN_ARG (bool, ret),
									   Q_ARG (PropDict, m_message.getDict ()));
		} else if (param == "QByteArray") {
			QMetaObject::invokeMethod (m_object, sig,
									   Q_RETURN_ARG (bool, ret),
									   Q_ARG (QByteArray, m_message.getBindata ()));
/*		} else if (param == "qint32") {
			arg = Q_ARG (qint32, )
		} else if (param == "QString") {
			arg = Q_ARG (QString, )*/
		} else if (param == "Playback::Status") {
			QMetaObject::invokeMethod (m_object, sig,
			                           Q_RETURN_ARG (bool, ret),
			                           Q_ARG (Playback::Status, (Playback::Status) m_message.getUInt32 ()));
		}
		
		if (m_broadcast && ret) {
			DBGRES ("restarting the broadcast");
			m_client->setResult (*this);
		}
		
		if (m_restartsignal && ret) {
			/* return value is true from the code, lets restart this signal */
			DBGRES ("going to restart signal %d", m_restartsignal);
			XmmsMessage msg (XMMS_IPC_OBJECT_SIGNAL, XMMS_IPC_CMD_SIGNAL);
			msg.add (m_restartsignal);
			XmmsResult r = m_client->queueMsg (msg, m_restartsignal);
			r (m_object, m_slot); /* set the same callback shit */
		}
		
	}
	
	DBGRES ("done with exec of result %d", m_cookie);
}

void
XmmsResult::operator() (QObject *object, const char *slot)
{
	m_object = object;
	m_slot = slot;
	m_client->setResult (*this);
}
