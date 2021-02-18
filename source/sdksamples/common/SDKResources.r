//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/common/SDKResources.r $
//  
//  Owner: Adobe Developer Technologies
//  
//  $Author: vans $
//  
//  $DateTime: 2020/11/06 05:06:09 $
//  
//  $Revision: #1 $
//  
//  $Change: 1088554 $
//  
//  Copyright 1997-2010 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//  
//  This is the resource file that provides the platform-specific resource information
//  common to all SDK plug-ins.
//  
//========================================================================================

#include "BuildNumber.h"

#ifdef MACINTOSH
// Macintosh specific resources: ---------------------------------------------------------

	#include <CoreServices/CoreServices.r>

	resource 'vers' (2) // Must be 2.
	{
		kMajorVersionNumberForResource, 
		kMinorVersionNumberForResource * 16, 
		kDevelopmentStage, 
		1, 
		verUS, 
		kVersionNumberStr, 
		"(for Adobe¨ InDesign¨)"
	};

	resource 'vers' (1) // Must be 1.
	{
		kMajorVersionNumberForResource, 
		kMinorVersionNumberForResource * 16, 
		kDevelopmentStage, 
		1, 
		verUS, 
		kVersionNumberStr, 
		kVersionCopyRightStr
	};

#else
// Windows specific resources: ---------------------------------------------------------

#endif // else MACINTOSH

// End, SDKResources.r.

