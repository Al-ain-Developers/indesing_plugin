//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/KeyValuePair.h $
//  
//  Owner: Mat Marcus (mmarcus)
//  
//  $Author: pmbuilder $
//  
//  $DateTime: 2020/11/06 13:08:29 $
//  
//  $Revision: #2 $
//  
//  $Change: 1088580 $
//  
//  Copyright 1997-2010 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//  
//  Purpose: clone of std::K2Pair based on STLPort 4.0 
//  
//========================================================================================

#pragma once
#ifndef __KEYVALUEPAIR__
#define __KEYVALUEPAIR__

#include <adobe/move.hpp>
#include <adobe/typeinfo.hpp>

/** KeyValuePair is similar in concept to std::pair. It is a bridge class between the old
	InDesign collection classes, and the newer stl-like collection classes. It enables 
	some of the old syntax that was used for BTLookup-based classes, which are now obsolete.
*/
template <class _T1, class _T2>
struct KeyValuePair {
	typedef object_type data_type; 

	typedef _T1 key_type;
	typedef _T2 value_type;

	KeyValuePair() : fKey(), fValue() {}
	
	/** Move constructor - moves the content of other into this object, leaving 'other' in destructible state
	 */
	KeyValuePair(adobe::move_from<KeyValuePair> other)
	: fKey(adobe::move(other.source.fKey)), fValue(adobe::move(other.source.fValue)) {}
	
	KeyValuePair(_T1 __a, _T2 __b)
	: fKey(adobe::move(__a)), fValue(adobe::move(__b)) {}

	KeyValuePair(const KeyValuePair &other) = default;
	KeyValuePair(KeyValuePair &&other) = default;
	KeyValuePair& operator=(const KeyValuePair &other) = default;
	KeyValuePair& operator=(KeyValuePair &&other) = default;

	friend inline void swap(KeyValuePair<_T1, _T2>& a, KeyValuePair<_T1, _T2>& b)
	{
		using std::swap;
		swap(a.fKey, b.fKey);
		swap(a.fValue, b.fValue);
	}

	_T1 fKey;
	_T2 fValue;
	
	/** Return the "left", or key of the pair.
		@return _T1& the key of the pair.
	*/
	_T1& Key() { return fKey; }
	
	/** Return the "right" or value of the pair.
		@return _T2& the value of the pair.
	*/
	_T2& Value() { return fValue; }

	/** Return the "left", or key of the pair.
		@return _T1& the key of the pair.
	*/
	const _T1& Key() const { return fKey; }

	/** Return the "right" or value of the pair.
		@return _T2& the value of the pair.
	*/
	const _T2& Value() const { return fValue; }
	
	/** Reset the value of the pair.
		@param val the new value
	*/
	void SetValue(const _T2& val) { fValue = val; }
};

// specialize adobe::type_info<> to avoid typeid problems across DLL boundaries
ADOBE_NAME_TYPE_2("keyvaluepair:indesign:adobe",KeyValuePair<T0,T1>)

/** Allow two KeyValuePairs to be compared for equality.
	@param __x the first value to compare
	@param __y the second value to compare
	@return bool true if the two KeyValuePairs are equivalent.
*/
template <class _T1, class _T2>
inline bool  operator==(const KeyValuePair<_T1, _T2>& __x, const KeyValuePair<_T1, _T2>& __y)
{ 
  return __x.Key() == __y.Key()  && __x.Value() == __y.Value(); 
}

/** Allow comparison between a KeyValuePair and a "key".
	This enables key-based lookup of a K2Vector of KeyValuePairs. The lookup client 
	code does a set of comparisons of the KeyValuePairs in a vector, comparing each 
	to the key. When it finds the key in a KeyValuePair, it returns the value of the 
	KeyValuePair. This method supplies the comparison operator used for the lookup. 
	@param __x	the KeyValuePair
	@param __y the key
	@return bool true if the KeyValuePair.key == key
*/
template <class _T1, class _T2>
inline bool  operator==(const KeyValuePair<_T1, _T2>& __x, const _T1& __y)
{ 
  return __x.Key() == __y; 
}

/** Allow comparison between a KeyValuePair and a "key".
	This enables key-based lookup of a K2Vector of KeyValuePairs. The lookup client 
	code does a set of comparisons of the KeyValuePairs in a vector, comparing each 
	to the key. When it finds the key in a KeyValuePair, it returns the value of the 
	KeyValuePair. This method supplies the comparison operator used for the lookup. 
	@param __x	the KeyValuePair
	@param __y the key
	@return bool true if the KeyValuePair.key == key
*/
template <class _T1, class _T2>
inline bool  operator==(const _T1& __y, const KeyValuePair<_T1, _T2>& __x)
{ 
  return __x.Key() == __y; 
}

/** Allow two KeyValuePairs to be sorted by key. This enables sorted arrays of 
	vectors of KeyValuePairs, where the sort is by key.
	@param __x the first value to compare
	@param __y the second value to compare
	@return bool true if the two key of the first pair is less than the key of the second pair
*/
template <class _T1, class _T2>
inline bool  operator<(const KeyValuePair<_T1, _T2>& __x, const KeyValuePair<_T1, _T2>& __y)
{ 
  return __x.Key() < __y.Key(); 
}

/** Allow comparison greater than/less than between a KeyValuePair and a "key". 
	@param __x	the KeyValuePair
	@param __y the key
	@return bool true if the KeyValuePair.key is less than the key
*/
template <class _T1, class _T2>
inline bool  operator<(const KeyValuePair<_T1, _T2>& __x, const _T1& __y)
{ 
  return __x.Key() < __y; 
}

/** Allow comparison greater than/less than between a KeyValuePair and a "key". 
	@param __y the key
	@param __x	the KeyValuePair
	@return bool true if the key is less than the KeyValuePair.key
*/
template <class _T1, class _T2>
inline bool  operator<(const _T1& __y, const KeyValuePair<_T1, _T2>& __x)
{ 
  return __y < __x.Key(); 
}

/** Allow two KeyValuePairs to be compared for inequality.
	@param __x the first KeyValuePair to compare
	@param __y the second KeyValuePair to compare
	@return bool true if the two KeyValuePairs are not equivalent.
*/
template <class _T1, class _T2>
inline bool  operator!=(const KeyValuePair<_T1, _T2>& __x, const KeyValuePair<_T1, _T2>& __y) {
  return !(__x == __y);
}

/** Compare two KeyValuePairs to be compared for greater than.
	@param __x the first KeyValuePair to compare
	@param __y the second KeyValuePair to compare
	@return bool true if the first KeyValuePair is greater than the second
*/
template <class _T1, class _T2>
inline bool  operator>(const KeyValuePair<_T1, _T2>& __x, const KeyValuePair<_T1, _T2>& __y) {
  return __y < __x;
}

/** Compare two KeyValuePairs to be compared for less than or equal.
	@param __x the first KeyValuePair to compare
	@param __y the second KeyValuePair to compare
	@return bool true if the first KeyValuePair is less than or equal the second
*/
template <class _T1, class _T2>
inline bool  operator<=(const KeyValuePair<_T1, _T2>& __x, const KeyValuePair<_T1, _T2>& __y) {
  return !(__y < __x);
}

/** Compare two KeyValuePairs to be compared for greater than or equal.
	@param __x the first KeyValuePair to compare
	@param __y the second KeyValuePair to compare
	@return bool true if the first KeyValuePair is greater than or equal the second
*/
template <class _T1, class _T2>
inline bool  operator>=(const KeyValuePair<_T1, _T2>& __x, const KeyValuePair<_T1, _T2>& __y) {
  return !(__x < __y);
}

/** Constructs a new KeyValuePair.
	@param __x  the key
	@param __y 	the value
	@return KeyValuePair<> the new pair
*/
template <class _T1, class _T2>
inline KeyValuePair<_T1, _T2>  K2make_keyvalue_pair(const _T1& __x, const _T2& __y)
{
  return KeyValuePair<_T1, _T2>(__x, __y);
}

// For sorted KeyValue vectors
template <class T>
struct KeyValueLess {
	bool operator()(const T& lhs, const T& rhs)
{
	return lhs.fKey < rhs.fKey;
}
}; 

/** Predicate object used for finding matching keys. Useful for find_if type expressions.
*/
template <class Key, class Value>
struct KeyMatchPredicate {
	/** Construct a new KeyMatchPredicate based on a key.
		@param key	 the key
		@return KeyMatchPredicate object
	*/
	KeyMatchPredicate(const Key& key) : fKey(key) {}
	
	/** Compare the supplied KeyValuePair with the key passed to the constructor.
		@param KeyValuePair to compare
		@return true if the key matches the KeyValuePair
	*/
	bool operator()(const KeyValuePair<Key,Value>& x) { return x.Key() == fKey; }
	Key fKey;
};


/** Return the index'th entry in the Container that matches the key.
	@param cont the collection class to search in
	@param key the key to search for
	@return int32 the index position of the key in the collection class, or -1 if not found
*/
template <class Key, class Container>
int32 FindLocation(const Container& cont, const Key& key)
{
	typedef typename Container::value_type KVP;
	typedef typename KVP::value_type Value;

	typename Container::const_iterator p = std::find_if(cont.begin(), cont.end(), KeyMatchPredicate<Key, Value>(key));
	return cont.end() == p ? -1 : p - cont.begin();
}


/** Predicate object used for finding matching values. Useful for finding the key the corresponds to
	a given value.
*/
template <class Key, class Value>
struct ValueMatchPredicate {
	ValueMatchPredicate(const Value& value) : fValue(value) {}
	bool operator()(const KeyValuePair<Key,Value>& x) { return x.Value() == fValue; }
	Value fValue;
};


/** Return the index'th entry in the Container that contains the value.
	@param cont the collection class to search in
	@param value the value to search for
	@return int32 the index position of the value in the collection class, or -1 if not found
*/
template <class Value, class Container>
int32 FindLocationByValue(const Container& cont, const Value& value)
{
	typedef typename Container::value_type KVP;
	typedef typename KVP::key_type Key;

	typename Container::const_iterator p = std::find_if(cont.begin(), cont.end(), ValueMatchPredicate<Key, Value>(value));
	return cont.end() == p ? -1 : p - cont.begin();
}


/** Insert a new <key, value> pair at the end of the collection. Allows duplicate entries
	to be added.
	@param cont the collection class to insert in
	@param key the key of the <key, value> pair to insert
	@param value the value  of the <key, value> pair to insert
*/
template <class Key, class Value, class Container>
void InsertKeyValue(Container& cont, const Key& key, const Value& val)
{
	cont.push_back(KeyValuePair<Key, Value>(key, val));
}



/** If the key is not already in the collection, insert the <key, value> pair at the
	end. Otherwise, replace the current value of the key with value.
	@param cont the collection class to insert in
	@param key the key of the <key, value> pair to insert
	@param value the value  of the <key, value> pair to insert
*/
template <class Key, class Value, class Container>
void InsertOrReplaceKeyValue(Container& cont, const Key& key, const Value& val)
{
	typename Container::iterator p = K2find(cont.begin(), cont.end(), key);
	if (p == cont.end())
		cont.push_back(KeyValuePair<Key, Value>(key, val));
	else
		p->SetValue(val);
}


/** Insert a value into a sorted container. Value is inserted in sorted order, rather than
	inserting and then re-sorting the container.
	@param cont the collection class to insert in
	@param value the value to insert
*/
template <class Value, class Container>
int32 InsertInSorted(Container& c, const Value& t)
{
	typename Container::iterator i = std::lower_bound(c.begin(), c.end(), t);
	i = c.insert(i, t);
	return i - c.begin();
}

/** Insert a <key, value> pair into a sorted container. The pair is inserted in sorted order, 
	rather than inserting and then re-sorting the container.
	@param cont the container to insert in
	@param key the key of the <key, value> pair to insert
	@param value the value  of the <key, value> pair to insert
*/
template <class Key, class Value, class Container>
int32 InsertKeyValueInSorted(Container& c,const Key& k,const Value& v)
{
	const KeyValuePair<Key, Value> el(k,v);
	
	typename Container::iterator i = std::lower_bound(c.begin(), c.end(), el);
	ASSERT(i == c.end() || *i != el);
	i = c.insert(i, el);
	return i - c.begin();
}

/** If the key is not already in the collection, insert the <key, value> pair in sorted
	order. Otherwise, replace the current value of the key with value.
	@param cont the collection class to insert in
	@param key the key of the <key, value> pair to insert
	@param value the value  of the <key, value> pair to insert
*/
template <class Key, class Value, class Container>
int32 InsertOrReplaceKeyValueInSorted(Container& c, const Key& k, const Value& v)
{
	typename Container::iterator i = std::lower_bound(c.begin(), c.end(), k);
	if (i == c.end() || i->Key() != k)
		i = c.insert( i, KeyValuePair<Key, Value>(k, v));
	else
		i->SetValue(v);
	return i - c.begin();
}

/** Find the index of the key's location in the container, where the container is in sorted order.
	@param cont the container to search in
	@param key the key of the <key, value> pair to search for
	@return index of the key's location in the container, or -1 if not found
*/
template <class Key, class Container>
int32 FindLocationInSorted(const Container& c, const Key& k)
{
	typename Container::const_iterator i = std::lower_bound(c.begin(), c.end(), k);
	return (i != c.end() && *i == k) ? (i - c.begin()) : -1;
}

#endif /* __KEYVALUEPAIR__ */
