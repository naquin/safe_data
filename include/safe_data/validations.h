/*
Copyright Mike Naquin, 2006. All rights reserved.

File:
	safe_data/common_validations.h

Created: 2006.05.14

Description:
	Generic validations to use with safe<>.
*/

#ifndef SAFE_DATA_COMMON_VALIDATIONS_MPN_14MAY2006_HPP
#define SAFE_DATA_COMMON_VALIDATIONS_MPN_14MAY2006_HPP

#include "safe_data/safe_detail.h"

#include "safe_data/exceptions.h"

namespace safe_data {


// min validations
template <class T, class min_value, class exception = min_exception<T, min_value> >
struct min_validation {
	typedef min_value value;
	typedef exception exception_type;
	typedef typename safe_detail::select_types<T>::types::argument_type argument_type;
	static inline void validate(argument_type data)
	{
		if ( data < value() )
			throw exception_type(data);
	}
};

template <class T, class min_value, class exception = min_exception<T, min_value> >
struct min_validation_lte {
	typedef min_value value;
	typedef exception exception_type;
	typedef typename safe_detail::select_types<T>::types::argument_type argument_type;
	static inline void validate(argument_type data)
	{
		if ( data <= value() )
			throw exception_type(data);
	}
};

// maximum validations
template <class T, class max_value, class exception = max_exception<T, max_value> >
struct max_validation {
	typedef max_value value;
	typedef exception  exception_type;
	typedef typename safe_detail::select_types<T>::types::argument_type argument_type;
	static inline void validate(argument_type data)
	{
		if ( data > value() )
			throw exception_type(data);
	}
};

template <class T, class max_value, class exception = max_exception<T, max_value> >
struct max_validation_gte {
	typedef max_value value;
	typedef exception exception_type;
	typedef typename safe_detail::select_types<T>::types::argument_type argument_type;
	static inline void validate(argument_type data)
	{
		if ( data >= value() )
			throw exception_type(data);
	}
};

// range validations
template <class T, class min_value, class max_value, class exception = range_exception<T, min_value, max_value> >
struct range_validation {
    typedef min_value lower;
    typedef max_value upper;
	typedef exception exception_type;
	typedef typename safe_detail::select_types<T>::types::argument_type argument_type;
	static inline void validate(argument_type data)
	{
		if ( data < lower() || data > upper() )
			throw exception_type(data);
	}
};

template <class T, class min_value, class max_value, class exception = range_exception<T, min_value, max_value> >
struct range_validation_min_lte_max_gte {
    typedef min_value lower;
    typedef max_value upper;
	typedef exception exception_type;
	typedef typename safe_detail::select_types<T>::types::argument_type argument_type;
	static inline void validate(argument_type data)
	{
		if ( data <= lower() || data >= upper() )
			throw exception_type(data);
	}
};

template <class T, class min_value, class max_value, class exception = range_exception<T, min_value, max_value> >
struct range_validation_min_lte {
    typedef min_value lower;
    typedef max_value upper;
	typedef exception exception_type;
	typedef typename safe_detail::select_types<T>::types::argument_type argument_type;
	static inline void validate(argument_type data)
	{
		if ( data <= lower() || data > upper() )
			throw exception_type(data);
	}
};

template <class T, class min_value, class max_value, class exception = range_exception<T, min_value, max_value> >
struct range_validation_max_gte {
    typedef min_value lower;
    typedef max_value upper;
	typedef exception exception_type;
	typedef typename safe_detail::select_types<T>::types::argument_type argument_type;
	static inline void validate(argument_type data)
	{
		if ( data < lower() || data >= upper() )
			throw exception_type(data);
	}
};

// size validations for any container with size()
template <class T, class size, class exception = size_exception<T, size> >
struct size_validation {
	typedef size value;
	typedef exception  exception_type;
	typedef typename safe_detail::select_types<T>::types::argument_type argument_type;
	static inline void validate(argument_type container) {
		if ( container.size() > value() )
			throw exception_type(container);
	}
};

// length validations for strings
template <class T, class length, class exception = str_length_exception<T, length> >
struct str_length_validation {
	typedef length value;
	typedef exception  exception_type;
	typedef typename safe_detail::select_types<T>::types::argument_type argument_type;
	static inline void validate(argument_type str) {
		if ( str.length() > value() )
			throw exception_type(str, str.length());
	}
};


} // namespace safe_data

#endif
