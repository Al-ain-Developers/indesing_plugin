//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/precomp/common/WShukHeaders.h $
//  
//  Owner: ?
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
//========================================================================================

#ifndef __WShukHeaders_h__
#define __WShukHeaders_h__

#include "xlocnum_hack.h"

#include <memory.h>
#include <cstdint>
#include <cstdio>
//	namespace std{	// VC lacks proper namespace std wrapper.
#include <boost/compatibility/cpp_c_headers/cstdarg>
#include <boost/compatibility/cpp_c_headers/cwctype>
#include <boost/compatibility/cpp_c_headers/cstddef>
//#include <boost/compatibility/cpp_c_headers/cstdio>
#include <boost/compatibility/cpp_c_headers/cstring>
#include <boost/compatibility/cpp_c_headers/cstdlib>
#include <boost/compatibility/cpp_c_headers/cmath>
namespace std {
  using ::hypot; //boost bug: missing from cmath in boost 1.26.0
}
#include <boost/compatibility/cpp_c_headers/cwchar>
#include <boost/compatibility/cpp_c_headers/cctype>
#include <boost/compatibility/cpp_c_headers/ctime>
#include <boost/compatibility/cpp_c_headers/clocale>

#define SIDEBYSIDE_COMMONCONTROLS 1 

	#include <malloc.h>

	//}		// end namespace std
	
	// additional using declarations needed so windows include files will work.
	// also here are things defined in c++ standard headers that should not be in std namespace.
//	using std::wctype_t;
//	using std::va_list;
//	using std::wchar_t;
//	using std::time_t;
	//using std::_pwctype;
	//using std::_fsize_t;
//	using std::stricmp;
//	using std::strnicmp;
//	using std::wcsicmp;
//	using std::mbstate_t;
//	using std::iswascii;
	//using std::_splitpath;
	//using std::_makepath;
	//using std::_fcvt;

using std::FILE;

#include <tchar.h>
#include <windows.h>

// windows sucks - min/max is a macro in windows.h - and missing from <algorithm>
	#undef min
	#undef max
	#if 0
	namespace std{

		template <class T>
		inline const T& 
		min(const T& a, const T& b)
		{
			return b < a ? b : a;
		}

		template <class T>
		inline const T& 
		max(const T& a, const T& b)
		{
			return a < b ? b : a;
		}
	}
	#endif //BOOST_NO_STD_MIN_MAX
#endif
