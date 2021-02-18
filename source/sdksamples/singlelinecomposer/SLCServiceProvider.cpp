//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/singlelinecomposer/SLCServiceProvider.cpp $
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
#include "IK2ServiceProvider.h"

// General includes:
#include "CPMUnknown.h"
#include "TextID.h"
#include "K2Vector.h"

// Project includes:
#include "SLCID.h"

/** Registers SLCParagraphComposer as a kTextEngineService, the ServiceID under
	which all IParagraphComposer services are registered. Also provides
	the name used to identify the composer in the user interface.

	@ingroup singlelinecomposer
	
	@see IK2ServiceProvider
	@see kTextEngineService
	@see SLCParagraphComposer
*/
class SLCServiceProvider : public CPMUnknown<IK2ServiceProvider>
{
public:
	/**	Constructor.
		@param boss interface ptr of boss object on which this interface is aggregated.
	*/
	SLCServiceProvider(IPMUnknown * boss) : CPMUnknown<IK2ServiceProvider>(boss)
	{
	}

	/** Get the name of the paragraph composer service.
		@param pName OUT string key that can be translated to give the name
		of the composer for display in the user interface.
	*/
	virtual void GetName(PMString* pName)
	{
		pName->SetKey(kSLComposerNameStringKey);
	}

	/** @return kTextEngineService the ServiceID returned by all IParagraphComposer services.
	*/
	virtual ServiceID GetServiceID(void)
	{
		return kTextEngineService;
	}

	/** @return kFalse.
	*/
	virtual bool16 HasMultipleIDs(void) const
	{
		return kFalse;
	}

	/** This service is registered under the ServiceID kTextEngineService only.
		@param serviceIDs vector to add ServiceID to.
	*/
	virtual void GetServiceIDs(K2Vector<ServiceID>& serviceIDs)
	{
		serviceIDs.push_back(kTextEngineService);
	}

	/** @return kFalse, the composer is not the default IParagraphComposer service.
	*/
	virtual bool16 IsDefaultServiceProvider(void)
	{
		return kFalse;
	}

	/** @return kInstancePerSession.
	*/
	virtual IK2ServiceProvider::InstancePerX GetInstantiationPolicy(void)
	{
		return IK2ServiceProvider::kInstancePerSession;
	}

	/** @return IPlugIn::kUnknownThreadingPolicy since we are not sure if this will be useful for worker threads.
	*/
	virtual IPlugIn::ThreadingPolicy GetThreadingPolicy() const
	{
		return IPlugIn::kUnknownThreadingPolicy;
	}
};

/* CREATE_PMINTERFACE
 Binds the C++ implementation class onto its
 ImplementationID making the C++ code callable by the
 application.
*/
CREATE_PMINTERFACE(SLCServiceProvider, kSLCServiceProviderImpl)

// End, SLCServiceProvider.cpp.

	
