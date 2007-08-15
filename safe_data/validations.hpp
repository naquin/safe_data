/*
Copyright Mike Naquin, 2006. All rights reserved.

File:
	safe_data/common_validations.hpp

Created: 2006.05.14

Description:
	Generic validations to use with safe<>.
*/

#ifndef SAFE_DATA_COMMON_VALIDATIONS_MPN_14MAY2006_HPP
#define SAFE_DATA_COMMON_VALIDATIONS_MPN_14MAY2006_HPP

#include "safe_detail.hpp"

#include "exceptions.hpp"

namespace safe_data {


// min validations
template <class T, class validation, class exception = min_exception<T, validation> >
struct min_validation {
	typedef validation validation_type;
	typedef exception  exception_type;
	typedef typename safe_detail::select_types<T>::types::argument_type argument_type;
	static inline void validate(argument_type data)
	{
		if ( data < validation::min_val )
			throw exception_type(data);
	}
};

template <class T, class validation, class exception = min_exception<T, validation> >
struct min_validation_lte {
	typedef validation validation_type;
	typedef exception  exception_type;
	typedef typename safe_detail::select_types<T>::types::argument_type argument_type;
	static inline void validate(argument_type data)
	{
		if ( data <= validation::min_val )
			throw exception_type(data);
	}
};

// maximum validations
template <class T, class validation, class exception = max_exception<T, validation> >
struct max_validation {
	typedef validation validation_type;
	typedef exception  exception_type;
	typedef typename safe_detail::select_types<T>::types::argument_type argument_type;
	static inline void validate(argument_type data)
	{
		if ( data > validation::max_val )
			throw exception_type(data);
	}
};

template <class T, class validation, class exception = max_exception<T, validation> >
struct max_validation_gte {
	typedef validation validation_type;
	typedef exception  exception_type;
	typedef typename safe_detail::select_types<T>::types::argument_type argument_type;
	static inline void validate(argument_type data)
	{
		if ( data >= validation::max_val )
			throw exception_type(data);
	}
};

// range validations
template <class T, class validation, class exception = range_exception<T, validation> >
struct range_validation {
	typedef validation validation_type;
	typedef exception  exception_type;
	typedef typename safe_detail::select_types<T>::types::argument_type argument_type;
	static inline void validate(argument_type data)
	{
		if ( data < validation::min_val || data > validation::max_val )
			throw exception_type(data);
	}
};

template <class T, class validation, class exception = range_exception<T, validation> >
struct range_validation_min_lte_max_gte {
	typedef validation validation_type;
	typedef exception  exception_type;
	typedef typename safe_detail::select_types<T>::types::argument_type argument_type;
	static inline void validate(argument_type data)
	{
		if ( data <= validation::min_val || data >= validation::max_val )
			throw exception_type(data);
	}
};

template <class T, class validation, class exception = range_exception<T, validation> >
struct range_validation_min_lte {
	typedef validation validation_type;
	typedef exception  exception_type;
	typedef typename safe_detail::select_types<T>::types::argument_type argument_type;
	static inline void validate(argument_type data)
	{
		if ( data <= validation::min_val || data > validation::max_val )
			throw exception_type(data);
	}
};

template <class T, class validation, class exception = range_exception<T, validation> >
struct range_validation_max_gte {
	typedef validation validation_type;
	typedef exception  exception_type;
	typedef typename safe_detail::select_types<T>::types::argument_type argument_type;
	static inline void validate(argument_type data)
	{
		if ( data < validation::min_val || data >= validation::max_val )
			throw exception_type(data);
	}
};

// size validations for any container with size()
template <class T, class validation, class exception = size_exception<T, validation> >
struct size_validation {
	typedef validation validation_type;
	typedef exception  exception_type;
	typedef typename safe_detail::select_types<T>::types::argument_type argument_type;
	static inline void validate(argument_type container) {
		if ( container.size() > validation::max_val )
			throw exception_type(container);
	}
};

// length validations for strings
template <class T, class validation, class exception = str_length_exception<T, validation> >
struct str_length_validation {
	typedef validation validation_type;
	typedef exception  exception_type;
	typedef typename safe_detail::select_types<T>::types::argument_type argument_type;
	static inline void validate(argument_type str) {
		if ( str.length() > validation::max_val )
			throw exception_type(str, str.length());
	}
};


} // namespace safe_data

#endif
