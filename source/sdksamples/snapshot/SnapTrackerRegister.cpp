//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/snapshot/SnapTrackerRegister.cpp $
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

#include "ITrackerRegister.h"
#include "ITrackerFactory.h"
#include "ISession.h"
#include "SnapID.h"
#include "LayoutUIID.h"

#include "CPMUnknown.h"

/** This ITrackerRegister implementation registers the SnapShot plug-in's trackers
	with the application. 

	
	@ingroup snapshot
*/
class SnapTrackerRegister : public CPMUnknown<ITrackerRegister>
{
public:
	/** Constructor */
	SnapTrackerRegister(IPMUnknown* boss);

	/**Register the trackers with the application tracker factory. */
	void Register(ITrackerFactory* factory);
	
};

/*
 CREATE_PMINTERFACE
 This macro creates a class factory for the given class name
 and registers the ID with the host.
*/
CREATE_PMINTERFACE(SnapTrackerRegister, kSnapTrackerRegisterImpl)

SnapTrackerRegister::SnapTrackerRegister(IPMUnknown* boss) :
	CPMUnknown<ITrackerRegister>(boss)
{
}

/* Register
*/
void SnapTrackerRegister::Register(ITrackerFactory* factory)
{
	factory->InstallTracker(kLayoutWidgetBoss, kSnapToolBoss, kSnapTrackerBoss);
}


// End, SnapTrackerRegister.cpp.


