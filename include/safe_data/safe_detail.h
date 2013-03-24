/*
Copyright Mike Naquin, 2006. All rights reserved.

File:
	safe_data/safe_detail.h

Created: 2006.05.14

Description:
	Validated data type
*/

#ifndef SAFE_DATA_SAFE_DETAIL_MPN_14MAY2006_HPP
#define SAFE_DATA_SAFE_DETAIL_MPN_14MAY2006_HPP

#include "safe_data/safe_fwd.h"

#include "boost/mpl/if.hpp"
#include "boost/type_traits/remove_reference.hpp"
#include "boost/type_traits/is_reference.hpp"

namespace safe_data {
namespace safe_detail {

template<class T>
struct not_ref_types {
	typedef T        raw_type;
	typedef T        storage_type;

	typedef T const& reference_const_type;
	typedef T      & reference_type;
	typedef T const* pointer_const_type;
	typedef T      * pointer_type;
	typedef T const& argument_type;
};

template<class T>
struct ref_types {
	typedef typename boost::remove_reference<T>::type raw_type;
	typedef T storage_type;

	typedef raw_type & reference_const_type;
	typedef raw_type & reference_type;
	typedef raw_type * pointer_const_type;
	typedef raw_type * pointer_type;
	typedef raw_type & argument_type;
};

template <class T>
struct select_types {
    typedef typename boost::is_reference<T>::type is_reference_predicate ;

    typedef typename boost::mpl::if_<
		is_reference_predicate,
		ref_types<T>,
		not_ref_types<T>
	>::type types ;
};

} // namespace safe_detail
} // namespace safe_data

#endif
