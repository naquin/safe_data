/*
Copyright Mike Naquin, 2006. All rights reserved.

File:
	safe_data/io.hpp

Created: 2006.05.14

Description:
	Input/output operators for safe<>.
*/

#ifndef SAFE_DATA_IO_MPN_14MAY2006_HPP
#define SAFE_DATA_IO_MPN_14MAY2006_HPP

#include "safe_fwd.hpp"

#include <iosfwd>

namespace safe_data {

template <class T, class V, class I, class Elem, class Traits>
inline std::basic_ostream<Elem, Traits>&
	operator<< (
		std::basic_ostream<Elem, Traits>& out,
		safe<T,V,I> const& s
	)
{
	out << s.data();
	return out;
}

template <class T, class V, class I, class Elem, class Traits>
inline std::basic_istream<Elem, Traits>&
	operator<< (
		std::basic_istream<Elem, Traits>& in,
		safe<T,V,I>& s
	)
{
	typename safe<T,V,I>::raw_type data;
	in >> data;
	s = data;
	return in;
}

} // namespace safe_data

#endif
