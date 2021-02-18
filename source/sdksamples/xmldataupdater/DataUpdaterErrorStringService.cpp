//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/xmldataupdater/DataUpdaterErrorStringService.cpp $
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
#include "DataUpdaterID.h"

/** From SDK sample; Provides error string service for XMLDataUpdater that 
	maps this plug-in's ErrorCode's to error strings defined in the 
	UserErrorTable ODFRez statement.

	@ingroup xmldataupdater
*/
class DataUpdaterErrorStringService : public CErrorStringService
{
public:
	/** Constructor 
	 * 	This is where we specify the pluginID and the resourceID for the 
	 * 	UserErrorTable resource that is associated with this implementation.
	 */
	DataUpdaterErrorStringService(IPMUnknown* boss):
		CErrorStringService(boss, kDataUpdaterPluginID, kSDKDefErrorStringResourceID) {}

	/** Destructor 
	 */
	virtual ~DataUpdaterErrorStringService(void) {}
};

/* Make the implementation available to the application.
*/
CREATE_PMINTERFACE(DataUpdaterErrorStringService, kDataUpdaterErrorStringServiceImpl)

// End, DataUpdaterErrorStringService.cpp.
