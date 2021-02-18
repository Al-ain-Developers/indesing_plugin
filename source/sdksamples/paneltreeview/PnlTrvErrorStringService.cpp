//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/paneltreeview/PnlTrvErrorStringService.cpp $
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
// None.

// Implementation includes:
#include "CErrorStringService.h"
#include "PnlTrvID.h"


/** Companion interface for an error string service. 
 *	This implementation, coupled with a UserErrorTable resource
 * 	and IDs in the kErrorIDSpace provide a searchable table
 * 	or error codes and corresponding error strings.. 
 * 
 * 	@ingroup paneltreeview
*/
class PnlTrvErrorStringService : public CErrorStringService
{
	public:
		/**	Constructor 
		*/
		PnlTrvErrorStringService(IPMUnknown* boss)
			: CErrorStringService(boss, kPnlTrvPluginID, kSDKDefErrorStringResourceID)
		{
		}
		
		/** Destructor.  
		*/
		virtual	~PnlTrvErrorStringService(void) 
		{
		}
};


/* CREATE_PMINTERFACE
 Binds the C++ implementation class onto its
 ImplementationID making the C++ code callable by the
 application.
*/
CREATE_PMINTERFACE(PnlTrvErrorStringService, kPnlTrvErrorStringServiceImpl)

// End, PnlTrvErrorStringService.cpp.




