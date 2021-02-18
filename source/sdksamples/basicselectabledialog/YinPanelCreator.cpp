//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/basicselectabledialog/YinPanelCreator.cpp $
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

// Implementation includes:
#include "cpanelcreator.h"

// Project includes:
#include "BscSlDlgID.h"

/** We override CPanelCreator::GetPanelRsrcID() so we 
  	can provide a specific service ID and resource ID for our panel.
	This is one of the key components that allows the switching mechanism.
	This implements IPanelCreator, and uses the partial implementation CPanelCreator.
	@see GetPanelRsrcID
  	@ingroup basicselectabledialog
	
*/
class YinPanelCreator : public CPanelCreator
{
public:
	/**	Constructor.
		@param boss IN interface ptr from boss object on which this interface is aggregated.
	*/
	YinPanelCreator(IPMUnknown* boss) : CPanelCreator(boss) {}

	/** Destructor.
	*/
	virtual ~YinPanelCreator() {}

	/** Returns the resource ID of the panel that is used in finding the
		service IDs resource and the panel view resource.
		Called by CPanelCreator::GetServiceIDs and CPanelCreator::GetPanelViewRsrcID.
		@return resource ID containing service IDs resource and panel view resource.
	*/
	virtual RsrcID GetPanelRsrcID() const;
};

/* CREATE_PMINTERFACE
 Binds the C++ implementation class onto its ImplementationID 
 making the C++ code callable by the application.
*/
CREATE_PMINTERFACE(YinPanelCreator, kYinPanelCreatorImpl)

/* GetPanelRsrcID
*/
RsrcID YinPanelCreator::GetPanelRsrcID() const
{
	return kYinPanelCreatorResourceID;
}

// End, YinPanelCreator.cpp

