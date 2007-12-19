/*
Copyright Mike Naquin, 2006. All rights reserved.
File:
	main.cpp

Created: 2006.05.14

Description:
	
*/

#include <iostream>
#include <stdexcept>

using std::cout;
using std::cerr;
using std::endl;

void test_percent(std::ostream& out);
void test_int    (std::ostream& out);
void test_str    (std::ostream& out);
void test_ref    (std::ostream& out);
void test_const  (std::ostream& out);
void test_date   (std::ostream& out);

int main(int const argc, char* argv[])
{
	try {
		test_percent(cout);
		test_int    (cout);
		test_str    (cout);
		test_ref    (cout);
		test_const  (cout);
		test_date   (cout);

		cout << '\n' << "--== Success ==--" << endl;
		return 0;
	}
	catch ( std::exception const& e ) {
		cerr << e.what() << endl;
	}
	catch (...) {
		cerr << "An unknown exception has occurred." << endl;
	}

	cerr << '\n' << "--== Failure ==--" << endl;
	return 1;
}


#include <boost/assert.hpp>

//#include "safe_data/safe_data.hpp"
#include "safe_data/safe.hpp"
#include "safe_data/values.hpp"
#include "safe_data/validations.hpp"
#include "safe_data/exceptions.hpp"


#include <stdexcept>
#include <string>

using std::string;

using safe_data::safe;
using safe_data::get;
using safe_data::no_initial;
using safe_data::no_validation;
      
using safe_data::min_exception;
using safe_data::max_exception;
using safe_data::range_exception;
using safe_data::size_exception;
using safe_data::str_length_exception;
      
using safe_data::initial_value;
using safe_data::max_value;
using safe_data::min_value;
using safe_data::range_value;
      
using safe_data::min_validation;
using safe_data::max_validation;
using safe_data::range_validation;
using safe_data::str_length_validation;

typedef initial_value<0> percent_initial;
typedef range_value<0,1> percent_range;

template <class T, class validation>
struct percent_exception : public range_exception<T, validation> {
	typedef T value_type;
	typedef T const& argument_type;
	typedef validation validation_type;

	explicit percent_exception(argument_type data) :
		range_exception<T, validation>(percent_msg(data))
	{ }
	explicit percent_exception(std::string const& msg) :
		range_exception<T, validation>(msg)
	{ }

//	virtual ~percent_exception() { }

	static std::string percent_msg(argument_type data)
	{
		std::ostringstream ss;
		ss  << "The percent " << (data * 100) << "% must be between "
			<< (validation_type::min_val * 100) << "% and "
			<< (validation_type::max_val * 100) << "%.";
		return ss.str();
	}
};

template <class T, class validation = percent_range,
	class exception = percent_exception<T, validation>
>
struct percent_validation : public range_validation<T, validation, exception> {
	typedef range_validation<T, validation, exception> base;
	typedef typename base::validation_type validation_type;
	typedef typename base::exception_type  exception_type;
	typedef typename base::argument_type   argument_type;

	using base::validate;
};

typedef safe<double, percent_validation<double>, percent_initial> percent;

void test_percent(std::ostream& out)
{
	out << " - percent test - " << endl;
	percent p;

	BOOST_ASSERT(p == 0);
	out << "initial value: " << p << endl;

	p = 0.5;
	BOOST_ASSERT(p == 0.5);
	out << "assign to 50%: " << p << endl;

	try {
		// test against min value
		p = -1.5;
	}
	catch (percent::validation_type::exception_type const& e) {
		out << "expected exception caught: " << e.what() << endl;
	}

	// should still be 50% at this point
	BOOST_ASSERT(p == 0.5);

	try {
		// test against max value
		p = 2;
	}
	catch (percent::validation_type::exception_type const& e) {
		out << "expected exception caught: " << e.what() << endl;
	}

	BOOST_ASSERT(p == 0.5);

	p = 1;
	out << "assign to 100%: " << p << endl;

	out << endl;
}

// int test
typedef safe<int, max_validation<int, max_value<32> >, initial_value<8> > safe_int;

void test_int(std::ostream& out)
{
	out << " - int max test - " << endl;
	safe_int i; // initial value set to 8

	BOOST_ASSERT(i == 8);
	out << "initial value: " << i << endl;

	i = 16;
	BOOST_ASSERT(i == 16);
	out << "assign to 16: " << i << endl;

	++i;
	BOOST_ASSERT(i == 17);
	out << "increment to 17: " << i << endl;

	try {
		// test against max value
		i = 33;
	}
	catch (safe_int::validation_type::exception_type const& e) {
		out << "expected exception caught: " << e.what() << endl;
	}

	BOOST_ASSERT(i == 17);

	// no min validation
	i = -128;
	BOOST_ASSERT(i = -128);
	out << "assign to -128: " << i << endl;

	out << endl;
}

#include "safe_data/compare.hpp"
#include "safe_data/io.hpp"
#include "safe_data/operators.hpp"

struct str_initial {
	static const char* value() { return "foo"; }
};

// string test
typedef safe<string, str_length_validation<string, max_value<8> >, str_initial> safe_str;

void test_str(std::ostream& out)
{
	out << " - string length test - " << endl;
	safe_str s; // initial "foo"

	BOOST_ASSERT(s == "foo"); // use boost/safe_data/compare.hpp or get(s) or s.data()
	out << "initial value: " << s << endl; // use boost/safe_data/io.hpp or get(s) or s.data()

	s += " bar"; // use boost/safe_data/operators.hpp or s = get(s) + " bar"
	BOOST_ASSERT(s == "foo bar");
	out << "concatination: " << s << endl;

	try {
		s = "long " + get(s); // operator+ cannot const char* to string
		                      // can also string("long ") + s
		                      // or "long " + s.data()
	}
	catch (safe_str::validation_type::exception_type const& e ) {
		out << "expected exception caught: " << e.what() << endl;
	}

	BOOST_ASSERT(s == "foo bar");

	out << endl;
}

typedef safe<double&, range_validation<double, range_value<0, 10> > > safe_dbl;

void test_ref(std::ostream& out)
{
	out << " - double reference test - " << endl;

	double pod_d = 3.14;
	out << "POD initial: " << pod_d << endl;

	safe_dbl safe_d(pod_d);
	BOOST_ASSERT(safe_d == 3.14);
	out << "safe initial: " << safe_d << endl;

	try {
		safe_d *= 4;
	}
	catch ( safe_dbl::validation_type::exception_type const& e )  {
		out << "expected exception caught: " << e.what() << endl;
	}

	BOOST_ASSERT(safe_d == 3.14);
	BOOST_ASSERT(pod_d  == 3.14);

	safe_d /= 2;
	BOOST_ASSERT(safe_d == 1.57);
	BOOST_ASSERT(pod_d  == 1.57);

	out << "safe double division: " << safe_d << endl;
	out << "reference value: "      << pod_d << endl;

	pod_d = 100; // setting reference value will not be validated
	BOOST_ASSERT(pod_d  == 100);
	BOOST_ASSERT(safe_d == 100);

	out << "safe double cannot check reference change: " << safe_d << endl;
	out << "reference value: "      << pod_d << endl;

	try {
		safe_d.validate();
	}
	catch ( safe_dbl::validation_type::exception_type const& e ) {
		out << "expected exception caught: " << e.what() << endl;
	}

	out << endl;
}


typedef safe<
	short,
	min_validation<short, min_value<3> >,
	no_initial<short>
> safe_short;
void test_const(std::ostream& out)
{
	out << " - invalid initial value test - " << endl;
// invalid initial value: 0 is less than 3
// debug will throw exception
/*
#ifndef NDEBUG
	try {
		safe_short bad_i; // invalid initial value
		BOOST_ASSERT(bad_i == 0);
	}
	catch (safe_short::validation_type::exception_type const& e ) {
		out << "expected exception caught: " << e.what() << endl;
	}
// release versions will continue unvalidated
#else
	safe_short bad_i; // invalid initial value
	try {
		bad_i.validate();
		throw std::runtime_error("error: expected exception not thrown");
	}
	catch (safe_short::validation_type::exception_type const& e ) {
		out << "expected exception caught: " << e.what() << endl;
	}
	BOOST_ASSERT(bad_i == 0);
#endif
*/
	safe_short i(3);

	BOOST_ASSERT(i == 3);
	out << "constructed value: " << i << endl;

	out << endl;
}

#pragma warning (disable:4996)
#include <boost/date_time/gregorian/gregorian.hpp>

using boost::gregorian::date;

struct date_validation {
	static void validate(date const& d) {
		if ( d.is_not_a_date() )
			throw std::runtime_error("Date must be initialized");
	}
};

struct date_initial {
	inline static date value() { return boost::gregorian::day_clock::local_day(); }
};

typedef safe<date, date_validation> uninitialized_date;
typedef safe<date, date_validation, date_initial> safe_date;

void test_date (std::ostream& out)
{
	out << " - date test - " << endl;
// debug will throw exception
/*
#ifndef NDEBUG
	try {
		uninitialized_date ud;
	}
	catch ( std::runtime_error const& e ) {
		out << "expected exception caught: " << e.what() << endl;
	}
#else
	uninitialized_date ud;
	try {
		ud.validate();
		throw std::runtime_error("error: expected exception not thrown");
	}
	catch ( std::runtime_error const& e ) {
		out << "expected exception caught: " << e.what() << endl;
	}
#endif
*/
	safe_date sd;
	BOOST_ASSERT(sd == date_initial::value());
	out << "initial value: " << sd << endl;

	out << endl;
}
