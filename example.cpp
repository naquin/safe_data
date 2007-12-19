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

#include "safe_data/safe_data.hpp"

using std::string;
using std::cout;
using std::endl;

using safe_data::safe;
using safe_data::no_initial;
using safe_data::no_validation;

using safe_data::initial_value;
using safe_data::max_value;
using safe_data::range_value;
      
using safe_data::max_validation;
using safe_data::range_validation;
using safe_data::str_length_validation;

// A floating point percent type with valid values between 0.0 and 1.0. Defaults to 0.0.
typedef safe<
    double,
    range_validation<double, range_value<0,1> >,
    initial_value<0>
> percent;

// An int type that must be less than 42. Defaults to 8.
typedef safe<
    int,
    max_validation<int, max_value<42> >,
    initial_value<8>
> safe_int;

struct str_initial {
	static const char* value() { return "foo"; }
};

// A string type that cannot exceed a length of 8 characters. Defaults to "foo".
typedef safe<
    string,
    str_length_validation<string, max_value<8> >,
    str_initial
> safe_str;

void example()
{
	percent p; // initial value is 0
	p = 0.5;   // 0.5 within range of 0.0 and 1.0
    try {
    	p = 1.5;   // throws exception: out of range
    }
    catch (std::exception const& e) {
        cout << e.what() << endl;
    }

	safe_int i; // initial value set to 8
	i = 16;     // 16 is less than the max value
	++i;        // increment to 17, still less than the max value
    try {
    	i = 43;     // throws exception: greater than the max value
    }
    catch (std::exception const& e) {
        cout << e.what() << endl;
    }
	i = -128;   // no minimum validation; okay

	safe_str s;       // initial value set to "foo"
	s += " bar";      // concatenates to "foo bar"
	try {
    	s += " too long"; // throws exception: string length would now be too long
	}
    catch (std::exception const& e) {
        cout << e.what() << endl;
    }    
}
