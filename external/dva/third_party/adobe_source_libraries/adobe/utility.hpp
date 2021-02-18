/*
 Copyright 2005-2007 Adobe Systems Incorporated
 Distributed under the MIT License (see accompanying file LICENSE_1_0_0.txt
 or a copy at http://stlab.adobe.com/licenses.html)
 */

/*************************************************************************************************/

#ifndef ADOBE_UTILITY_HPP
#define ADOBE_UTILITY_HPP

/*************************************************************************************************/

#include <adobe/config.hpp>

#include <adobe/utility/pair.hpp>
#include <adobe/utility/ignore_unused.hpp>

/*************************************************************************************************/

/*!
 \defgroup utility Utility
 \ingroup asl_libraries
 
 */

namespace adobe 
{
	// makes a value for an non-associative container
	template<typename T, typename ValueType>
	inline typename T::value_type
	make_value(const ValueType& value)
	{
		return typename T::value_type(value);
	}
	
	// makes a value for an associative container
	template<typename T, typename KeyType, typename MappedType>
	inline typename T::value_type
	make_value(const KeyType& key, const MappedType& value)
	{
		return typename T::value_type(typename T::key_type(key), typename T::mapped_type(value));
	}
	
} // namespace adobe

/*************************************************************************************************/
// ADOBE_UTILITY_HPP
#endif

/*************************************************************************************************/
