//  (C) Copyright Gennadiy Rozental 2001-2002.
//  Permission to copy, use, modify, sell and distribute this software
//  is granted provided this copyright notice appears in all copies.
//  This software is provided "as is" without express or implied warranty,
//  and with no claim as to its suitability for any purpose.

//  See http://www.boost.org for updates, documentation, and revision history.
//
//  File        : $RCSfile: unit_test_suite.cpp,v $
//
//  Version     : $Id: unit_test_suite.cpp,v 1.1.1.1 2003/02/25 14:58:27 tjl Exp $
//
//  Description : privide core implementation for Unit Test Framework. 
//  Extensions could be provided in separate files
// ***************************************************************************

// Boost.Test
#include <boost/test/unit_test_suite.hpp>
#include <boost/test/unit_test_log.hpp>
#include <boost/test/unit_test_result.hpp>

// STL
#include <list>
#include <algorithm>

namespace boost {

namespace unit_test_framework {

// ************************************************************************** //
// **************                   test_case                  ************** //
// ************************************************************************** //

void
test_case::run()
{
    bool is_initialized  = true;
         s_abort_testing = false;

    char const* name = ((std::string&)p_name).data();

    // 1. Init test results
    unit_test_result::test_case_start( name, p_expected_failures );


    BOOST_TEST_SUITE_MESSAGE_BEGIN
        "\nEntering test " << (size() > 1 ? "suite" : "case") << " \"" << name << "\""
    BOOST_TEST_SUITE_MESSAGE_END

    // 2. Initialize test case
    if( m_monitor_run ) {
        error_level_type init_result =
            detail::unit_test_monitor( *this, &test_case::do_init ).execute_and_translate( p_timeout );

        is_initialized   = init_result == detail::unit_test_monitor::test_ok;
        s_abort_testing  = detail::unit_test_monitor::is_critical_error( init_result );
    }
    else {
        do_init();
    }

    // 3. Run test case (all stages)
    for( unit_test_counter i=0; i != p_stages_amount && !s_abort_testing && is_initialized; ++i ) {
        p_compound_stage.value = false; // could be set by do_run to mark compound stage;
                                        // than no need to report progress here

        if( m_monitor_run ) {
            error_level_type run_result =
                detail::unit_test_monitor( *this, &test_case::do_run ).execute_and_translate( p_timeout );

            s_abort_testing = detail::unit_test_monitor::is_critical_error( run_result );
        }
        else {
            do_run();
        }

        if( p_stages_amount != 1 && !p_compound_stage.get() ) // compound test
            unit_test_log::instance() << report_progress();
    }

    // 3. Finalize test case
    if( is_initialized && !s_abort_testing ) {
        if( m_monitor_run ) {
            error_level_type destroy_result =
                detail::unit_test_monitor( *this, &test_case::do_destroy ).execute_and_translate( p_timeout );

            s_abort_testing = detail::unit_test_monitor::is_critical_error( destroy_result );
        }
        else {
            do_destroy();
        }
    }

    if( s_abort_testing ) {
        BOOST_UT_LOCAL_LOG_BEGIN( report_fatal_errors )
            "testing aborted"
        BOOST_UT_LOG_END
    }

    BOOST_TEST_SUITE_MESSAGE_BEGIN
        "Leaving  test " << (size() > 1 ? "suite" : "case") << " \"" << name << "\""
    BOOST_TEST_SUITE_MESSAGE_END

    unit_test_result::test_case_end();
}

//____________________________________________________________________________//

bool test_case::s_abort_testing = false;

// ************************************************************************** //
// **************                  test_suite                  ************** //
// ************************************************************************** //

struct test_suite::Impl {
    std::list<test_case*>           m_test_cases;
    std::list<test_case*>::iterator m_curr_test_case;
    unit_test_counter               m_cumulative_size;
};

//____________________________________________________________________________//

test_suite::test_suite( char const* name ) : test_case( name, 0, false ), m_pimpl( new Impl )
{
    m_pimpl->m_cumulative_size = 0;
}

//____________________________________________________________________________//

static void safe_delete_test_case( test_case* ptr ) { boost::checked_delete<test_case>( ptr ); }

test_suite::~test_suite()
{   
    std::for_each( m_pimpl->m_test_cases.begin(), m_pimpl->m_test_cases.end(), &safe_delete_test_case );
}

//____________________________________________________________________________//

void
test_suite::add( test_case* tc, unit_test_counter exp_fail, int timeout )
{
    if( exp_fail != 0 ) {
        tc->p_expected_failures.value = exp_fail;
    }

    p_expected_failures.value += tc->p_expected_failures;

    if( timeout != 0 )
        tc->p_timeout.value = timeout;

    m_pimpl->m_test_cases.push_back( tc );
    m_pimpl->m_cumulative_size += tc->size();

    p_stages_amount.set( p_stages_amount.get()+1 );
}

//____________________________________________________________________________//

unit_test_counter
test_suite::size() const
{
    return m_pimpl->m_cumulative_size;
}

//____________________________________________________________________________//

void
test_suite::do_init()
{
    m_pimpl->m_curr_test_case = m_pimpl->m_test_cases.begin();
}

//____________________________________________________________________________//

void
test_suite::do_run()
{
    if( (*m_pimpl->m_curr_test_case)->size() > 1 )
        p_compound_stage.value = true;
    (*m_pimpl->m_curr_test_case)->run();
    ++m_pimpl->m_curr_test_case;
}

//____________________________________________________________________________//

// ************************************************************************** //
// **************               object generators              ************** //
// ************************************************************************** //

} // namespace unit_test_framework

} // namespace boost

// ***************************************************************************
//  Revision History :
//  
//  $Log: unit_test_suite.cpp,v $
//  Revision 1.1.1.1  2003/02/25 14:58:27  tjl
//  From debian's boost...
//
//  Revision 1.4.2.1  2002/10/01 05:48:27  rogeeff
//  coment clarified
//
//  Revision 1.4  2002/08/20 08:24:13  rogeeff
//  cvs keywords added
//
//   5 Oct 01  Initial version (Gennadiy Rozental)

// ***************************************************************************

// EOF
