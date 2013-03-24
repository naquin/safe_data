/*
Copyright Mike Naquin, 2006. All rights reserved.

File:
	safe_data/safe_fwd.hpp

Created: 2006.05.14

Description:
	Validated data type
*/

#ifndef SAFE_DATA_SAFE_FWD_MPN_14MAY2006_HPP
#define SAFE_DATA_SAFE_FWD_MPN_14MAY2006_HPP

namespace safe_data {

// default value
//template <class T> class no_initial;

// data validation
template <class T> class no_validation;

// safe
template <
	class T,
	class validation    = no_validation<T>,
	class initial_value = T
>
class safe;

} // namespace safe_data


#endif
