//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/customdatalink/CusDtLnkPhase2Conversion.cpp $
//  
//  Owner: SusanCL
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

// ----- Interfaces -----

#include "IPhase2Conversion.h"
#include "isignalmgr.h"
#include "IDataBase.h"
#include "INewLinkConverter.h"
#include "ILinkManager.h"
#include "ILinksManager.h"

// ----- Includes -----

#include "CResponder.h"
#include "FormatNumber.h"
#include "UIDList.h"

// ----- ID.h files -----
#include "FormatID.h"
#include "ShuksanID.h"
#include "CusDtLnkID.h"

/** Handles Phase Two conversion of data for the CusDtLnk plug-in.

	@ingroup customdatalink
	@see IPhase2Conversion
*/
class CusDtLnkPhase2Conversion : public CResponder
{
	public:
		CusDtLnkPhase2Conversion(IPMUnknown * boss) : CResponder(boss) {}
		virtual void Respond(ISignalMgr* signalMgr);
	
	private:
		void ConvertLinksToNewArchitecture(IPhase2Conversion* iPhase2);
};

CREATE_PMINTERFACE(CusDtLnkPhase2Conversion, kCusDtLnkPhase2ConversionImpl)

/*
*/
void CusDtLnkPhase2Conversion::Respond(ISignalMgr* signalMgr)
{
	//
	// Get our Phase 2 Conversion interface from the Signal Manager.
	//
	InterfacePtr<IPhase2Conversion>	iPhase2 (signalMgr, UseDefaultIID());
	ASSERT_MSG((iPhase2 != nil), "CusDtLnkPhase2Conversion::Respond - Cannot get IPhase2Conversion.");

	//
	// Determine the source and target format numbers to see if we need to do conversion.
	//
	FormatID sFormat;
	FormatID tFormat;
	bool16 gotSFormat = iPhase2->GetSourcePluginFormatNumber(kCusDtLnkPluginID, sFormat);
	if (gotSFormat == kFalse)
	{
		// No persistent data from this plug-in found in the database - no conversion required.
		return;
	}
	bool16 gotTFormat = iPhase2->GetTargetPluginFormatNumber(kCusDtLnkPluginID, tFormat);
	ASSERT_MSG(gotTFormat, "CusDtLnkPhase2Conversion::Respond - Cannot get target format number.");

	//
	// If the data was earlier than the BookNewLinksArchitecture format change then convert the data.
	//
	if (sFormat < FormatID(kBasilMajorFormatNumber, kCusDtLnkConvertLinksToNewArchitecture))
	{
		this->ConvertLinksToNewArchitecture(iPhase2);
	}
}

/*
*/
void CusDtLnkPhase2Conversion::ConvertLinksToNewArchitecture(IPhase2Conversion* iPhase2)
{
	//
	// Convert old datalink on each kBookContentBoss
	//
	InterfacePtr<INewLinkConverter>	iLinkConverter(::CreateObject2<INewLinkConverter>(kCusDtLnkNewLinkConverterBoss));
	ASSERT(iLinkConverter);
	if (!iLinkConverter)
	{
		return;
	}
	IDataBase* dbToConvert = iPhase2->GetRootObject().GetDataBase();
	InterfacePtr<ILinkManager> iLinkManager (dbToConvert, dbToConvert->GetRootUID(), UseDefaultIID());
	if (iLinkManager != nil)
	{
		InterfacePtr<ILinksManager> iOldLinkManager (iLinkManager, IID_ILINKSMANAGER);
		if (iOldLinkManager != nil)
		{
			UIDList	oldLinksToRemove (dbToConvert);
			
			ErrorCode		errorCode = kSuccess;
			for (int32 index = iOldLinkManager->GetLinkCount (); index--;)
			{
				UIDRef	oldLinkRef = iOldLinkManager->GetNthLinkUID (index);

				if (iLinkConverter != nil)
				{
					errorCode = iLinkConverter->DoConvert (oldLinkRef);
					ASSERT (errorCode == kSuccess);
				}

				if (errorCode == kSuccess)
				{
					oldLinksToRemove.Append (oldLinkRef.GetUID ());
				}
			}

			//	Delete these data link objects
			iOldLinkManager->RemoveLinks (&oldLinksToRemove);
			for (UIDList::const_iterator iter = oldLinksToRemove.begin(); iter != oldLinksToRemove.end(); ++iter)
				dbToConvert->DeleteUID (*iter);

			if (iOldLinkManager->GetLinkCount () == 0)
			{
				iPhase2->RemoveImplementation(kLinksManagerImpl);
			}
		}
	}		
}
