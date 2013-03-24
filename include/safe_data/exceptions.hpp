/*
Copyright Mike Naquin, 2006. All rights reserved.

File:
	safe_data/common_exceptions.hpp

Created: 2006.05.14

Description:
	Common exceptions to be thrown during validations in safe<>.
*/

#ifndef SAFE_DATA_COMMON_EXCEPTIONS_MPN_14MAY2006_HPP
#define SAFE_DATA_COMMON_EXCEPTIONS_MPN_14MAY2006_HPP

#include "safe_detail.hpp"

#include <stdexcept>
#include <string>
#include <sstream>

namespace safe_data {


template <class T, class min_value>
struct min_exception : public std::out_of_range {
	typedef std::out_of_range base;
	typedef T value_type;
	typedef min_value value;
	typedef typename safe_detail::select_types<T>::types::argument_type argument_type;

	explicit min_exception(argument_type data) : base(min_msg(data)) { }
	explicit min_exception(std::string const& msg) : base(msg) { }

	static std::string min_msg(argument_type data)
	{
		std::ostringstream ss;
		ss << "The value " << data << " must not be less than "
			<< value() << '.';
		return ss.str();
	}
};

template <class T, class max_value>
struct max_exception : public std::out_of_range {
	typedef std::out_of_range base;
	typedef T value_type;
	typedef max_value value;
	typedef typename safe_detail::select_types<T>::types::argument_type argument_type;

	explicit max_exception(argument_type data) : base(max_msg(data)) { }
	explicit max_exception(std::string const& msg) : base(msg) { }

	static std::string max_msg(argument_type data)
	{
		std::ostringstream ss;
		ss  << "The value " << data
			<< " must not be greater than "
			<< value()
			<< '.';
		return ss.str();
	}
};

template <class T, class min_value, class max_value>
struct range_exception : public std::out_of_range {
	typedef std::out_of_range base;
	typedef T value_type;
	typedef min_value lower;
    typedef max_value upper;
	typedef typename safe_detail::select_types<T>::types::argument_type argument_type;

	explicit range_exception(argument_type data) :
		base(range_msg(data))
	{ }
	explicit range_exception(std::string const& msg) : base(msg) { }

	static std::string range_msg(argument_type data)
	{
		std::ostringstream ss;
		ss  << "The value " << data << " must be between "
			<< lower() << " and "
			<< upper() << '.';
		return ss.str();
	}
};

template <class T, class size>
struct size_exception : public std::length_error {
	typedef std::length_error base;
	typedef T value_type;
	typedef size value;
	typedef typename safe_detail::select_types<T>::types::argument_type argument_type;

	explicit size_exception(argument_type data) :
		base(size_msg(data)) { }
	explicit size_exception(std::string const& msg) : base(msg) { }

	static std::string size_msg(argument_type data)
	{
		std::ostringstream ss;
		ss  << "The size " << data.size()
			<< " must not exceed "
			<< value()
			<< '.';
		return ss.str();
	}
};

template <class T, class length>
struct str_length_exception : public std::length_error {
	typedef std::length_error base;
	typedef T value_type;
	typedef length value;

	typedef typename safe_detail::select_types<T>::types types;
	typedef typename types::argument_type argument_type;
	typedef typename types::raw_type             raw_type;
	typedef typename raw_type::size_type     length_type;

	str_length_exception(argument_type data, length_type const& len) :
		base(length_msg(data, len))
	{ }
	explicit str_length_exception(std::string const& msg) : base(msg) { }

	static std::string length_msg(argument_type data, length_type const& )
	{
		std::ostringstream ss;
		ss  << "The length of " << data
			<< " must not exceed "
			<< value()
			<< '.';
		return ss.str();
	}
};


} // namespace safe_data

#endif
