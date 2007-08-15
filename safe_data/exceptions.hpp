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


template <class T, class validation>
struct min_exception : public std::out_of_range {
	typedef std::out_of_range base;
	typedef T value_type;
	typedef validation validation_type;
	typedef typename safe_detail::select_types<T>::types::argument_type argument_type;

	explicit min_exception(argument_type data) : base(min_msg(data)) { }
	explicit min_exception(std::string const& msg) : base(msg) { }
//	virtual ~min_exception() { }

	static std::string min_msg(argument_type data)
	{
		std::ostringstream ss;
		ss << "The value " << data << " must not be less than "
			<< validation_type::min_val << '.';
		return ss.str();
	}
};

template <class T, class validation>
struct max_exception : public std::out_of_range {
	typedef std::out_of_range base;
	typedef T value_type;
	typedef validation validation_type;
	typedef typename safe_detail::select_types<T>::types::argument_type argument_type;

	explicit max_exception(argument_type data) : base(max_msg(data)) { }
	explicit max_exception(std::string const& msg) : base(msg) { }

//	virtual ~max_exception() { }

	static std::string max_msg(argument_type data)
	{
		std::ostringstream ss;
		ss  << "The value " << data
			<< " must not be greater than "
			<< validation_type::max_val
			<< '.';
		return ss.str();
	}
};

template <class T, class validation>
struct range_exception : public std::out_of_range {
	typedef std::out_of_range base;
	typedef T value_type;
	typedef validation validation_type;
	typedef typename safe_detail::select_types<T>::types::argument_type argument_type;

	explicit range_exception(argument_type data) :
		base(range_msg(data))
	{ }
	explicit range_exception(std::string const& msg) : base(msg) { }
//	virtual ~range_exception() { }

	static std::string range_msg(argument_type data)
	{
		std::ostringstream ss;
		ss  << "The value " << data << " must be between "
			<< validation_type::min_val << " and "
			<< validation_type::max_val << '.';
		return ss.str();
	}
};

template <class T, class validation>
struct size_exception : public std::length_error {
	typedef std::length_error base;
	typedef T value_type;
	typedef validation validation_type;
	typedef typename safe_detail::select_types<T>::types::argument_type argument_type;

	explicit size_exception(argument_type data) :
		base(size_msg(data)) { }
	explicit size_exception(std::string const& msg) : base(msg) { }
	virtual ~size_exception() { }

	static std::string size_msg(argument_type data)
	{
		std::ostringstream ss;
		ss  << "The size " << data.size()
			<< " must not exceed "
			<< validation_type::max_val
			<< '.';
		return ss.str();
	}
};

template <class T, class validation>
struct str_length_exception : public std::length_error {
	typedef std::length_error base;
	typedef T value_type;
	typedef validation validation_type;

	typedef typename safe_detail::select_types<T>::types types;
	typedef typename types::argument_type argument_type;
	typedef typename types::raw_type             raw_type;
	typedef typename raw_type::size_type     length_type;

	str_length_exception(argument_type data, length_type const& length) :
		base(length_msg(data, length))
	{ }
	explicit str_length_exception(std::string const& msg) : base(msg) { }
//	virtual ~str_length_exception() { }

	static std::string length_msg(argument_type data, length_type const& )
	{
		std::ostringstream ss;
		ss  << "The length of " << data
			<< " must not exceed "
			<< validation_type::max_val
			<< '.';
		return ss.str();
	}
};


} // namespace safe_data

#endif
