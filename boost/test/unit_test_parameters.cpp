//  (C) Copyright Gennadiy Rozental 2001-2002.
//  Permission to copy, use, modify, sell and distribute this software
//  is granted provided this copyright notice appears in all copies.
//  This software is provided "as is" without express or implied warranty,
//  and with no claim as to its suitability for any purpose.

//  See http://www.boost.org for updates, documentation, and revision history.
//
//  File        : $RCSfile: unit_test_parameters.cpp,v $
//
//  Version     : $Id: unit_test_parameters.cpp,v 1.1.1.1 2003/02/25 14:58:27 tjl Exp $
//
//  Description : simple implementation for Unit Test Framework parameter 
//  handling routines. May be rewritten in future to use some kind of 
//  command-line arguments parsing facility and environment variable handling 
//  facility
// ***************************************************************************

// Boost.Test
#include <boost/test/detail/unit_test_parameters.hpp>

//BOOST
#include <boost/config.hpp>           // for broken compiler workarounds
// for strcmp etc:
#include <cstring>
#include <cstdlib>

# ifdef BOOST_NO_STDC_NAMESPACE
namespace std { using ::getenv; using ::strncmp; using ::strcmp; }
# endif

namespace boost {

namespace unit_test_framework {

const struct parameter_names {
    char const* env_name;
    char const* cla_name;
} parameter_cla_names [] = {
    { LOGLEVEL          , "--log_level" },
    { NO_RESULT_CODE    , "--result_code" },
    { RESULT_REPORT     , "--report_level" },
    { TESTS_TO_RUN      , "--run_test" },
    { SAVE_TEST_PATTERN , "--save_pattern" },
    { BUILD_INFO        , "--build_info" },
    { NULL              , NULL }
    
} ;

std::string
retrieve_framework_parameter( char const* parameter_name, int* argc, char** argv )
{
    // first try to find parameter among command line arguments if present
    if( argc != NULL ) {
        // locate corresponding cla name
        parameter_names const* curr = parameter_cla_names;
        while( curr->env_name != NULL && std::strcmp( curr->env_name, parameter_name ) != 0 )
            curr++;

        if( curr->env_name != NULL ) {
            std::string parameter_cla_name = curr->cla_name;
            parameter_cla_name += '=';
            
            for( int i = 1; i < *argc; ++i ) {
                if( std::strncmp( parameter_cla_name.data(), argv[i], parameter_cla_name.length() ) == 0 ) {
                    std::string result = argv[i] + parameter_cla_name.length();
                    
                    for( int j = i; j < *argc; ++j ) {
                        argv[j] = argv[j+1];
                    }
                    --(*argc);
                    
                    return result;
                }
            }
        }
    }

    char const* env_var_value = std::getenv( parameter_name );
    return  env_var_value == NULL ? "" : env_var_value;
}

//____________________________________________________________________________//

} // namespace unit_test_framework

} // namespace boost

// ***************************************************************************
//  Revision History :
//  
//  $Log: unit_test_parameters.cpp,v $
//  Revision 1.1.1.1  2003/02/25 14:58:27  tjl
//  From debian's boost...
//
//  Revision 1.4.2.1  2002/10/01 05:48:27  rogeeff
//  coment clarified
//
//  Revision 1.4  2002/09/15 11:17:23  johnmaddock
//  Added missing includes
//
//  Revision 1.3  2002/08/20 08:24:13  rogeeff
//  cvs keywords added
//
//   26 Oct 01  Initial version (Gennadiy Rozental)

// ***************************************************************************

// EOF

