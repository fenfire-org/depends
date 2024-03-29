//  (C) Copyright Gennadiy Rozental 2001-2002.
//  Permission to copy, use, modify, sell and distribute this software
//  is granted provided this copyright notice appears in all copies.
//  This software is provided "as is" without express or implied warranty,
//  and with no claim as to its suitability for any purpose.

//  See http://www.boost.org for most recent version including documentation.
//
//  File        : $RCSfile: unit_test_log.hpp,v $
//
//  Version     : $Id: unit_test_log.hpp,v 1.1.1.1 2003/02/25 14:58:27 tjl Exp $
//
//  Description : defines singleton class unit_test_log and all manipulators.
//  unit_test_log has output stream like interface. It's implementation is completely 
//  hidden with pimple idiom
// ***************************************************************************

#ifndef BOOST_UNIT_TEST_LOG_HPP
#define BOOST_UNIT_TEST_LOG_HPP

// Boost.Test
#include <boost/test/detail/unit_test_config.hpp>

// BOOST
#include <boost/utility.hpp>

// STL
#include <iosfwd>   // for std::ostream&
#include <string>   // for std::string&; in fact need only forward declaration

namespace boost {

namespace unit_test_framework {

//  each reporting level includes all subsequent higher reporting levels
enum            report_level {
    report_successful_tests     = 0,
    report_test_suites          = 1,
    report_messages             = 2,
    report_warnings             = 3,
    report_all_errors           = 4, // reported by unit test macros
    report_cpp_exception_errors = 5, // uncaught C++ exceptions
    report_system_errors        = 6, // including timeouts, signals, traps
    report_fatal_errors         = 7, // including unit test macros or
                                     // fatal system errors
    report_progress_only        = 8, // only unit test progress to be reported
    report_nothing              = 9
};

// ************************************************************************** //
// **************                log manipulators              ************** //
// ************************************************************************** //

struct begin {
};

struct end {
};

struct level {
    explicit    level( report_level l_ ) : m_level( l_ ) {}

    report_level m_level;
};

struct line {
    explicit    line( unsigned int ln_ ) : m_line_num( ln_ ) {}

    unsigned int m_line_num;
};

struct file {
    explicit    file( char const* fn_ ) : m_file_name( fn_ ) {}

    char const* m_file_name;
};

struct checkpoint {
    explicit    checkpoint( std::string const& message_ ) : m_message( message_ ) {}

    std::string const& m_message;
};

struct report_exception {
    report_exception( char const* what_ ) : m_what( what_ ) {}

    char const*     m_what;
};

struct report_progress {
};

// ************************************************************************** //
// **************                 unit_test_log                ************** //
// ************************************************************************** //

class unit_test_log : private boost::noncopyable { //!! Singleton
public:
    // Destructor
    ~unit_test_log();

    // instance access method;
    static unit_test_log& instance();

    // log configuration methods
    void            start( unit_test_counter test_cases_amount_, bool print_build_info_ = false );
    void            set_log_stream( std::ostream& str_ );
    void            set_log_threshold_level( report_level lev_ );
    void            set_log_threshold_level_by_name( char const* lev_ );
    void            clear_checkpoint();

    // entry configuration methods
    unit_test_log&  operator<<( begin const& ); // begin entry 
    unit_test_log&  operator<<( end const& );   // end entry
    unit_test_log&  operator<<( file const& );  // set file name
    unit_test_log&  operator<<( line const& );  // set line number
    unit_test_log&  operator<<( level const& );  // set entry level
    unit_test_log&  operator<<( checkpoint const& ); // set checkpoint

    // print value_ methods
    unit_test_log&  operator<<( report_progress const& );
    unit_test_log&  operator<<( report_exception const& );
    unit_test_log&  operator<<( char const* value_ );
    unit_test_log&  operator<<( std::string const& value_ );

private:
    // Constructor
    unit_test_log();

    struct          Impl;
    Impl*           m_pimpl;
}; // unit_test_log

// helper macro
#define BOOST_UT_LOG_BEGIN( file_name, line_num, loglevel )                             \
    boost::unit_test_framework::unit_test_log::instance()                               \
                                     << boost::unit_test_framework::begin()             \
                                     << boost::unit_test_framework::level( loglevel )   \
                                     << boost::unit_test_framework::file( file_name )   \
                                     << boost::unit_test_framework::line( line_num ) <<

#define BOOST_UT_LOCAL_LOG_BEGIN( loglevel ) BOOST_UT_LOG_BEGIN( __FILE__, __LINE__, boost::unit_test_framework::loglevel )
#define BOOST_UT_MESSAGE_BEGIN( loglevel )                                              \
    boost::unit_test_framework::unit_test_log::instance()                               \
                                     << boost::unit_test_framework::begin()             \
                                     << boost::unit_test_framework::level( boost::unit_test_framework::loglevel ) <<

#define BOOST_TEST_SUITE_MESSAGE_BEGIN BOOST_UT_MESSAGE_BEGIN( report_test_suites )
#define BOOST_UT_LOG_END             << boost::unit_test_framework::end();
#define BOOST_TEST_SUITE_MESSAGE_END << boost::unit_test_framework::end();

} // namespace unit_test_framework

} // namespace boost

// ***************************************************************************
//  Revision History :
//  
//  $Log: unit_test_log.hpp,v $
//  Revision 1.1.1.1  2003/02/25 14:58:27  tjl
//  From debian's boost...
//
//  Revision 1.10.2.1  2002/10/01 17:26:36  rogeeff
//  reset current set feature introduces. Mostly for internal testing
//
//  Revision 1.10  2002/09/19 08:23:23  rogeeff
//  explicit private added to shut down warnings
//
//  Revision 1.9  2002/09/16 08:47:29  rogeeff
//  STL includes normalized
//
//  Revision 1.8  2002/09/09 09:07:03  rogeeff
//  descriptions added
//
//  Revision 1.7  2002/08/20 22:24:53  rogeeff
//  all formal arguments trailed with underscore
//
//  Revision 1.6  2002/08/20 08:52:40  rogeeff
//  cvs keywords added
//
//   5 Oct 01  Initial version (Gennadiy Rozental)

// ***************************************************************************

#endif // BOOST_UNIT_TEST_LOG_HPP

