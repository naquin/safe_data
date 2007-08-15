/*
Copyright Mike Naquin, 2006. All rights reserved.

File:
	safe_data/compare.hpp

Created: 2006.05.14

Description:
	Comparison operators for safe<>. These make the syntax easier when
	implicit conversions do not work with safe<>.
*/

#ifndef SAFE_DATA_COMPARE_MPN_14MAY2006_HPP
#define SAFE_DATA_COMPARE_MPN_14MAY2006_HPP

#include "safe_fwd.hpp"

namespace safe_data {


// ==
template <class T, class V, class I, class T2, class V2, class I2>
inline bool operator== (safe<T,V,I> const& lhs, safe<T2,V2,I2> const& rhs)
{ return lhs.data() == rhs.data(); }

template <class T, class V, class I, class Y>
inline bool operator== (safe<T,V,I> const& lhs, Y const& rhs)
{ return lhs.data() == rhs; }

template <class T, class V, class I, class Y>
inline bool operator== (Y const& lhs, safe<T,V,I> const& rhs)
{ return lhs == rhs.data(); }


// <
template <class T, class V, class I, class T2, class V2, class I2>
inline bool operator< (safe<T,V,I> const& lhs, safe<T2,V2,I2> const& rhs)
{ return lhs.data() < rhs.data(); }

template <class T, class V, class I, class Y>
inline bool operator< (safe<T,V,I> const& lhs, Y const& rhs)
{ return lhs.data() < rhs; }

template <class T, class V, class I, class Y>
inline bool operator< (Y const& lhs, safe<T,V,I> const& rhs)
{ return lhs < rhs.data(); }


// !=
template <class T, class V, class I, class T2, class V2, class I2>
inline bool operator!= (safe<T,V,I> const& lhs, safe<T2,V2,I2> const& rhs)
{ return !(lhs == rhs); }

template <class T, class V, class I, class Y>
inline bool operator!= (safe<T,V,I> const& lhs, Y const& rhs)
{ return !(lhs == rhs); }

template <class T, class V, class I, class Y>
inline bool operator!= (Y const& lhs, safe<T,V,I> const& rhs)
{ return !(lhs == rhs); }


// >
template <class T, class V, class I, class T2, class V2, class I2>
inline bool operator> (safe<T,V,I> const& lhs, safe<T2,V2,I2> const& rhs)
{ return rhs < lhs; }

template <class T, class V, class I, class Y>
inline bool operator> (safe<T,V,I> const& lhs, Y const& rhs)
{ return rhs < lhs; }

template <class T, class V, class I, class Y>
inline bool operator> (Y const& lhs, safe<T,V,I> const& rhs)
{ return rhs < lhs; }


// <=
template <class T, class V, class I, class T2, class V2, class I2>
inline bool operator<= (safe<T,V,I> const& lhs, safe<T2,V2,I2> const& rhs)
{ return !(rhs < lhs); }

template <class T, class V, class I, class Y>
inline bool operator<= (safe<T,V,I> const& lhs, Y const& rhs)
{ return !(rhs < lhs); }

template <class T, class V, class I, class Y>
inline bool operator<= (Y const& lhs, safe<T,V,I> const& rhs)
{ return !(rhs < lhs); }


// >=
template <class T, class V, class I, class T2, class V2, class I2>
inline bool operator>= (safe<T,V,I> const& lhs, safe<T2,V2,I2> const& rhs)
{ return (!lhs < rhs); }

template <class T, class V, class I, class Y>
inline bool operator>= (safe<T,V,I> const& lhs, Y const& rhs)
{ return (!lhs < rhs); }

template <class T, class V, class I, class Y>
inline bool operator>= (Y const& lhs, safe<T,V,I> const& rhs)
{ return (!lhs < rhs); }


} // namespace safe_data

#endif
