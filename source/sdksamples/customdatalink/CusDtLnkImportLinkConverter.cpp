//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/customdatalink/CusDtLnkImportLinkConverter.cpp $
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
#include "CusDtLnkImportLinkConverter.h"

#include "ILinkResource.h"
#include "IDatalink.h"
#include "CusDtLnkID.h"


CREATE_PMINTERFACE (CusDtLnkImportLinkConverter, kCusDtLnkImportLinkConverterImpl)

//========================================================================================
// Constructor
//========================================================================================
CusDtLnkImportLinkConverter::CusDtLnkImportLinkConverter(IPMUnknown* boss)
: inherited(boss),
  fType(kImport),
  fClientId(kIDLinkClientID),
  fResourceModState(kResourceModified)
{
}

//========================================================================================
// Destructor
//========================================================================================
CusDtLnkImportLinkConverter::~CusDtLnkImportLinkConverter()
{
}

//========================================================================================
// CusDtLnkImportLinkConverter::SetResourceModificationState
//========================================================================================
void CusDtLnkImportLinkConverter::SetResourceModificationState (ResourceModificationState modState)
{
	if (fResourceModState != modState)
	{
		fResourceModState = modState;
	}
}


//========================================================================================
// CusDtLnkImportLinkConverter::Init
//========================================================================================
ErrorCode CusDtLnkImportLinkConverter::Init (IDataLink* iDataLink)
{
	uint64		storedSize = 0;
	uint64		storedTime = 0;
	IDataLink::StateType	oldStoredType = iDataLink->GetStoredState (&storedSize, &storedTime);

	ErrorCode	errorCode = kFailure;
	InterfacePtr<ILinkResource>	iPrivateResource (this, UseDefaultIID ());
	if (iPrivateResource != nil)
	{
		errorCode = kSuccess;
		fImportStamp = iPrivateResource->GetStamp();
		if (oldStoredType == IDataLink::kLinkOutOfDate)
		{
			fLastImportTime.SetTime(storedTime);
			fImportModTime.SetTime(storedTime);
			SetResourceModificationState(kResourceModified); 
		}
		else
		{
			fLastImportTime.CurrentTime();
			fImportModTime.SetTime(storedTime);
			SetResourceModificationState(kResourceUnmodified); 
		}
	}

	return errorCode;
}

