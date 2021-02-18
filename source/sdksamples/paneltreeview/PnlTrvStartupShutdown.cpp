//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/paneltreeview/PnlTrvStartupShutdown.cpp $
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
#include "ISession.h"
#include "IIdleTask.h"

// General includes:
#include "CPMUnknown.h"

// Project includes:
#include "PnlTrvID.h"
#include "IStartupShutdownService.h"

/** Implements IStartupShutdownService; purpose is to install the idle task.

	
	@ingroup paneltreeview
*/
class PnlTrvStartupShutdown : 
	public CPMUnknown<IStartupShutdownService>
{
public:
	/**	Constructor
		@param boss interface ptr from boss object on which this interface is aggregated.
	 */
    PnlTrvStartupShutdown(IPMUnknown* boss );

	/**	Destructor
	 */
	virtual ~PnlTrvStartupShutdown() {}

	/**	Called by the core when app is starting up
	 */
    virtual void Startup();

	/**	Called by the core when app is shutting down
	 */
    virtual void Shutdown();
};

/* CREATE_PMINTERFACE
 Binds the C++ implementation class onto its ImplementationID 
 making the C++ code callable by the application.
*/
CREATE_PMINTERFACE(PnlTrvStartupShutdown, kPnlTrvStartupShutdownImpl)

/* Constructor
*/
PnlTrvStartupShutdown::PnlTrvStartupShutdown(IPMUnknown* boss) :
    CPMUnknown<IStartupShutdownService>(boss)
{
}


/* Startup
*/
void PnlTrvStartupShutdown::Startup()
{
    do 
	{
		InterfacePtr<IIdleTask> 
			task(GetExecutionContextSession(), IID_IPNLTRVIDLETASK);
		ASSERT(task);
		if(!task)
		{
			break;
		}
		task->InstallTask(0);
	} while(kFalse);
}


/* Shutdown
*/
void PnlTrvStartupShutdown::Shutdown()
{
	do 
	{
		InterfacePtr<IIdleTask> 
			task(GetExecutionContextSession(), IID_IPNLTRVIDLETASK);
		ASSERT(task);
		if(!task)
		{
			break;
		}
		task->UninstallTask();
	} while(kFalse);
}

 
