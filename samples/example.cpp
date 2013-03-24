/*
Copyright Mike Naquin, 2007. All rights reserved.
File:
	example.cpp

Created: 2007.12.18

Description:
	examples of safe_data
*/

#include <iostream>
#include <stdexcept>
#include <string>

#include "safe_data/safe_data.h"

using safe_data::safe;
using safe_data::no_initial;
using safe_data::no_validation;

using safe_data::c_str;
using boost::mpl::int_;
      
using safe_data::max_validation;
using safe_data::range_validation;
using safe_data::str_length_validation;

// A floating point percent type with valid values between 0.0 and 1.0. Defaults to 0.5.
SAFE_DATA_INITIAL_VALUE(double_init, double, 0.5)

typedef safe<
    double,
    range_validation<double, int_<0>, int_<1> >,
    double_init
> percent;

// An int type that must be less than 42. Defaults to 8.
typedef safe<
    int,
    max_validation<int, int_<42> >,
    int_<8>
> safe_int;

// A string type that cannot exceed a length of 8 characters. Defaults to "foo".
typedef safe<
    std::string,
    str_length_validation<std::string, boost::mpl::size_t<8> >,
    c_str<boost::mpl::string<'f', 'o', 'o'> >
> safe_str;

void example()
{
	percent p; // initial value is 0.5
	p = 0.6;   // 0.6 within range of 0.0 and 1.0
    try {
    	p = 1.5;   // throws exception: out of range
    }
    catch (std::exception const& e) {
        std::cout << e.what() << std::endl;
    }

	safe_int i; // initial value set to 8
	i = 16;     // 16 is less than the max value
	++i;        // increment to 17, still less than the max value
    try {
    	i = 43;     // throws exception: greater than the max value
    }
    catch (std::exception const& e) {
        std::cout << e.what() << std::endl;
    }
	i = -128;   // no minimum validation; okay

	safe_str s;       // initial value set to "foo"
	s += " bar";      // concatenates to "foo bar"
	try {
    	s += " too long"; // throws exception: string length would now be too long
	}
    catch (std::exception const& e) {
        std::cout << e.what() << std::endl;
    }    
}
