#if _MSC_VER < 1900
	#include "xlocnum_hack_vs2010-2013.h"
#elif _MSC_VER == 1900
	#include "xlocnum_hack_vs2015.h"
#elif _MSC_VER >= 1910 && _MSC_VER < 1914
	#include "xlocnum_hack_vs2017.h"
#elif _MSC_VER == 1914 // VS 2017 version 15.7
	#include "xlocnum_hack_vs2017_15_7.h"
#elif _MSC_VER >= 1915 && _MSC_VER < 1920 // VS 2017 version 15.8 and higher
	#include "xlocnum_hack_vs2017_15_8.h"
#elif _MSC_VER >= 1920 && _MSC_VER < 1930 // VS 2019 version 15.0 and higher
	#include "xlocnum_hack_vs2019.h"
#else
	//	Added to aid in determing the current _MSC_VER if it is not handled.
	#if !defined(STR_HELPER) && !defined(STR)
		#define STR_HELPER(x)  #x
		#define STR(x) STR_HELPER(x)
	#endif
	
	#pragma message("Unexpected _MSC_VER: " STR(_MSC_VER))
	#error "You need to update xlocnum hack header by copying over the header from your Visual Studio installation and applying the same changes as to the previous versions. Be careful, this header also changes between minor versions of Visual Studio. MSC_VER was: " VALUE_TO_STRING(_MSC_VER)
#endif