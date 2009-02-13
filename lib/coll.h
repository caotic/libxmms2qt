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

#ifndef __XMMSCLIENTPP_COLL_H__
#define __XMMSCLIENTPP_COLL_H__

#include <xmmsc/xmmsc_idnumbers.h>

#include <QObject>
#include <QString>
#include <QMap>

#if XMMS_IPC_PROTOCOL_VERSION >= 13
#include <xmmsc/xmmsv_coll.h>
#else
#include <xmmsc/xmmsc_coll.h>
#endif

#include "typedefs.h"
#include "message.h"

namespace XMMSQt
{

	class Collection;
	class Playlist;
	class CollResult;

	/** @class Coll coll.h "xmmsclient/xmmsclient++/coll.h"
	 *  @brief This class is used to build collection structures.
	 */
	namespace Coll
	{

		typedef xmmsc_coll_type_t Type;

		const Type REFERENCE    = XMMS_COLLECTION_TYPE_REFERENCE;
		const Type UNION        = XMMS_COLLECTION_TYPE_UNION;
		const Type INTERSECTION = XMMS_COLLECTION_TYPE_INTERSECTION;
		const Type COMPLEMENT   = XMMS_COLLECTION_TYPE_COMPLEMENT;
		const Type HAS          = XMMS_COLLECTION_TYPE_HAS;
		const Type EQUALS       = XMMS_COLLECTION_TYPE_EQUALS;
		const Type MATCH        = XMMS_COLLECTION_TYPE_MATCH;
		const Type SMALLER      = XMMS_COLLECTION_TYPE_SMALLER;
		const Type GREATER      = XMMS_COLLECTION_TYPE_GREATER;
		const Type IDLIST       = XMMS_COLLECTION_TYPE_IDLIST;
		const Type QUEUE        = XMMS_COLLECTION_TYPE_QUEUE;
		const Type PARTYSHUFFLE = XMMS_COLLECTION_TYPE_PARTYSHUFFLE;

		class Coll
		{
			public:
				Coll (const Coll& src)
				{
					m_type = src.m_type;
					m_operands = src.m_operands;
					m_attributes = src.m_attributes;
					m_idlist = src.m_idlist;
				};

				/** Destructor.
				 */
				virtual ~Coll ();

				Type getType () const;

				// get/set attributes
				void setAttribute (const QString &attrname,
				                   const QString &value);
				QString getAttribute (const QString &attrname) const;
				void removeAttribute (const QString &attrname);
				QStringList getAttributeList () const;
				QList<quint32> getIdList () const;
				QList<Coll *> getOperandList () const;
				Coll operator= (const Coll& src)
				{
					m_type = src.m_type;
					m_operands = src.m_operands;
					m_attributes = src.m_attributes;
					m_idlist = src.m_idlist;
					return *this;
				};

				virtual void addOperand (Coll *operand);
				virtual void removeOperand (Coll *operand);

				virtual void removeOperand ();
				virtual void setOperand (Coll *operand);

				virtual void append (quint32);
				virtual void insert (quint32, quint32);
				virtual void move (quint32 index,
				                   quint32 newindex);
				virtual void remove (quint32 index);
				virtual void clear ();

				virtual quint32 size () const;

			/** @cond */
			protected:
				friend class ::XMMSQt::Collection;
				friend class ::XMMSQt::Playlist;
				friend class ::XMMSQt::CollResult;
				friend class ::XMMSQt::Message;
				friend class Unary;
				friend class Nary;

				Coll (Type type);

				void setOperandList (const QList<Coll *> &lst)
				{
					m_operands = lst;
				};

				void setAttributeList (const QMap<QString, QString> &attr)
				{
					m_attributes = attr;
				};

				void setIdList (const QList<quint32> &lst)
				{
					m_idlist = lst;
				};

				void setIndex (quint32 index, quint32 value);
				unsigned int getIndex (quint32 index) const;

				QList<Coll *> m_operands;
				QMap<QString, QString> m_attributes;
				QList<quint32> m_idlist;
				Type m_type;

			/** @endcond */
		};


		class Nary : public Coll
		{
			public:
				// FIXME: support operator<< too ?
				void addOperand (Coll *operand);
				void removeOperand (Coll *operand);

			protected:
				Nary (Type type);
				~Nary ();
		};

		class Unary : public Coll
		{
			public:
				void setOperand (Coll *operand);
				void removeOperand ();

			protected:
				Unary (Type type);
				Unary (Type type, Coll& operand);
				~Unary();
		};

		// FIXME: support integer value too? depend on class?
		class Filter : public Unary
		{
			protected:
				Filter (Type type);
				Filter (Type type, Coll& operand);
				Filter (Type type, Coll& operand, const QString &field);
				Filter (Type type,
				        Coll& operand,
				        const QString &field,
				        const QString &value);
				Filter (Type type,
				        Coll& operand,
				        const QString &field,
				        const QString &value,
				        bool case_sensitive);
				~Filter ();
		};


		class Reference : public Coll
		{
			friend class ::XMMSQt::Collection;
			friend class ::XMMSQt::CollResult;

			public:
				// nsname is actually of type Collection::Namespace,
				// but we try to avoid a dependency hell here..
				Reference ();
				Reference (const QString &name,
				           const char* const &nsname);
				~Reference ();
		};


        /** A collection operator corresponding to all the media in
		 *  the medialib.
		 *
		 *  Used attributes: none.
		 *
		 *  Operand: none.
		 *
		 *  A Universe operator is used to refer to the "All Media"
		 *  meta-collection that represents all the media in the
		 *  medialib.  Useful as input for other operators.
		 */
		class Universe : public Reference
		{
			public:
				Universe ();
				~Universe ();
		};


        /** A Union collection operator forms the union of multiple
		 *  operators.
		 *
		 *  Used attributes: none.
		 *
		 *  Operand: unbounded.
		 *
		 *  The collection produced by a Union operator is the union
		 *  of all its operands, i.e. all the media matching
		 *  <em>any</em> of the collection operands.
		 */
		class Union : public Nary
		{
			friend class ::XMMSQt::Collection;
			friend class ::XMMSQt::CollResult;

			public:
				Union ();
				~Union ();
		};


        /** An Intersection collection operator forms the intersection
		 *  of multiple operators.
		 *
		 *  Used attributes: none.
		 *
		 *  Operand: unbounded.
		 *
		 *  The collection produced by an Intersection operator is the
		 *  intersection of all its operands, i.e. all the media
		 *  matching <em>all</em> the collection operands.
		 */
		class Intersection : public Nary
		{
			friend class ::XMMSQt::Collection;
			friend class ::XMMSQt::CollResult;

			public:
				Intersection ();
				~Intersection ();
		};


        /** A Complement collection operator forms the complement of
		 *  an operators.
		 *
		 *  Used attributes: none.
		 *
		 *  Operand: 1.
		 *
		 *  The collection produced by an Intersection operator is the
		 *  complement of its unique operand, i.e. all the media
		 *  <em>not</em> matching the collection operand.
		 */
		class Complement : public Unary
		{
			friend class ::XMMSQt::Collection;
			friend class ::XMMSQt::CollResult;

			public:
				Complement ();
				Complement (Coll& operand);
				~Complement ();
		};

		class Has : public Filter
		{
			friend class ::XMMSQt::Collection;
			friend class ::XMMSQt::CollResult;

			public:
				Has ();
				Has (Coll& operand);
				Has (Coll& operand, const QString &field);
				~Has ();
		};

		class Smaller : public Filter
		{
			friend class ::XMMSQt::Collection;
			friend class ::XMMSQt::CollResult;

			public:
				Smaller ();
				Smaller (Coll& operand);
				Smaller (Coll& operand, const QString &field);
				Smaller (Coll& operand,
				        const QString &field,
				        const QString &value);
				~Smaller ();
		};

		class Greater : public Filter
		{
			friend class ::XMMSQt::Collection;
			friend class ::XMMSQt::CollResult;

			public:
				Greater ();
				Greater (Coll& operand);
				Greater (Coll& operand, const QString &field);
				Greater (Coll& operand,
				         const QString &field,
				         const QString &value);
				~Greater ();
		};

		class Equals : public Filter
		{
			friend class ::XMMSQt::Collection;
			friend class ::XMMSQt::CollResult;

			public:
				Equals ();
				Equals (Coll& operand);
				Equals (Coll& operand, const QString &field);
				Equals (Coll& operand,
				        const QString &field,
				        const QString &value,
				        bool case_sensitive = false);
				~Equals ();
		};

		class Match : public Filter
		{
			friend class ::XMMSQt::Collection;
			friend class ::XMMSQt::CollResult;

			public:
				Match ();
				Match (Coll& operand);
				Match (Coll& operand, const QString &field);
				Match (Coll& operand,
				       const QString &field,
				       const QString &value,
				       bool case_sensitive = false);
				~Match ();
		};


        /** An Idlist collection operator.
		 *
		 *  Used attributes: none.
		 *
		 *  Operand: none.
		 *
		 *  The Idlist operator stores a fixed list of media id.  The
		 *  list is ordered, and that ordering is used if the operator
		 *  is used as a playlist.
		 *
		 *  The Idlist operator also unmasks the methods related to
		 *  managing the internal id-list, as well as the [] bracket
		 *  operator with integer argument for direct access.
		 */
		class Idlist : public Coll
		{
			friend class ::XMMSQt::Collection;
			friend class ::XMMSQt::CollResult;

			protected:
				Idlist (Type type);

			public:
				Idlist ();
				~Idlist ();

				void append (quint32);
				void insert (quint32 id, quint32 index);
				void move (quint32 index, quint32 newindex);
				void remove (quint32 index);
				void clear ();

				quint32 size () const;
		};


        /** A Queue collection operator.
		 *
		 *  Used attributes:
		 *  - history: if used as a playlist, determines how many
		 *             played items remain before they are popped
		 *             off the queue.
		 *
		 *  Operand: none.
		 *
		 *  The Queue operator is similar to the Idlist operator,
		 *  except if loaded as a playlist, only <em>history</em>
		 *  played items will remain and the previous ones are
		 *  removed.
		 */
		class Queue : public Idlist
		{
			friend class ::XMMSQt::Collection;
			friend class ::XMMSQt::CollResult;

			protected:
				Queue (Type type);
				Queue (Type type, quint32 history);

			public:
				Queue ();
				Queue (quint32 history);
				~Queue ();
		};


        /** A PartyShuffle collection operator.
		 *
		 *  Used attributes:
		 *  - history: if used as a playlist, determines how many
		 *             played items remain before they are popped
		 *             off the queue.
		 *  - upcoming: if used as a playlist, determines the minimum
		 *              number of incoming entries (if fewer, new entries
		 *              are randomly fetched from the operand collection).
		 * - jumplist: optionally, the name of a playlist to jump to
         *             once the PartyShuffle is done playing.
		 *
		 *  Operand: 1, the input collection to randomly fetch media from.
		 *
		 *  The PartyShuffle operator is similar to the Queue operator
		 *  (entries are popped if they exceed <em>history</em>), but
		 *  when loaded, the playlist is automatically fed by random
		 *  media taken from the input collection until its size reaches
		 */
		class PartyShuffle : public Queue
		{
			friend class ::XMMSQt::Collection;
			friend class ::XMMSQt::CollResult;

			public:
				PartyShuffle ();
				PartyShuffle (quint32 history);
				PartyShuffle (quint32 history, quint32 upcoming);
				~PartyShuffle ();

				void setOperand (Coll *operand);
				void removeOperand ();
		};
	}
}

#endif // XMMSCLIENTPP_COLL_H
