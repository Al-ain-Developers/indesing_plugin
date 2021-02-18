//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/InterfaceTrackingUtils.h $
//  
//  Owner: Habib Khalfallah
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
#ifndef __InterfaceTrackingUtils__
#define __InterfaceTrackingUtils__
#ifdef DEBUG
#ifdef __OMTypes__
#ifdef __clang__ // Not supported until we convert the assembly code
	//#define INTERFACEPROXIES_SUPPORTED
	//#undef TRACKING_ALL
#else
	#define INTERFACEPROXIES_SUPPORTED
	#undef TRACKING_ALL
#endif
#endif
#endif

#ifdef DEBUG
#ifdef __OMTypes__
#pragma export on

class IPMUnknown;
namespace InterfaceTrackingUtils
{
	PUBLIC_DECL void ReportOutStandingBosses();
	PUBLIC_DECL void ReportOutstandingBoss(IPMUnknown *bossIFace, char *logfile);
	PUBLIC_DECL void ReportOutstandingBoss(ClassID cls, char *logfile);

	PUBLIC_DECL const IPMUnknown * ExtractInterfaceImplementation (const IPMUnknown *pIFace);
 
	inline PUBLIC_DECL const void * ExtractInterfaceImplementation (const void *pIFace)
	{return pIFace;}
	
	inline PUBLIC_DECL  bool16 EqualIFacePtrs (const IPMUnknown *p1, const IPMUnknown *p2)
	{
		const IPMUnknown *_p1 = ExtractInterfaceImplementation(p1);
		const IPMUnknown *_p2 = ExtractInterfaceImplementation(p2);
		
		return (_p1 == _p2);
	}

#ifdef INTERFACEPROXIES_SUPPORTED
	// singleton that is intialized and destroyed at load of omlib.
	// no thread contention involved
	extern PUBLIC_DECL void * ts_SharedProxyObj;
#endif
}

#pragma export off
#endif //__OMTypes__
#endif // DEBUG
#endif // __InterfaceTrackingUtils__
