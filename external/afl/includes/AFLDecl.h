//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/external/afl/includes/AFLDecl.h $
//  
//  Owner: Michael Easter
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

#pragma once
#ifndef __AFLDecl__
#define __AFLDecl__

#ifndef AFL_DECL
	#ifdef __GNUC__
		#define AFL_DECL  __attribute__ ((visibility("default")))
	#else
		#ifdef AFL_LIB
			#define AFL_DECL  __declspec(dllexport)
		#else
			#define AFL_DECL  __declspec(dllimport)
		#endif
	#endif
#endif

#endif	// __AFLDecl__
