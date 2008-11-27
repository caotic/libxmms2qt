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

#include "propdict.h"
#include "QtDebug"

namespace XMMSQt
{

	// The pre-rv-split serialisation
	PropDict::PropDict (const QVariantList& src) : QObject ()
	{
		initSourcePref ();

		// Test for number of elements
		if (src.size () % 3 != 0) {
			qDebug ("PropDict creation from QList failed:" \
			        " wrong number of elements");
			return;
		}

		int i = 0;
		while (i != src.size ()) {
			QString source = src.at (i++).toString ();
			QString key = src.at (i++).toString ();
			QVariant value = src.at (i++);
			add (key, value, source);
		}
	}

	void
	PropDict::add (const QString &key, const QVariant &val,
	               const QString &source)
	{
		QVariantMap sdict;
		if (m_prop.contains (key)) {
			sdict = m_prop[key].toMap ();
		}

		// If we get the request to add a QVarianMap we just ignore 'source'
		// and merge the new map into the one we already have for 'key'
		if (val.canConvert (QVariant::Map)) {
			QVariantMap v = val.toMap ();
			sdict.unite (v);
		} else {
			sdict[source] = val;
		}

		m_prop[key] = sdict;
	};

	QVariantMap
	PropDict::toDict () const
	{
		// TODO: Test this function
		QVariantMap ret;

		QVariantMap::const_iterator it = m_prop.constBegin ();
		while (it != m_prop.constEnd ()) {
			QVariant v = it.value ();
			// TODO: This should work for DrL. But for DrM and later, v might
			// be a plain value and no list. 
			if (v.canConvert (QVariant::Map)) {
				ret[it.key ()] = getBestValue (v.toMap ());
			} else {
				ret[it.key ()] = v;
			}
			++it;
		}
		return ret;
	}

	QVariant
	PropDict::operator[] (const QString &key) const
	{
		if (!m_prop.contains (key))
			return QVariant ();

		QVariant v = m_prop[key];
		if (v.canConvert (QVariant::Map)) {
			return getBestValue (v.toMap ());
		} else {
			return v;
		}
	}

	void
	PropDict::initSourcePref ()
	{
		m_source.append (QRegExp ("server"));
		m_source.append (QRegExp ("client/.*"));
		m_source.append (QRegExp ("plugin/id3v2"));
		m_source.append (QRegExp ("plugin/.*"));
		m_source.append (QRegExp (".*"));
	}

	QVariant
	PropDict::getBestValue (const QVariantMap &m) const
	{
		if (m.isEmpty ())
			return QVariant ();
		if (m.size () == 1)
			return m.values ().first ();

		int prio = m_source.size ();
		QVariant ret;

		QVariantMap::const_iterator it = m.constBegin ();
		while (it != m.constEnd ()) {
			// The earlier an entry is in m_source the higher it's priority
			// so we need only check the source preferences with index smaller
			// than our current best fitting value
			// If we don't match any source preference we return QVariant()
			for (int p=0; p < prio; p++) {
				if (m_source[p].exactMatch (it.key ())) {
					ret = it.value ();
					qDebug () << it.value ();
					prio = p;
				}
			}
			++it;
		}

		return ret;
	}
}
