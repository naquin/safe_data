/*
Copyright Mike Naquin, 2006. All rights reserved.

File:
	safe_data/common_values.hpp

Created: 2006.05.14

Description:
	Value policies to use with safe<>.
*/

#ifndef SAFE_DATA_COMMON_VALUES_MPN_14MAY2006_HPP
#define SAFE_DATA_COMMON_VALUES_MPN_14MAY2006_HPP

namespace safe_data {


template <int initial_val>
struct initial_value {
	static inline int value() { return initial_val; }
};

template <int minimum_value>
struct min_value {
	enum { min_val = minimum_value };
};

template <int maximum_value>
struct max_value {
	enum { max_val = maximum_value };
};

template <int minimum_value, int maximum_value>
struct range_value {
	enum { min_val = minimum_value };
	enum { max_val = maximum_value };
};


} // namespace safe_data

#endif
