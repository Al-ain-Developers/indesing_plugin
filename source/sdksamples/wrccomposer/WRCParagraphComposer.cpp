//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/wrccomposer/WRCParagraphComposer.cpp $
//  
//  Owner: Prashant Dahiya
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
#include "IBoolData.h"
#include "IComposeScanner.h"
#include "IParagraphComposer.h"
#include "IK2ServiceRegistry.h"
#include "IK2ServiceProvider.h"
#include "ITextParcelList.h"
#include "IDocument.h"
#include "IFrameList.h"
#include "IStringData.h"


// General includes:
#include "CPMUnknown.h"
#include "textiterator.h"
#include "TCID.h"

// Project includes:
#include "wrcID.h"

class WRCParagraphComposer : public CPMUnknown<IParagraphComposer>
{
public:

	WRCParagraphComposer(IPMUnknown* boss);

	virtual ~WRCParagraphComposer(void);

	virtual bool16 Recompose(IParagraphComposer::RecomposeHelper* helper);
	
	virtual bool16  RebuildLineToFit (IParagraphComposer::RebuildHelper* helper);
    
    virtual bool16 RebuildLineWithOverrides(IParagraphComposer::RebuildHelper* helper, const AttributeBossList *overrides, bool16 clearOverrides = kFalse){return kFalse;}
};


CREATE_PMINTERFACE(WRCParagraphComposer, kWRCParagraphComposerImpl)

WRCParagraphComposer::WRCParagraphComposer(IPMUnknown* boss) : CPMUnknown<IParagraphComposer>(boss)
{}

WRCParagraphComposer::~WRCParagraphComposer(void)	
{}

/*
*/
bool16 WRCParagraphComposer::Recompose(IParagraphComposer::RecomposeHelper* helper)
{
	bool16 result = kFalse;
	do
	{
		TRACE("WRCParagraphComposer::Recompose\n");
		if (helper == nil)
		{
			ASSERT(helper);
			break;
		}

		ISession *gSession = GetExecutionContextSession();
		if(!gSession)
			break;

		InterfacePtr<IK2ServiceRegistry> iRegistry(gSession, UseDefaultIID());
		if (!iRegistry)
			break;

		{
			InterfacePtr<IK2ServiceProvider> iServiceProvider(iRegistry->QueryServiceProviderByClassID(kTextEngineService , kOptycaParagraphComposerBoss));
			if(!iServiceProvider)
				break;

			InterfacePtr<IParagraphComposer> adobeWorldReadyParagrahComposer(iServiceProvider, UseDefaultIID());
			if( adobeWorldReadyParagrahComposer )
			{
				TRACE(" using kOptycaParagraphComposerBoss\n");
				result = adobeWorldReadyParagrahComposer->Recompose(helper);
			}

		}
	} 
	while (false);
	
	return result;
}

bool16 WRCParagraphComposer::RebuildLineToFit(IParagraphComposer::RebuildHelper* helper)
{
	bool16 result = kFalse;
	do
	{
		TRACE("WRCParagraphComposer::RebuildLineToFit\n");
		
		ASSERT(helper);
		if(!helper) 
		{
			break;
		}

		ISession *gSession = GetExecutionContextSession();
		if(!gSession)
			break;

		InterfacePtr<IK2ServiceRegistry> iRegistry(gSession, UseDefaultIID());
		if (!iRegistry)
			break;

		{
			InterfacePtr<IK2ServiceProvider> iServiceProvider(iRegistry->QueryServiceProviderByClassID(kTextEngineService , kOptycaParagraphComposerBoss));
			if(!iServiceProvider)
				break;

			InterfacePtr<IParagraphComposer> adobeWorldReadyParagrahComposer(iServiceProvider, UseDefaultIID());
			if( adobeWorldReadyParagrahComposer )
			{
				TRACE(" using kOptycaParagraphComposerBoss\n");
				result = adobeWorldReadyParagrahComposer->RebuildLineToFit(helper);
			}
		}

	} while (false);
	return result;
}

// End of WRCParagraphComposer.cpp

