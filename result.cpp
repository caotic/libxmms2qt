
#include "result.h"
#include "client.h"

#include <QMetaMethod>

XmmsResult::XmmsResult (XmmsClient *client, int cookie) : QObject ()
{
	m_cookie = cookie;
	m_object = NULL;
	m_slot = NULL;
	m_client = client;
}

void
XmmsResult::exec (const XmmsMessage &msg)
{
	m_message = msg;
		
	if (m_object && m_slot) {
		QByteArray sig (m_object->metaObject ()->normalizedSignature (m_slot).mid (1));
		qDebug ("we have object and slot: %s, woot!", sig.constData ());

		qint32 methidx = m_object->metaObject ()->indexOfMethod (sig.constData ());
		if (methidx == -1) {
			qWarning ("the object doesn't have that slot!");
			return;
		}
		
		QMetaMethod meth = m_object->metaObject ()->method (methidx);
		QByteArray param = meth.parameterTypes ()[0];
		QGenericArgument arg;
		if (param == "quint32") {
			arg = Q_ARG (quint32, m_message.getUInt32 ());
		} else if (param == "QList<QVariant>") {
			QList<QVariant> l = m_message.getList ();
			arg = Q_ARG (QList<QVariant>, l);
/*		} else if (param == "qint32") {
			arg = Q_ARG (qint32, )
		} else if (param == "QString") {
			arg = Q_ARG (QString, )*/
		}
		
		sig = sig.left(sig.indexOf('('));
		bool ret;
		QMetaObject::invokeMethod (m_object, sig, 
								   Q_RETURN_ARG (bool, ret),
								   arg);
	}
	
	qDebug ("done with exec of result %d", m_cookie);
}

void
XmmsResult::operator() (QObject *object, const char *slot)
{
	m_object = object;
	m_slot = slot;
	m_client->setResult (*this);
}