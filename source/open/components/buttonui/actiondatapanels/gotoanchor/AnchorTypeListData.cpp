//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/buttonui/actiondatapanels/gotoanchor/AnchorTypeListData.cpp $
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

#include "IAnchorTypeListData.h"

// ----- Implementation Includes -----

#include "BehaviorUIID.h"
#include "CPMUnknown.h"
#include "PMString.h"


//========================================================================================
// CLASS AnchorFileListData
//========================================================================================

class AnchorTypeListData : public CPMUnknown<IAnchorTypeListData>
{
public:
	AnchorTypeListData(IPMUnknown *boss);
	virtual ~AnchorTypeListData();

	virtual void						SetAnchorTypeData(const K2Vector<AnchorTypeData>& GoToAnchorTypeData);
	virtual K2Vector<AnchorTypeData>	GetAnchorTypeData() const;

private:
	K2Vector<AnchorTypeData> fGoToAnchorTypeData;

};	

//========================================================================================
// METHODS AnchorTypeListData
//========================================================================================

CREATE_PMINTERFACE(AnchorTypeListData, kAnchorTypeListDataImpl)

//----------------------------------------------------------------------------------------
// AnchorTypeListData::AnchorTypeListData
//----------------------------------------------------------------------------------------

AnchorTypeListData::AnchorTypeListData(IPMUnknown *boss) :
	CPMUnknown<IAnchorTypeListData>(boss)
{
}

//----------------------------------------------------------------------------------------
// AnchorTypeListData::~AnchorTypeListData
//----------------------------------------------------------------------------------------

AnchorTypeListData::~AnchorTypeListData()
{
}

//----------------------------------------------------------------------------------------
// AnchorTypeListData::SetAnchorTypeData
//----------------------------------------------------------------------------------------

void AnchorTypeListData::SetAnchorTypeData(const K2Vector<AnchorTypeData>& GoToAnchorTypeData)
{
	fGoToAnchorTypeData = GoToAnchorTypeData;
}

//----------------------------------------------------------------------------------------
// AnchorTypeListData::GetAnchorTypeData
//----------------------------------------------------------------------------------------

K2Vector<IAnchorTypeListData::AnchorTypeData> AnchorTypeListData::GetAnchorTypeData() const
{
	return fGoToAnchorTypeData;
}

// end AnchorTypeListData.cpp