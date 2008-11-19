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

#ifndef __XMMS_RESULT_H__
#define __XMMS_RESULT_H__

#include <QObject>
#include <QPointer>

#include "message.h"

#include "propdict.h"

#undef __DEBUG_RESULT__

#ifdef __DEBUG_RESULT__
#define DBGRES(fmt, ...) qDebug("DEBUG RESULT: " fmt, ## __VA_ARGS__)
#else
#define DBGRES(fmt, ...)
#endif

namespace XMMSQt
{

	class Client;

	class Result : public QObject
	{
		Q_OBJECT
		public:
			Result (const Result &src) : QObject (src.parent ())
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
				m_apierr = src.m_apierr;
			};

			Result (Client *, int cookie);

//			Result () : QObject () {};

			Result (QString apierr = "Wrong use of class Result");

			Result &
			operator= (const Result &src)
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
				m_apierr = src.m_apierr;
				return *this;
			};

			void operator() (QObject *object, const char *slot);
			void operator() (QObject *object, const char *slot,
			                 const char *errslot);
			void operator() (QObject *object, const char *slot,
			                 QObject *errobject, const char *errslot);

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

			Client *client () const {
				return m_client;
			};

			Message message () const {
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

			void exec (const Message &);

		private:
			int m_cookie;

			const char *m_slot;
			QPointer<QObject> m_object;

			const char *m_errslot;
			QPointer<QObject> m_errobject;

			Client *m_client;
			Message m_message;

			QString m_apierr;

			void setSlots (QObject *object, const char *slot,
			               QObject *errobject, const char *errslot);

		protected:
			quint32 m_restartsignal;
			bool m_broadcast;
	};

}

#endif
