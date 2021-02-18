//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/CrossPlatformTypes.h $
//  
//  Owner: Mouhammad Fakhoury
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

#ifndef __CrossPlatformTypes__
#define __CrossPlatformTypes__


#ifdef __cplusplus
/*
//================================================================================
//	Generic Macros when C++ compiler is invoked
//================================================================================
*/
// Types that can be used in files that compiles for both C++ and Resource compiler such as ShuksanID.h
	#define RezLong(n) ((int32)0 + n)
#elif defined __ODFRC__
	#define RezLong
	#include "GeneralBuildFlags.h" // make sure ODFRC gets important defines, like ID_DEPRECATED
#else

	#ifdef __PLIST__
		/*
			PList compiler (mac only) doesn't need any of this
		 */
		#define RezLong(n) n

	#else 
		/*
		//================================================================================
		//	Generic Macros when resource compiler is invoked
		//================================================================================
		*/

		#include "CoreResTypes.h"


		#ifdef MACINTOSH
			#define RezLong
		#else
			#define RezLong(n) (0L+n)
		#endif

/*
//================================================================================
//	Platform Error Table
//================================================================================
*/

		#ifdef MACINTOSH
			#define ResourcePetb Resource kPErrorTableType
			#define AddPetb
			#define BeginPetb {{
			#define EndPetb }}; 
		#else
			#define ResourcePetb(resID,name,purgeable,preload) resID kPErrorTableType BEGIN name,"\0",
			#define AddPetb	 "\0",
			#define BeginPetb
			#define EndPetb	Add 0L."" END
		#endif

/*
//================================================================================
//	User Error Table
//================================================================================
*/

		#ifdef MACINTOSH
			#define ResourceUetb Resource kUErrorTableType
			#define AddUetb
			#define BeginUetb {{
			#define EndUetb }}; 
		#else
			#define ResourceUetb(resID,name,purgeable,preload) resID kUErrorTableType BEGIN name,"\0",
			#define AddUetb	 "\0",
			#define BeginUetb
			#define EndUetb	Add 0L."" END
		#endif


	#endif // __PLIST__

#endif // __cplusplus || __ODFRC__

#endif // __CrossPlatformTypes__

