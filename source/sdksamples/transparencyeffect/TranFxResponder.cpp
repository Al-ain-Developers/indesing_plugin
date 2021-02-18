//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/transparencyeffect/TranFxResponder.cpp $
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
#include "isignalmgr.h"
#include "IDocumentSignalData.h"
#include "IDrawOptions.h"

// General  includes:
#include "CResponder.h"
#include "PMRect.h"

// Project includes:
#include "TranFxID.h"
#include "TranFxMatteFactory.h"

/** Purges effect images from the image cache when a document closes.

	
	@ingroup transparencyeffect
 */
class TranFxResponder : public CResponder
{
public:
	/** Constructor.
		@param boss
	*/
	TranFxResponder(IPMUnknown* boss);

	/** Destructor.
	*/
	virtual ~TranFxResponder(); 

	/** Purges effect images from the image cache when a document closes.
		@param signalMgr provides information about the signal.
	 */
	virtual void Respond(ISignalMgr* signalMgr);
};

/*
*/
CREATE_PMINTERFACE(TranFxResponder, kTranFxResponderImpl)

/*
*/
TranFxResponder::TranFxResponder(IPMUnknown* boss) : CResponder(boss)
{
}

/*
*/
TranFxResponder::~TranFxResponder()	
{
}

/*
*/
void TranFxResponder::Respond(ISignalMgr* signalMgr)
{
	do
	{
		// Get a reference to the document. 
		InterfacePtr<IDocumentSignalData> documentSignalData(signalMgr, UseDefaultIID());
		ASSERT(documentSignalData != nil);
		if (documentSignalData == nil)
		{
			break;
		}
		UIDRef documentUIDRef = documentSignalData->GetDocument();

		// Get the service ID from the signal manager
		ServiceID serviceID = signalMgr->GetServiceID();

		// Take action based on the service ID
		switch (serviceID.Get())
		{
		case kBeforeCloseDocSignalResponderService:
			{
				TranFxMatteFactory matteFactory;
				matteFactory.PurgeWholeCache(documentUIDRef);
				break;
			}
		default:
			break;
		}
	} while (false);

}

// End, TranFxResponder.cpp
