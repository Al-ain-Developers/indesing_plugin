//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/customactionfilter/CstAFltStartupShutdown.cpp $
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
#include "ActionMapper.h"

// General includes:
#include "CPMUnknown.h"

// Project includes:
#include "CstAFltID.h"
#include "IStartupShutdownService.h"

/** Implements IStartupShutdownService; purpose is to install the idle task.

	
	@ingroup paneltreeview
*/
class CstAFltStartupShutdown : 
	public CPMUnknown<IStartupShutdownService>
{
public:
	/**	Constructor
		@param boss interface ptr from boss object on which this interface is aggregated.
	 */
    CstAFltStartupShutdown(IPMUnknown* boss );

	/**	Destructor
	 */
	virtual ~CstAFltStartupShutdown() {}

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
CREATE_PMINTERFACE(CstAFltStartupShutdown, kCstAFltStartupShutdownImpl)

/* Constructor
*/
CstAFltStartupShutdown::CstAFltStartupShutdown(IPMUnknown* boss) :
    CPMUnknown<IStartupShutdownService>(boss)
{
}


/* Startup
*/
void CstAFltStartupShutdown::Startup()
{
}


/* Shutdown - clear the action map from memory
*/
void CstAFltStartupShutdown::Shutdown()
{
	ActionMapper * actionMapperPtr = ActionMapper::ActionMapperFactory();
	actionMapperPtr->ActionMapperDestroy();
}

 
