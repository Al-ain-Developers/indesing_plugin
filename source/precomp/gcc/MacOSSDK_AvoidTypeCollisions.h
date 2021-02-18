//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/precomp/gcc/MacOSSDK_AvoidTypeCollisions.h $
//  
//  Owner: Dave Burnard
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

#ifndef __MacOSSDK_AvoidTypeCollisions__
#define __MacOSSDK_AvoidTypeCollisions__

#ifdef MACINTOSH
	// InDesign's PMRect conflicts with the PMRect in PrintCore/PMDefinitions.h
	// This is a temporary hack to not include a couple of print related files
	// so the conflict doesn't surface
	#define __PRINTCORE__
	#define __PRINT__
	// Same issue for TextChunk which is defined in AIFF.h and textiterator.h
	#define __AIFF__
	
	//New for 10.5SDK (csmconfig.h defines uint32, etc.)
		//#define _CSSMCONFIG_H_  1
		#define _UINT32
		#define _UINT16
		#define _UINT8

	// Collision for 'ok' between boost and Carbon Dialogs.h
	#define __DIALOGS__

#endif

#endif
