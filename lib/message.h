#include <QDataStream>
#include <QVariant>
#include <QList>

#ifndef __XMMS_MESSAGE_H__
#define __XMMS_MESSAGE_H__

#include "propdict.h"

class XmmsMessage {
public:
	XmmsMessage (quint32 object = 0, quint32 cmd = 0);
	~XmmsMessage ()
	{
		delete m_stream;
	};
		
	XmmsMessage (const XmmsMessage &src) : m_bytearray (src.m_bytearray) {
		m_cookie = src.cookie ();
		m_length = src.m_length;
		m_headercomplete = src.m_headercomplete;
		m_stream = new QDataStream (m_bytearray);
	};
	
	XmmsMessage & operator= (const XmmsMessage &src)
	{
		m_cookie = src.cookie ();
		m_length = src.m_length;
		m_headercomplete = src.m_headercomplete;
		m_bytearray = src.m_bytearray;
		if (m_stream) {
			delete m_stream;
		}
		m_stream = new QDataStream (m_bytearray);
		return *this;
	};
	
	void add (qint32);
	void add (quint32);
	void add (qreal);
	void add (const QString &);
	void add (const QStringList &);
	void add (const QByteArray &);

	void addData (const QByteArray &);
	
	quint32 getUInt32 ();
	qint32 getInt32 ();
	qreal getReal ();
	QString getString (const bool &checktype = true);
	QVariant getValue ();
	QVariantList getList (const bool &checktype = true);
	PropDict getDict ();
	QByteArray getBindata ();
	
	QByteArray finish (quint32 cookie) const;
	bool process (QIODevice *);
	bool processHeader (const QByteArray &);
	bool headerComplete () {
		return m_headercomplete;
	};
	
	quint32 cookie () const {
		return m_cookie;
	};
	
	quint32 fullLength () const {
		return m_length + 16; /* header is 16 */
	};
	
	QByteArray buf () const {
		return m_bytearray;
	};
	
	quint32 cmd () const {
		return m_cmd;
	};
	
	quint32 object () const {
		return m_object;
	};
	
private:
	quint32 m_object;
	quint32 m_cmd;
	quint32 m_cookie;
	qint32 m_length;
	bool m_headercomplete;
	QByteArray m_bytearray;
	QByteArray m_readbuffer;
	
	QDataStream *m_stream;
	
};

#endif
