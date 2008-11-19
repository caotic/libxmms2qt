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

#include "coll.h"
#include "collection.h"

namespace XMMSQt
{

	namespace Coll
	{

	Coll::Coll (Type type)
	{
		m_type = type;
	}

	Coll::~Coll ()
	{
		for (int i = 0; i < m_operands.size (); i++)
		{
			Coll *c = m_operands.takeFirst ();
			delete c;
		}
	}

	Type
	Coll::getType () const {
		return m_type;
	}

/*	AttributeElement
	Coll::operator[] (const QString &attrname)
	{
		return AttributeElement (*this, attrname);
	}

	const AttributeElement
	Coll::operator[] (const QString &attrname) const
	{
		return AttributeElement (*this, attrname);
	}*/

	void
	Coll::setAttribute (const QString &attrname, const QString &value)
	{
		m_attributes[attrname] = value;
	}

	QString
	Coll::getAttribute (const QString &attrname) const
	{
		return m_attributes[attrname];
	}

	QStringList
	Coll::getAttributeList () const
	{
		QStringList ret;
		QStringList keys = m_attributes.keys ();
		for (int i = 0; i < keys.size (); i++)
		{
			ret.append (keys[i]);
			ret.append (m_attributes[keys[i]]);
		}
		return ret;
	}

	QList<quint32>
	Coll::getIdList () const
	{
		return m_idlist;
	}

	QList<Coll *>
	Coll::getOperandList () const
	{
		return m_operands;
	}

	void
	Coll::removeAttribute (const QString &attrname)
	{
		m_attributes.take (attrname);
	}

	void
	Coll::setIndex (quint32 index, quint32 value)
	{
		m_idlist[index] = value;
	}

 	quint32
	Coll::getIndex (quint32 index) const
	{
		return m_idlist[index];
	}

	void
	Coll::addOperand (Coll *) {
		qWarning ("Wrong type!");
	}

	void
	Coll::removeOperand (Coll *) {
		qWarning ("Wrong type!");
	}

	void
	Coll::removeOperand () {
		qWarning ("Wrong type!");
	}

	void
	Coll::setOperand (Coll *) {
		qWarning ("Wrong type!");
	}

	void
	Coll::append (quint32) {
		qWarning ("Wrong type!");
	}

	void
	Coll::insert (quint32, quint32) {
		qWarning ("Wrong type!");
	}

	void
	Coll::move (quint32, quint32) {
		qWarning ("Wrong type!");
	}

	void
	Coll::remove (quint32) {
		qWarning ("Wrong type!");
	}

	void
	Coll::clear () {
		qWarning ("Wrong type!");
	}

 	quint32
	Coll::size () const {
		qWarning ("Wrong type!");
		return 0;
	}

/*	IdlistElement
	Coll::operator[] (quint32) {
		qWarning ("Wrong type!");
	}

	const IdlistElement
	Coll::operator[] (quint32) const {
		qWarning ("Wrong type!");
	}*/

	Nary::Nary (Type type)
		: Coll (type)
	{
	}

	Nary::~Nary ()
	{
	}

	void
	Nary::addOperand (Coll *operand)
	{
		m_operands.append (operand);
	}

	void
	Nary::removeOperand (Coll *operand)
	{
		m_operands.removeAll (operand);
	}


	Unary::Unary (Type type)
		: Coll (type)
	{
	}

	Unary::Unary (Type type, Coll& operand)
		: Coll (type)
	{
		setOperand (&operand);
	}

	Unary::~Unary ()
	{
	}

	void
	Unary::setOperand (Coll *operand)
	{
		removeOperand ();
		m_operands.append (operand);
	}

	void
	Unary::removeOperand ()
	{
		m_operands.clear ();
	}

	Filter::Filter (Type type) : Unary (type)
	{
	}

	Filter::Filter (Type type, Coll& operand) : Unary (type, operand)
	{
	}

	Filter::Filter (Type type, Coll& operand, const QString &field) : Unary (type, operand)
	{
		setAttribute ("field", field);
	}

	Filter::Filter (Type type,
	                Coll& operand,
	                const QString &field,
	                const QString &value) : Unary (type, operand)
	{
		setAttribute ("field", field);
		setAttribute ("value", value);
	}

	Filter::Filter (Type type,
	                Coll& operand,
	                const QString &field,
	                const QString &value,
	                bool case_sensitive) : Unary (type, operand)
	{
		setAttribute ("field", field);
		setAttribute ("value", value);
		if (case_sensitive) {
			setAttribute ("case-sensitive", "true");
		}
	}

	Filter::~Filter () {}

	Reference::Reference () : Coll (REFERENCE)
	{
	}

	Reference::Reference (const QString &name,
	                      const char* const &nsname) : Coll (REFERENCE)
	{
		setAttribute ("reference", name);
		setAttribute ("namespace", nsname);
	}

	Reference::~Reference ()
	{
	}

	Universe::Universe () : Reference ("All Media", Collection::COLLECTIONS) {}
	Universe::~Universe () {}

	Union::Union () : Nary (UNION) {}
	Union::~Union () {}

	Intersection::Intersection () : Nary (INTERSECTION) {}
	Intersection::~Intersection () {}

	Complement::Complement () : Unary (COMPLEMENT) {}
	Complement::Complement (Coll& operand) : Unary (COMPLEMENT, operand) {}
	Complement::~Complement () {}

	Has::Has () : Filter (HAS) {}
	Has::Has (Coll& operand) : Filter (HAS, operand) {}
	Has::Has (Coll& operand, const QString &field) : Filter(HAS, operand, field) {}
	Has::~Has () {}

	Smaller::Smaller () : Filter (SMALLER) {}
	Smaller::Smaller (Coll& operand) : Filter (SMALLER, operand) {}
	Smaller::Smaller (Coll& operand, const QString &field)
		: Filter (SMALLER, operand, field) {}
	Smaller::Smaller (Coll& operand,
	                  const QString &field,
	                  const QString &value)
		: Filter (SMALLER, operand, field, value) {}
	Smaller::~Smaller() {}

	Greater::Greater () : Filter (GREATER) {}
	Greater::Greater (Coll& operand) : Filter(GREATER, operand) {}
	Greater::Greater (Coll& operand, const QString &field)
		: Filter (GREATER, operand, field) {}
	Greater::Greater (Coll& operand,
	                  const QString &field,
	                  const QString &value)
		: Filter (GREATER, operand, field, value) {}
	Greater::~Greater() {}

	Equals::Equals () : Filter (EQUALS) {}
	Equals::Equals (Coll& operand) : Filter (EQUALS, operand) {}
	Equals::Equals (Coll& operand, const QString &field)
		: Filter (EQUALS, operand, field) {}
	Equals::Equals (Coll& operand,
	               const QString &field,
	               const QString &value,
	               bool case_sensitive)
		: Filter (EQUALS, operand, field, value, case_sensitive) {}
	Equals::~Equals () {}

	Match::Match () : Filter (MATCH) {}
	Match::Match (Coll& operand) : Filter (MATCH, operand) {}
	Match::Match (Coll& operand, const QString &field) : Filter (MATCH, operand, field) {}
	Match::Match (Coll& operand,
	              const QString &field,
	              const QString &value,
	              bool case_sensitive)
		: Filter (MATCH, operand, field, value, case_sensitive) {}
	Match::~Match () {}


	Idlist::Idlist (Type type) : Coll (type) {}
	Idlist::Idlist () : Coll (IDLIST) {}
	Idlist::~Idlist () {}

	Queue::Queue (Type type) : Idlist (type) {}
	Queue::Queue (Type type, quint32 history) : Idlist (type)
	{
		setAttribute ("history", QString::number (history));
	}
	Queue::Queue () : Idlist (QUEUE) {}
	Queue::Queue (quint32 history) : Idlist (QUEUE)
	{
		setAttribute ("history", QString::number (history));
	}
	Queue::~Queue () {}

	PartyShuffle::PartyShuffle () : Queue (PARTYSHUFFLE) {}
	PartyShuffle::PartyShuffle (quint32 history) : Queue (PARTYSHUFFLE, history) {}
	PartyShuffle::PartyShuffle (quint32 history, quint32 upcoming) : Queue (PARTYSHUFFLE, history)
	{
		setAttribute("upcoming", QString::number (upcoming));
	}
	PartyShuffle::~PartyShuffle () {}

	void
	Idlist::append (quint32 id)
	{
		m_idlist.append (id);
	}

	void
	Idlist::insert (quint32 index, quint32 id)
	{
		m_idlist.insert (index, id);
	}

	void
	Idlist::move (quint32 index, quint32 newindex )
	{
		quint32 id = m_idlist.takeAt (index);
		m_idlist.insert (newindex, id);
	}

	void
	Idlist::remove (quint32 index)
	{
		m_idlist.removeAt (index);
	}

	void
	Idlist::clear ()
	{
		m_idlist.clear ();
	}

	quint32
	Idlist::size () const
	{
		return m_idlist.size ();
	}

	void
	PartyShuffle::setOperand (Coll *operand)
	{
		removeOperand ();
		m_operands.append (operand);
	}

	void
	PartyShuffle::removeOperand ()
	{
		m_operands.clear ();
	}


/*	IdlistElement
	Idlist::operator[] (quint32 index)
	{
		return IdlistElement (*this, index);
	}

	const IdlistElement Idlist::operator []( unsigned int index ) const
	{
		return IdlistElement( *this, index );
	}

	IdlistElement::IdlistElement( Coll& coll, unsigned int index )
		: AbstractElement< unsigned int, unsigned int >( coll, index )
	{
	}

	IdlistElement::IdlistElement( const Coll& coll, unsigned int index )
		: AbstractElement< unsigned int, unsigned int >( const_cast< Coll& >( coll ),
	                                                     index )
	{
	}

	IdlistElement::~IdlistElement()
	{
	}

	IdlistElement::operator unsigned int() const
	{
		return coll_.getIndex( index_ );
	}

	unsigned int
	IdlistElement::operator=( unsigned int value )
	{
		coll_.setIndex( index_, value );
		return value;
	}

	OperandIterator::OperandIterator (Coll& coll) : coll_ (coll)
	{
	}

	OperandIterator::OperandIterator( const Coll& coll )
		: coll_( const_cast< Coll& >( coll ) )
	{
		coll_.ref();
	}

	OperandIterator::OperandIterator( const OperandIterator& src )
		: coll_( src.coll_ )
	{
		coll_.ref();
	}

	OperandIterator OperandIterator::operator=( const OperandIterator& src ) const
	{
		coll_.unref();
		coll_ = src.coll_;
		coll_.ref();
		return *this;
	}

	OperandIterator::~OperandIterator()
	{
		coll_.unref();
	}

	void OperandIterator::first()
	{
		if( !xmmsc_coll_operand_list_first( coll_.coll_ ) ) {
			throw out_of_range( "Access out of the operand list!" );
		}
	}

	bool OperandIterator::valid() const
	{
		return xmmsc_coll_operand_list_valid( coll_.coll_ );
	}

	void OperandIterator::next()
	{
		if( !xmmsc_coll_operand_list_next( coll_.coll_ ) ) {
			throw out_of_range( "Access out of the operand list!" );
		}
	}

	void OperandIterator::save()
	{
		if( !xmmsc_coll_operand_list_save( coll_.coll_ ) ) {
			throw out_of_range( "Access out of the operand list!" );
		}
	}

	void OperandIterator::restore()
	{
		if( !xmmsc_coll_operand_list_restore( coll_.coll_ ) ) {
			throw out_of_range( "Access out of the operand list!" );
		}
	}

	CollPtr OperandIterator::operator *() const
	{
		xmmsc_coll_t *op;
		if( !xmmsc_coll_operand_list_entry( coll_.coll_, &op ) ) {
			throw out_of_range( "Access out of the operand list!" );
		}

		return CollResult::createColl( op );
	}



	AttributeElement::AttributeElement( Coll& coll, string index )
		: AbstractElement< string, string >( coll, index )
	{
	}

	AttributeElement::AttributeElement( const Coll& coll, string index )
		: AbstractElement< string, string >( const_cast< Coll& >( coll ), index )
	{
	}

	AttributeElement::~AttributeElement()
	{
	}

	AttributeElement::operator string() const
	{
		return coll_.getAttribute( index_ );
	}

	string
	AttributeElement::operator=( string value )
	{
		coll_.setAttribute( index_, value );
		return value;
	}*/

	}
}
