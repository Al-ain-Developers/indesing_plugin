//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/snippetrunner/SnipRunStartupShutdown.cpp $
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

// General includes:
#include "CPMUnknown.h"

// Project includes:
#include "SnipRunID.h"
#include "IStartupShutdownService.h"
#include "SnipRunManager.h"

/** Implements IStartupShutdownService; purpose is to delete all Snippets instance at shutdown.

	
	@ingroup snippetrunner
*/
class SnipRunStartupShutdown : 
	public CPMUnknown<IStartupShutdownService>
{
public:
	/**	Constructor
		@param boss interface ptr from boss object on which this interface is aggregated.
	 */
    SnipRunStartupShutdown(IPMUnknown* boss );

	/**	Destructor
	 */
	virtual ~SnipRunStartupShutdown() {}

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
CREATE_PMINTERFACE(SnipRunStartupShutdown, kSnipRunStartupShutdownImpl)

/* Constructor
*/
SnipRunStartupShutdown::SnipRunStartupShutdown(IPMUnknown* boss) :
    CPMUnknown<IStartupShutdownService>(boss)
{
}


/* Startup
*/
void SnipRunStartupShutdown::Startup()
{
}


/* Shutdown
*/
void SnipRunStartupShutdown::Shutdown()
{
	do 
	{
		//	Watson# 1315301: A SnpRunnable instance is static, in Xcode, it doesn't get deleted until InDesign Shutdown
		//	Call SnipRunManager::DeleteInstance() inside a shutdown responder, and DeletInstance will remove all snippets there.
		//	Before this change, snippet is deleted in SnpRunnable's dtor by calling SnipRunManager::RemoveSnippet, it was too late
		//	in Xcode cause the static was deleted after InDesign Shutdown
		SnipRunManager* snipRunnerManager = SnipRunManager::Instance();
		snipRunnerManager->DeleteInstance();
	} while(kFalse);
}

 
