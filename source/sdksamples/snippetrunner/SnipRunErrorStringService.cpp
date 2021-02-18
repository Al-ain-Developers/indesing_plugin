//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/snippetrunner/SnipRunErrorStringService.cpp $
//  
//  Owner: Adobe Developer Technologies
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

#include "VCPlugInHeaders.h"

// Interface includes:
// none.

// General includes:
#include "CErrorStringService.h"

// Project includes:
#include "SnipRunID.h"

/** Implements IErrorString via partial implementation CErrorStringService.
 * 
 * 	@ingroup snippetrunner
 * 	@author Ken Sadahiro
*/
class SnipRunErrorStringService : public CErrorStringService
{
public:
	/** Constructor 
	 * 	This is where we specify the pluginID and the resourceID for the 
	 * 	UserErrorTable resource that is associated with this implementation.
	 */
	SnipRunErrorStringService(IPMUnknown* boss):
		CErrorStringService(boss, kSnipRunPluginID, kSDKDefErrorStringResourceID) {}

	/** Destructor 
	 */
	virtual ~SnipRunErrorStringService(void) {}
};

/* Make the implementation available to the application.
*/
CREATE_PMINTERFACE(SnipRunErrorStringService, kSnipRunErrorStringServiceImpl)

// End, SnipRunErrorStringService.cpp.
