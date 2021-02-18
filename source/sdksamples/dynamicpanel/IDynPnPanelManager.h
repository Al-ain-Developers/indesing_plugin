//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/dynamicpanel/IDynPnPanelManager.h $
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

#ifndef _IDynPnPanelManager_
#define _IDynPnPanelManager_

// Interface includes:
#include "IPMUnknown.h"
#include "DynPnID.h"

/** From SDK sample; interface to instantiate the (singleton) dynamic panel manager; also 
	methods to create and destroy dynamic panels, and query their properties.
	There is a singleton dynamic panel manager boss object, which is created on
	demand the first time that QueryDynamicPanelManager is called.

	
	@ingroup dynamicpanel
*/
class IDynPnPanelManager : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IDynPnPANELMANAGER };

	/**	Accessor for the count of (persistent) panels created to date
			@return int32 
	*/
	virtual int32 GetPanelsCreatedCount()=0;

	/** Create the named panel if it doesn't already exist
		@return kSuccess if operation completed successfully, kFailure otherwise
	*/
	virtual ErrorCode Create(const PMString& name)=0;

	/** Destroy the named panel if it can be destroyed
		@return kSuccess if operation completed successfully, kFailure otherwise
	*/
	virtual ErrorCode Destroy(const PMString& name)=0;

	/**	Determine if named panel is showing
		@param name specifies the panel whose visibility we're interested in
		@return bool16 
	 */
	virtual bool16 IsShowing(const PMString& name)=0;

	/**	Class (static) method to allow  instance of our dynamic panel manager to be obtained 
		@return reference to the singleton dynamic panel manager
	 */
	static IDynPnPanelManager* QueryDynamicPanelManager();
};

#endif // _IDynPnPanelManager_

