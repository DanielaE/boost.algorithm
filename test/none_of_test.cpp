/* 
   Copyright (c) Marshall Clow 2010-2012.

   Distributed under the Boost Software License, Version 1.0. (See accompanying
   file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    For more information, see http://www.boost.org
*/

#include <boost/config.hpp>
#include <boost/algorithm/cxx11/none_of.hpp>

#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>

#include <functional>
#include <vector>
#include <list>

template<typename T>
struct is_ {
    BOOST_CXX14_CONSTEXPR is_ ( T v ) : val_ ( v ) {}
    BOOST_CXX14_CONSTEXPR bool operator () ( T comp ) const { return val_ == comp; }
private:
    is_ (); // need a value

    T val_;
    };

namespace ba = boost::algorithm;

void test_none()
{
//  Note: The literal values here are tested against directly, careful if you change them:
    BOOST_CXX14_CONSTEXPR int some_numbers[] = { 1, 5, 0, 18, 1 };
    std::vector<int> vi(some_numbers, some_numbers + 5);
    std::list<int>   li(vi.begin(), vi.end ());
    
    char some_letters[] = { 'a', 'q', 'n', 'y', 'n' };
    std::vector<char> vc(some_letters, some_letters + 5);
    
    BOOST_CHECK ( ba::none_of_equal ( vi,                                  100 ));
    BOOST_CHECK ( ba::none_of       ( vi,                       is_<int> ( 100 )));
    BOOST_CHECK ( ba::none_of_equal ( vi.begin(),     vi.end(),            100 ));
    BOOST_CHECK ( ba::none_of       ( vi.begin(),     vi.end(), is_<int> ( 100 )));

    BOOST_CHECK (!ba::none_of_equal ( vi,                                    1 ));
    BOOST_CHECK (!ba::none_of       ( vi,                       is_<int> (   1 )));
    BOOST_CHECK (!ba::none_of_equal ( vi.begin(),     vi.end(),              1 ));
    BOOST_CHECK (!ba::none_of       ( vi.begin(),     vi.end(), is_<int> (   1 )));

    BOOST_CHECK ( ba::none_of_equal ( vi.end(),       vi.end(),              0 ));
    BOOST_CHECK ( ba::none_of       ( vi.end(),       vi.end(), is_<int> (   0 )));

//   5 is not in { 0, 18, 1 }, but 1 is
    BOOST_CHECK ( ba::none_of_equal ( vi.begin() + 2, vi.end(),              5 ));
    BOOST_CHECK ( ba::none_of       ( vi.begin() + 2, vi.end(), is_<int> (   5 )));
    BOOST_CHECK (!ba::none_of_equal ( vi.begin() + 2, vi.end(),              1 ));
    BOOST_CHECK (!ba::none_of       ( vi.begin() + 2, vi.end(), is_<int> (   1 )));

//  18 is not in { 1, 5, 0 }, but 5 is
    BOOST_CHECK ( ba::none_of_equal ( vi.begin(),     vi.begin() + 3,            18 ));
    BOOST_CHECK ( ba::none_of       ( vi.begin(),     vi.begin() + 3, is_<int> ( 18 )));
    BOOST_CHECK (!ba::none_of_equal ( vi.begin(),     vi.begin() + 3,             5 ));
    BOOST_CHECK (!ba::none_of       ( vi.begin(),     vi.begin() + 3, is_<int> (  5 )));
    
    BOOST_CHECK ( ba::none_of_equal ( vc,             'z' ));
    BOOST_CHECK ( ba::none_of       ( vc, is_<char> ( 'z' )));

    BOOST_CHECK (!ba::none_of_equal ( vc,             'a' ));
    BOOST_CHECK (!ba::none_of       ( vc, is_<char> ( 'a' )));

    BOOST_CHECK (!ba::none_of_equal ( vc,             'n' ));
    BOOST_CHECK (!ba::none_of       ( vc, is_<char> ( 'n' )));

    BOOST_CHECK ( ba::none_of_equal ( vi.begin(), vi.begin(),   1 ));
    BOOST_CHECK ( ba::none_of_equal ( vc.begin(), vc.begin(), 'a' ));
    BOOST_CHECK ( ba::none_of       ( vi.begin(), vi.begin(), is_<int>  (   1 )));
    BOOST_CHECK ( ba::none_of       ( vc.begin(), vc.begin(), is_<char> ( 'a' )));

    BOOST_CHECK ( ba::none_of_equal ( li,                                  100 ));
    BOOST_CHECK ( ba::none_of       ( li,                       is_<int> ( 100 )));
    BOOST_CHECK ( ba::none_of_equal ( li.begin(),     li.end(),            100 ));
    BOOST_CHECK ( ba::none_of       ( li.begin(),     li.end(), is_<int> ( 100 )));
    
    std::list<int>::iterator l_iter = li.begin ();
    l_iter++; l_iter++; l_iter++;
    BOOST_CHECK ( ba::none_of_equal ( li.begin(), l_iter,            18 ));
    BOOST_CHECK ( ba::none_of       ( li.begin(), l_iter, is_<int> ( 18 )));
    BOOST_CHECK (!ba::none_of       ( li.begin(), l_iter, is_<int> (  5 )));

    BOOST_CXX14_CONSTEXPR bool constexpr_res =
        !ba::none_of_equal ( some_numbers, 1 )                                 &&
        !ba::none_of       ( some_numbers, is_<int> ( 1 ))                     &&
         ba::none_of_equal ( some_numbers, some_numbers + 3,            100 )  &&
         ba::none_of       ( some_numbers, some_numbers + 3, is_<int> ( 100 )) &&
        true;

    BOOST_CHECK ( constexpr_res );
}

BOOST_AUTO_TEST_CASE( test_main )
{
  test_none();
}
