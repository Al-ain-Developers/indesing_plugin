//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/dynamicdocumentsui/TimingPanelNameILEEditingAttributes.cpp $
//  
//  Owner: Yeming Liu
//  
//  $Author: pmbuilder $
//  
//  $DateTime: 2020/11/06 13:08:29 $
//  
//  $Revision: #2 $
//  
//  $Change: 1088580 $
//  
//  ADOBE CONFIDENTIAL
//  
//  Copyright 1997-2010 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//  
//  Owner
//  
//========================================================================================

#include "VCPlugInHeaders.h"

// ----- Interface files -----

#include "IWidgetParent.h"
#include "ITreeNodeIDData.h"
#include "ITreeViewController.h"

// ----- Include files -----

#include "InLineEditEditingAttributes.h"

// ----- Utilitity files -----

// ----- ID files -----

#include "DynamicDocumentsUIID.h"

class TimingPanelNameILEEditingAttributes : public InLineEditEditingAttributes
{
	public:	
		TimingPanelNameILEEditingAttributes(IPMUnknown *boss) : InLineEditEditingAttributes(boss) { }
		~TimingPanelNameILEEditingAttributes() { }

		virtual bool16 IsSelected() const;
		virtual bool16 GetFitEditBoxtoText() const { return kTrue; }
};

CREATE_PERSIST_PMINTERFACE(TimingPanelNameILEEditingAttributes, kTimingPanelNameILEEditingAttributesImpl)

//----------------------------------------------------------------------------------------
// TimingPanelNameILEEditingAttributes::IsSelected
//----------------------------------------------------------------------------------------
bool16 TimingPanelNameILEEditingAttributes::IsSelected() const
{
	InterfacePtr<const IWidgetParent>	iWidgetParent(this, UseDefaultIID());
	InterfacePtr<const ITreeNodeIDData>	iTreeNodeIDData((ITreeNodeIDData*)iWidgetParent->QueryParentFor(IID_ITREENODEIDDATA));
	if (iTreeNodeIDData)
	{
		InterfacePtr<const ITreeViewController> iTreeViewController((ITreeViewController*)iWidgetParent->QueryParentFor(IID_ITREEVIEWCONTROLLER));
		if (iTreeViewController->IsSelected(iTreeNodeIDData->Get()))
			return kTrue;
	}

	return kFalse;
}
