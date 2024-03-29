//  (C) Copyright Gennadiy Rozental 2001-2002.
//  Permission to copy, use, modify, sell and distribute this software
//  is granted provided this copyright notice appears in all copies.
//  This software is provided "as is" without express or implied warranty,
//  and with no claim as to its suitability for any purpose.

//  See http://www.boost.org for most recent version including documentation.
//
//  File        : $RCSfile: class_properties.hpp,v $
//
//  Version     : $Id: class_properties.hpp,v 1.1.1.1 2003/02/25 14:58:27 tjl Exp $
//
//  Description : simple facility that mimmic notion of read-only read-write 
//  properties in C++ classes. Original idea by Henrik Ravn.
// ***************************************************************************

#ifndef CLASS_PROPERTY_HPP
#define CLASS_PROPERTY_HPP

// ************************************************************************** //
// **************               readonly_property              ************** //
// ************************************************************************** //

#define BOOST_FRIENDS_DECLARER0()
#define BOOST_FRIENDS_DECLARER1( friend1 )                            friend class friend1;
#define BOOST_FRIENDS_DECLARER2( friend1, friend2 )                   BOOST_FRIENDS_DECLARER1( friend1 ) friend class friend2;
#define BOOST_FRIENDS_DECLARER3( friend1, friend2, friend3 )          BOOST_FRIENDS_DECLARER2( friend1, friend2 ) friend class friend3;
#define BOOST_FRIENDS_DECLARER4( friend1, friend2, friend3, friend4 ) BOOST_FRIENDS_DECLARER3( friend1, friend2, friend3 ) friend class friend4;

#define BOOST_READONLY_PROPERTY( property_type, friends_num, friends )                                              \
class BOOST_JOIN( readonly_property, __LINE__ )                                                                     \
{                                                                                                                   \
    BOOST_FRIENDS_DECLARER ## friends_num friends                                                                   \
public:                                                                                                             \
    explicit BOOST_JOIN( readonly_property, __LINE__ )( property_type const& init_value  ) : value( init_value ) {} \
                                                                                                                    \
    operator                property_type const &() const       { return value; }                                   \
    property_type const&    get() const                         { return value; }                                   \
private:                                                                                                            \
    property_type           value;                                                                                  \
}

// ************************************************************************** //
// **************              readwrite_property              ************** //
// ************************************************************************** //

#define BOOST_READWRITE_PROPERTY( property_type )                                                                   \
class BOOST_JOIN( readwrite_property, __LINE__ )                                                                    \
{                                                                                                                   \
public:                                                                                                             \
             BOOST_JOIN( readwrite_property, __LINE__ )()        {}                                                 \
    explicit BOOST_JOIN( readwrite_property, __LINE__ )( property_type const& init_value  ) : value( init_value ) {}\
                                                                                                                    \
    operator                property_type const &() const       { return value; }                                   \
    property_type const&    get() const                         { return value; }                                   \
    void                    set( property_type const& v )       { value = v; }                                      \
private:                                                                                                            \
    property_type value;                                                                                            \
}

// ***************************************************************************
//  Revision History :
//  
//  $Log: class_properties.hpp,v $
//  Revision 1.1.1.1  2003/02/25 14:58:27  tjl
//  From debian's boost...
//
//  Revision 1.5.2.1  2002/10/01 17:23:53  rogeeff
//  cr fixed
//
//  Revision 1.5  2002/09/09 09:07:03  rogeeff
//  descriptions added
//
//  Revision 1.4  2002/08/20 08:52:41  rogeeff
//  cvs keywords added
//
//   5 Oct 01  Initial version (Gennadiy Rozental)

// ***************************************************************************

#endif // CLASS_PROPERTY_HPP
