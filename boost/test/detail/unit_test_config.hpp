//  (C) Copyright Gennadiy Rozental 2001-2002.
//  Permission to copy, use, modify, sell and distribute this software
//  is granted provided this copyright notice appears in all copies.
//  This software is provided "as is" without express or implied warranty,
//  and with no claim as to its suitability for any purpose.

//  See http://www.boost.org for most recent version including documentation.
//
//  File        : $RCSfile: unit_test_config.hpp,v $
//
//  Version     : $Id: unit_test_config.hpp,v 1.1.1.1 2003/02/25 14:58:27 tjl Exp $
//
//  Description : contains workarounds and works as a central place for configurable types
// ***************************************************************************

#ifndef BOOST_UNIT_TEST_CONFIG_HPP
#define BOOST_UNIT_TEST_CONFIG_HPP

// BOOST
#include <boost/config.hpp> // compilers workarounds and std::ptrdiff_t

// STL
#include <iterator>     // for std::distance
#include <cstddef>      // for std::ptrdiff_t

namespace boost {

namespace unit_test_framework {

typedef unsigned long unit_test_counter;

namespace detail {

#ifdef BOOST_NO_STD_DISTANCE
template <class T>
std::ptrdiff_t distance( T const& x_, T const& y_ )
{ 
    std::ptrdiff_t res = 0;

    std::distance( x_, y_, res );

    return res;
}
#else
using std::distance;
#endif

} // namespace detail

} // namespace unit_test_framework

} // namespace boost

// ***************************************************************************
//  Revision History :
//  
//  $Log: unit_test_config.hpp,v $
//  Revision 1.1.1.1  2003/02/25 14:58:27  tjl
//  From debian's boost...
//
//  Revision 1.10.2.2  2002/10/10 18:14:41  rogeeff
//  removed incorrect fix
//
//  Revision 1.10.2.1  2002/10/01 17:23:15  rogeeff
//  borlang temporary bug fix introduced
//
//  Revision 1.10  2002/09/16 08:47:29  rogeeff
//  STL includes normalized
//
//  Revision 1.9  2002/09/09 09:07:03  rogeeff
//  descriptions added
//
//  Revision 1.8  2002/08/20 22:24:53  rogeeff
//  all formal arguments trailed with underscore
//
//  Revision 1.7  2002/08/20 08:52:41  rogeeff
//  cvs keywords added
//
//   8 Aug 02  Parameters definition separated (Gennadiy Rozental)
//   5 Oct 01  Initial version (Gennadiy Rozental)

// ***************************************************************************

#endif // BOOST_UNIT_TEST_CONFIG_HPP
