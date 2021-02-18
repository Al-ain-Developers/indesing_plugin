//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/K2Pair.h $
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
//	ADOBE CONFIDENTIAL. Portions Copyright 2013 Adobe Systems Incorporated.  All rights reserved.
//
//	NOTICE: All information contained herein is, and remain the property of Adobe Systems Incorporated
//	and its suppliers, if any. The intellectual and technical concepts contained herein are proprietary
//	to Adobe Systems Incorporated and its suppliers and are protected by all applicable intellectual property
//	laws, including trade secret and copyright laws. Dissemination of this information or reproduction of
//	this material is strictly forbidden unless prior written permission is obtained from Adobe Systems Incorporated.
//
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//  
//  Purpose: clone of std::K2Pair based on STLPort 4.0
//
//	This file has been modified by Adobe to meet the needs of the InDesign project.
//  
//  Copyright (c) 1994
//  Hewlett-Packard Company
//  
//  Copyright (c) 1996,1997
//  Silicon Graphics Computer Systems, Inc.
//  
//  Copyright (c) 1997
//  Moscow Center for SPARC Technology
//  
//  Copyright (c) 1999 
//  Boris Fomitchev
//  
//  This material is provided "as is", with absolutely no warranty expressed
//  or implied. Any use is at your own risk.
//  
//  Permission to use or copy this software for any purpose is hereby granted 
//  without fee, provided the above notices are retained on all copies.
//  Permission to modify the code and to distribute modified code is granted,
//  provided the above notices are retained, and a notice that the code was
//  modified is included with the above copyright notice.
//  
//  NOTE: This is an internal header file, included by other STL headers.
//  You should not attempt to use it directly.
//  
//========================================================================================

#pragma once
#ifndef __K2PAIR__
#define __K2PAIR__


template <class _T1, class _T2>
struct K2Pair {
	typedef object_type data_type; // Could write meta function to declare as base type 
								 // if both _T1 and _T2 are base types. But we don't
								 // want to force _T1 and _T2 to declare whether they
								 // are base or objec types.
  typedef _T1 first_type;
  typedef _T2 second_type;

  _T1 first;
  _T2 second;
  K2Pair() {}
  K2Pair(const _T1& __a, const _T2& __b) : first(__a), second(__b) {}

  template <class _U1, class _U2>
  K2Pair(const K2Pair<_U1, _U2>& __p) : first(__p.first), second(__p.second) {}

  K2Pair(const K2Pair<_T1, _T2>& __o) = default;
  K2Pair(K2Pair<_T1, _T2>&& __o) = default;
  K2Pair &operator=(const K2Pair<_T1, _T2>& __o) = default;
  K2Pair &operator=(K2Pair<_T1, _T2>&& __o) = default;

  friend inline void swap(K2Pair<_T1, _T2>& a, K2Pair<_T1, _T2>& b)
  {
	  using std::swap;
	  swap(a.first, b.first);
	  swap(a.second, b.second);
  }

};

template <class _T1, class _T2>
inline bool16  operator==(const K2Pair<_T1, _T2>& __x, const K2Pair<_T1, _T2>& __y)
{ 
  return __x.first == __y.first && __x.second == __y.second; 
}

template <class _T1, class _T2>
inline bool16  operator<(const K2Pair<_T1, _T2>& __x, const K2Pair<_T1, _T2>& __y)
{ 
  return __x.first < __y.first || 
         (!(__y.first < __x.first) && __x.second < __y.second); 
}


template <class _T1, class _T2>
inline bool16  operator!=(const K2Pair<_T1, _T2>& __x, const K2Pair<_T1, _T2>& __y) {
  return !(__x == __y);
}

template <class _T1, class _T2>
inline bool16  operator>(const K2Pair<_T1, _T2>& __x, const K2Pair<_T1, _T2>& __y) {
  return __y < __x;
}

template <class _T1, class _T2>
inline bool16  operator<=(const K2Pair<_T1, _T2>& __x, const K2Pair<_T1, _T2>& __y) {
  return !(__y < __x);
}

template <class _T1, class _T2>
inline bool16  operator>=(const K2Pair<_T1, _T2>& __x, const K2Pair<_T1, _T2>& __y) {
  return !(__x < __y);
}


template <class _T1, class _T2>
inline K2Pair<_T1, _T2>  K2make_pair(const _T1& __x, const _T2& __y)
{
  return K2Pair<_T1, _T2>(__x, __y);
}

template <class First, class Second>
struct MatchFirstPredicate {
	MatchFirstPredicate(const First& first) : fFirst(first) {}
	bool16 operator()(const K2Pair<First,Second>& x) { return x.first == fFirst; }
	First fFirst;
};

template <class First, class Second>
struct MatchSecondPredicate {
	MatchSecondPredicate(const Second& second) : fSecond(second) {}
	bool16 operator()(const K2Pair<First,Second>& x) { return x.second == fSecond; }
	Second fSecond;
};



#endif /* __K2PAIR__ */
