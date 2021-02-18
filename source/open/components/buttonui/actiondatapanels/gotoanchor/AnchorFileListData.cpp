//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/buttonui/actiondatapanels/gotoanchor/AnchorFileListData.cpp $
//  
//  Owner: Steve Dowd
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

// ----- Interface Includes -----
#include "ShuksanID.h"

#include "IAnchorFileListData.h"

// ----- Implementation Includes -----

#include "BehaviorUIID.h"
#include "CPMUnknown.h"
#include "PMString.h"


//========================================================================================
// CLASS AnchorFileListData
//========================================================================================

class AnchorFileListData : public CPMUnknown<IAnchorFileListData>
{
public:
	AnchorFileListData(IPMUnknown *boss);
	virtual ~AnchorFileListData();

	virtual void						SetAnchorFileData(const K2Vector<AnchorFileData>& GoToAnchorFileData);
	virtual K2Vector<AnchorFileData>	GetAnchorFileData() const;

private:
	K2Vector<AnchorFileData> fGoToAnchorFileData;

};	

//========================================================================================
// METHODS AnchorFileListData
//========================================================================================

CREATE_PMINTERFACE(AnchorFileListData, kAnchorFileListDataImpl)

//----------------------------------------------------------------------------------------
// AnchorFileListData::AnchorFileListData
//----------------------------------------------------------------------------------------

AnchorFileListData::AnchorFileListData(IPMUnknown *boss) :
	CPMUnknown<IAnchorFileListData>(boss)
{
}

//----------------------------------------------------------------------------------------
// AnchorFileListData::~AnchorFileListData
//----------------------------------------------------------------------------------------

AnchorFileListData::~AnchorFileListData()
{
}

//----------------------------------------------------------------------------------------
// AnchorFileListData::SetAnchorFileData
//----------------------------------------------------------------------------------------

void AnchorFileListData::SetAnchorFileData(const K2Vector<AnchorFileData>& GoToAnchorFileData)
{
	fGoToAnchorFileData = GoToAnchorFileData;
}

//----------------------------------------------------------------------------------------
// AnchorFileListData::GetAnchorFileData
//----------------------------------------------------------------------------------------

K2Vector<IAnchorFileListData::AnchorFileData> AnchorFileListData::GetAnchorFileData() const
{
	return fGoToAnchorFileData;
}

// end AnchorFileListData.cpp