/*  XMMS2 - X Music Multiplexer System
 *  Copyright (C) 2003-2008 XMMS2 Team
 *
 *  PLUGINS ARE NOT CONSIDERED TO BE DERIVED WORK !!!
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 */

#ifndef __PROPDICT_H__
#define __PROPDICT_H__

#include <QObject>
#include <QMap>
#include <QRegExp>
#include <QVariant>

namespace XMMSQt
{

	class PropDict : public QObject
	{
		public:
			PropDict () : QObject () {initSourcePref ();}

			PropDict (const PropDict &src) : QObject (src.parent ())
			{
				m_source = src.m_source;
				m_prop = src.m_prop;
			};

			PropDict (const QVariantMap& src) : QObject ()
			{
				initSourcePref ();
				// TODO: Make sure we really have a propdict
				m_prop = src;
			}

			// The pre-rv-split serialisation
			PropDict (const QVariantList& src);

			void setSource (const QList<QRegExp> &l)
			{
				if (l.size () == 0) {
					qDebug ("Propdict: empty source preference rejected");
					return;
				}
				m_source = l;
			};

			QList<QRegExp> getSource () const
			{
				return m_source;
			};

			void add (const QString &key, const QVariant &val,
			          const QString &source = QString ());

			QVariantMap toDict () const;

			QVariant operator[] (const QString &key) const;

			PropDict& operator= (const PropDict &src)
			{
				m_prop = src.m_prop;
				m_source = src.m_source;
				return *this;
			};


		protected:
			void initSourcePref ();
			QVariant getBestValue (const QVariantMap &) const;

			QVariantMap m_prop;
			QList<QRegExp> m_source;

	};

}

Q_DECLARE_METATYPE (XMMSQt::PropDict)

#endif
