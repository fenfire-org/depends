//  (C) Copyright Gennadiy Rozental 2001-2002.
//  Permission to copy, use, modify, sell and distribute this software
//  is granted provided this copyright notice appears in all copies.
//  This software is provided "as is" without express or implied warranty,
//  and with no claim as to its suitability for any purpose.

//  See http://www.boost.org for most recent version including documentation.
//
//  File        : $RCSfile: unit_test_parameters.hpp,v $
//
//  Version     : $Id: unit_test_parameters.hpp,v 1.1.1.1 2003/02/25 14:58:27 tjl Exp $
//
//  Description : storage for unit test framework parameters information
// ***************************************************************************

#ifndef BOOST_UNIT_TEST_PARAMETERS_HPP
#define BOOST_UNIT_TEST_PARAMETERS_HPP

// STL
#include <string>

namespace boost {

namespace unit_test_framework {

// framework parameters and there corresponding command-line arguments
char const* const LOGLEVEL          = "BOOST_TEST_LOG_LEVEL";        // --log_level
char const* const NO_RESULT_CODE    = "BOOST_TEST_RESULT_CODE";      // --result_code
char const* const RESULT_REPORT     = "BOOST_TEST_REPORT_LEVEL";     // --result_report
char const* const TESTS_TO_RUN      = "BOOST_TESTS_TO_RUN";          // --run_test
char const* const SAVE_TEST_PATTERN = "BOOST_TEST_SAVE_PATTERN";     // --save_pattern
char const* const BUILD_INFO        = "BOOST_TEST_BUILD_INFO";       // --build_info

enum result_report_level                { CONFIRMATION_REPORT, SHORT_REPORT, DETAILED_REPORT, NO_REPORT };
char const* const report_level_names[] = { "confirm"          , "short"     , "detailed"     , "no"      };

std::string retrieve_framework_parameter( char const* parameter_name_, int* argc_ = NULL, char ** argv_ = NULL );

} // namespace unit_test_framework

} // namespace boost

// ***************************************************************************
//  Revision History :
//  
//  $Log: unit_test_parameters.hpp,v $
//  Revision 1.1.1.1  2003/02/25 14:58:27  tjl
//  From debian's boost...
//
//  Revision 1.4  2002/09/09 09:07:03  rogeeff
//  descriptions added
//
//  Revision 1.3  2002/08/20 22:24:54  rogeeff
//  all formal arguments trailed with underscore
//
//  Revision 1.2  2002/08/20 08:52:41  rogeeff
//  cvs keywords added
//
//   8 Aug 02  Initial version (Gennadiy Rozental)

// ***************************************************************************

#endif // BOOST_UNIT_TEST_CONFIG_HPP
