#include <QObject>
#include <QMap>
#include <QRegExp>
#include <QVariant>

#ifndef __PROPDICT_H__
#define __PROPDICT_H__


class PropDict : public QObject
{
	Q_OBJECT
	public:
		PropDict () : QObject ()
		{
			m_source.append (QRegExp ("server"));
			m_source.append (QRegExp ("client/.*"));
			m_source.append (QRegExp ("plugin/id3v2"));
			m_source.append (QRegExp ("plugin/.*"));
			m_source.append (QRegExp (".*"));
		};
		
		PropDict (const PropDict &src) : QObject (src.parent ())
		{
			m_source = src.m_source;
			m_prop = src.m_prop;
		};
		
		void setSource (const QList<QRegExp> &l)
		{
			m_source = l;
		};
		
		QList<QRegExp> getSource () const
		{
			return m_source;
		};
		
		void add (const QString &key, const QVariant &val, const QString &source = QString ())
		{
			QVariantList l;
			if (m_prop.contains (key)) {
				l = m_prop[key];
			}
			
			l.append (source);
			l.append (val);
			
			m_prop[key] = l;
		};
		
		QVariant operator[] (const QString &key) const
		{
			if (m_prop.contains (key)) {
				QVariantList l = m_prop[key];
				QVariant ret;
				qint32 lsrc = 0;
				for (int i = 0; i < l.size (); i ++)
				{
					QString source = l.at (i ++).toString ();
					QVariant value = l.at (i);

					if (lsrc != 0) {	
						for (int l = 0; l < m_source.size (); l ++)
						{
							if (m_source.at (l).indexIn (source)) {
								lsrc = l;
								ret = value;
								break;
							}
						}
					} else {
						lsrc = m_source.size ();
						ret = value;
					}
				}
				
				return ret;
			}
			
			return QVariant ();
		};
		
		PropDict& operator= (const PropDict &src)
		{
			m_prop = src.m_prop;
			m_source = src.m_source;
			return *this;
		};
		
		
		
	protected:
		QMap<QString, QVariantList> m_prop;
		QList<QRegExp> m_source;
	
};

#endif
