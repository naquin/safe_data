/*
Copyright Mike Naquin, 2006. All rights reserved.

File:
	safe_data/safe.hpp

Created: 2006.05.14

Description:
	Validated data type
*/

#ifndef SAFE_DATA_SAFE_MPN_14MAY2006_HPP
#define SAFE_DATA_SAFE_MPN_14MAY2006_HPP

#include "safe_fwd.hpp"
#include "safe_detail.hpp"

namespace safe_data {


// initial value
template <class T> class no_initial {
	typedef typename safe_detail::select_types<T>::types types;
public:
	typedef typename types::raw_type             raw_type;
    // typedef typename types::reference_const_type reference_const_type;

	inline static raw_type value() { return raw_type(); }
    // inline static reference_const_type value() { return val; }
// private:
//  static raw_type const val;
};

// template <class T>
// typename no_initial<T>::raw_type const no_initial<T>::val = no_initial<T>::raw_type();


// data validation
template <class T> class no_validation {
public:
	typedef typename safe_detail::select_types<T>::types::argument_type argument_type;

	static inline void validate(argument_type /*data*/ ) { }
};


// safe - throws an exception when new data does not pass validation
template <class T, class validation_attributes, class initial_value>
class safe {
	typedef typename safe_detail::select_types<T>::types types;
public:
	typedef T value_type;
	typedef validation_attributes validation_type;
	typedef initial_value         initial_type;

	typedef typename types::raw_type             raw_type;
	typedef typename types::storage_type         storage_type;
	typedef typename types::reference_type       reference_type;
	typedef typename types::reference_const_type reference_const_type;
	typedef typename types::pointer_type         pointer_type;
	typedef typename types::pointer_const_type   pointer_const_type;
	typedef typename types::argument_type        argument_type;

// self
	safe() : data_(initial_type::value())
	{
		#ifndef NDEBUG
		validation_type::validate(data_);
		#endif
	}
	safe(safe const& rhs) : data_(rhs.data_) { }
	safe& operator= (safe const& rhs) { data_ = rhs.data_; return *this; }

// data
	safe(argument_type data) : data_(do_validation(data)) { }
	safe& operator= (argument_type data) { data_ = do_validation(data); return *this; }

// similar types
	template <class U>
	safe(U const& data) : data_(do_validation(data)) { }
	template <class U>
	safe& operator= (U const& data) { data_ = do_validation(data); return *this; }

// similar safe data
	template <class U, class V, class I>
	safe(safe<U,V,I> const& rhs) : data_(do_validation(rhs.data())) { }
	template <class U, class V, class I>
	safe& operator= (safe<U,V,I> const& rhs) { data_ = do_validation(rhs.data()); return *this; }

// access
	operator reference_const_type     () const { return data_; }
	         reference_const_type data() const { return data_; }

	 inline void validate() const { validation_type::validate(data_); }

// unary operators
	inline bool operator! () const { return !data_; }

	inline raw_type operator+() const { return +data_; }
	inline raw_type operator-() const { return -data_; }
	inline raw_type operator~() const { return ~data_; }

	inline safe& operator++()
	{
		raw_type d(data_);
		data_ = do_validation(++d);
		return *this;
	}
	inline safe& operator--()
	{
		raw_type d(data_);
		data_ = do_validation(--d);
		return *this;
	}

	inline safe  operator++(int)
	{
		safe s(*this);
		raw_type d(data_);
		data_ = do_validation(++d);
		return s;
	}
	inline safe  operator--(int)
	{
		safe s(*this);
		raw_type d(data_);
		data_ = do_validation(--d);
		return s;
	}

	static inline reference_const_type do_validation(reference_const_type data)
	{ validation_type::validate(data); return data; }

private:
	storage_type data_;
};

template <class T, class V, class I>
typename safe<T,V,I>::reference_const_type get(safe<T,V,I> const& s) { return s.data(); }

} // namespace safe_data

#endif
