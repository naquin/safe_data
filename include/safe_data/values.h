/*
Copyright Mike Naquin, 2006. All rights reserved.

File:
	safe_data/common_values.h

Created: 2006.05.14

Description:
	Value policies to use with safe<>.
*/

#ifndef SAFE_DATA_COMMON_VALUES_MPN_14MAY2006_HPP
#define SAFE_DATA_COMMON_VALUES_MPN_14MAY2006_HPP

#include <boost/mpl/integral_c.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/size_t.hpp>
#include <boost/mpl/string.hpp>

namespace safe_data {

// only use this when there is no alternative in boost MPL, like for doubles
#define SAFE_DATA_INITIAL_VALUE(name, type, value)                              \
    struct name                                                                 \
    {                                                                           \
        operator type() const                                                   \
        {                                                                       \
            return value;                                                       \
        }                                                                       \
    };

template <class T>
struct c_str {
    typedef boost::mpl::c_str<T> type;
    operator const char*() const { return type::value; }
};

} // namespace safe_data

#endif
