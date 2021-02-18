//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/xmlcataloghandler/XCatHndStartupShutdown.cpp $
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
#include "IStartupShutdownService.h"
#include "IXCatHndFacade.h"
// General includes:
#include "CPMUnknown.h"
#include "Utils.h"
#include "SDKFileHelper.h"
#include "ErrorUtils.h"
// Project includes:
#include "XCatHndID.h"


/** Implements IStartupShutdownService
	@ingroup xmlcataloghandler
*/
class XCatHndStartupShutdown : 
	public CPMUnknown<IStartupShutdownService>
{
public:
	/**	Constructor
		@param boss interface ptr from boss object on which this interface is aggregated.
	 */
    XCatHndStartupShutdown(IPMUnknown* boss );

	/**	Destructor
	 */
	virtual ~XCatHndStartupShutdown() {}

	/**	Called when app is starting up; attempt to load default catalog.
		@see IStartupShutdownService::Startup
	 */
    virtual void Startup();

	/**	@see IStartupShutdownService::Shutdown
	 */
	virtual void Shutdown() {}
};

/* CREATE_PMINTERFACE
 Binds the C++ implementation class onto its ImplementationID 
 making the C++ code callable by the application.
*/
CREATE_PMINTERFACE(XCatHndStartupShutdown, kXCatHndStartupShutdownImpl)

/* Constructor
*/
XCatHndStartupShutdown::XCatHndStartupShutdown(IPMUnknown* boss) :
    CPMUnknown<IStartupShutdownService>(boss)
{
}


/* 
*/
void XCatHndStartupShutdown::Startup()
{
    do 
	{
		IDFile defaultCatalogFile = Utils<IXCatHndFacade>()->GetDefaultXMLCatalogFile();
		SDKFileHelper fileHelper(defaultCatalogFile);
		if(fileHelper.IsExisting()) {
			ErrorCode err = 
				Utils<IXCatHndFacade>()->LoadCatalog(defaultCatalogFile);
			} 
		// If there is no catalog there, then no problem; we look for one in the same
		// folder as the XML we're importing
	} while(kFalse);
}



 
