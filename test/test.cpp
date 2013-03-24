/*
Copyright Mike Naquin, 2006. All rights reserved.
File:
	test.cpp

Created: 2006.05.14

Description:
	Automated tests for safe_data. There should be no unexpected exceptions
	when running main().
*/

#include <gtest/gtest.h>

#include "safe_data/safe.h"
#include "safe_data/values.h"
#include "safe_data/validations.h"
#include "safe_data/exceptions.h"

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

using boost::mpl::integral_c;
using boost::mpl::int_;

using safe_data::min_validation;
using safe_data::max_validation;
using safe_data::range_validation;
using safe_data::str_length_validation;

SAFE_DATA_INITIAL_VALUE(percent_min, double, 0.0)
SAFE_DATA_INITIAL_VALUE(percent_max, double, 1.0)

template <class T, class min_value, class max_value>
struct percent_exception : public range_exception<T, min_value, max_value> {
	typedef T value_type;
	typedef T const& argument_type;
	typedef min_value lower;
	typedef max_value upper;

	explicit percent_exception(argument_type data) :
		range_exception<T, min_value, max_value>(percent_msg(data))
	{ }
	explicit percent_exception(std::string const& msg) :
		range_exception<T, min_value, max_value>(msg)
	{ }

	static std::string percent_msg(argument_type data)
	{
		std::ostringstream ss;
		ss  << "The percent " << (data * 100) << "% must be between "
			<< (lower() * 100) << "% and "
			<< (upper() * 100) << "%.";
		return ss.str();
	}
};

template <class T,
          class min_value = percent_min,
          class max_value = percent_max,
	      class exception = percent_exception<T, min_value, max_value>
>
struct percent_validation : public range_validation<T, min_value, max_value, exception> {
	typedef range_validation<T, min_value, max_value, exception> base;
	typedef typename base::lower lower;
	typedef typename base::upper upper;
	typedef typename base::exception_type  exception_type;
	typedef typename base::argument_type   argument_type;

	using base::validate;
};

typedef safe<double, percent_validation<double> > percent;

TEST(SafeDataTest, Percent)
{
	percent p;

	EXPECT_EQ(0, p);

	p = 0.5;
	EXPECT_EQ(0.5, p);

    // test against min value
    EXPECT_THROW(p = -1.5,
                 percent::validation_type::exception_type);

	// should still be 50% at this point
	EXPECT_EQ(0.5, p);

    // test against max value
    EXPECT_THROW(p = 2, percent::validation_type::exception_type);
    
	EXPECT_EQ(0.5, p);

	EXPECT_NO_THROW(p = 1);

	// test swap
	percent p2;
	p.swap(p2);

	EXPECT_EQ(0.0, p);
	EXPECT_EQ(1.0, p2);
}

// int test
typedef safe<int, max_validation<int, int_<32> >, int_<8> > safe_int;

TEST(SafeDataTest, Int)
{
	safe_int i; // initial value set to 8

	EXPECT_EQ(8, i);

	i = 16;
	EXPECT_EQ(16, i);

	++i;
	EXPECT_EQ(17, i);

    // test against max value
    EXPECT_THROW(i = 33, safe_int::validation_type::exception_type);

	EXPECT_EQ(17, i);

	// no min validation
	i = -128;
	EXPECT_NO_THROW(i = -128);
}

#include "safe_data/compare.h"
#include "safe_data/io.h"
#include "safe_data/operators.h"

typedef safe_data::c_str<boost::mpl::string<'f', 'o', 'o'> > str_initial;

// string test
typedef safe<string, str_length_validation<string, boost::mpl::size_t<8> >, str_initial> safe_str;

void test_str(std::ostream& out)
{
	safe_str s; // initial "foo"

	EXPECT_EQ("foo", s); // use boost/safe_data/compare.h or get(s) or s.data()

	s += " bar"; // use boost/safe_data/operators.h or s = get(s) + " bar"
	EXPECT_EQ("foo bar", s);

	EXPECT_THROW(s = "long " + get(s), // operator+ cannot const char* to string
                                       // can also string("long ") + s
                                       // or "long " + s.data()
                 safe_str::validation_type::exception_type);

	EXPECT_EQ("foo bar", s);
}

typedef safe<double&, range_validation<double, int_<0>, int_<10> > > safe_dbl;

void test_ref(std::ostream& out)
{
	double pod_d = 3.14;

	safe_dbl safe_d(pod_d);
	EXPECT_EQ(3.14, safe_d);

	EXPECT_THROW(safe_d *= 4, safe_dbl::validation_type::exception_type);

	EXPECT_EQ(3.14, safe_d);
	EXPECT_EQ(3.14, pod_d);

	safe_d /= 2;
	EXPECT_EQ(1.57, safe_d);
	EXPECT_EQ(1.57, pod_d);

	pod_d = 100; // setting reference value will not be validated
	EXPECT_EQ(100, pod_d);
	EXPECT_EQ(100, safe_d);

	EXPECT_THROW(safe_d.validate(), safe_dbl::validation_type::exception_type);
}


typedef safe<
	short,
	min_validation<short, integral_c<short, 3> >,
	no_initial<short>
> safe_short;

TEST(SafeDataTest, Const)
{
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

	EXPECT_EQ(3, i); // constructed value
}

#include <boost/date_time/gregorian/gregorian.hpp>

using boost::gregorian::date;

struct date_validation {
	static void validate(date const& d) {
		if ( d.is_not_a_date() )
			throw std::runtime_error("Date must be initialized");
	}
};

SAFE_DATA_INITIAL_VALUE(date_initial, date, boost::gregorian::day_clock::local_day())

typedef safe<date, date_validation> uninitialized_date;
typedef safe<date, date_validation, date_initial> safe_date;

TEST(SafeDataTest, Date)
{
// debug will throw exception

#ifndef NDEBUG
    EXPECT_THROW(uninitialized_date ud, std::runtime_error);
#else
   EXPECT_NO_THROW(uninitialized_date ud);
   EXPECT_THROW(ud.validate(), std::runtime_error)
#endif

	safe_date sd;
	EXPECT_EQ(date_initial(), sd);
}
