//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/buttonui/msopanel/MSOPanelView.cpp $
//  
//  Owner: Michele Stutzman
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

#include "IPanelControlData.h"
#include "IPanelDetailController.h"

// ----- Includes -----

#include "CIDErasablePanelView.h"
#include "FormFieldUIDefs.h"

// ----- Utility files -----


// ----- ID.h files -----

#include "FormFieldUIID.h"


class  MSOPanelView : public CIDErasablePanelView
{
	typedef CIDErasablePanelView inherited;

public:
			 MSOPanelView(IPMUnknown* boss) : inherited(boss) { ; }
			 virtual ~MSOPanelView() { ; }

	virtual PMPoint	ConstrainDimensions(const PMPoint& dimensions) const;
};

// =============================================================================
// *** MSOPanelView impl ***
// -----------------------------------------------------------------------------
#pragma mark MSOPanelView implementation

CREATE_PERSIST_PMINTERFACE(MSOPanelView, kMSOPanelViewImpl)

// -------------------------------------------------------------------------------------				
#define kMinMSOPanelWidth 240
#define kMaxMSOPanelWidth 10000
#define	kMinMSOPanelHeight (2*kMSOStateMediumRowHeight + kCC2016PanelIconHeight + kHeaderHeight)
#define kMaxMSOPanelHeight 10000

PMPoint MSOPanelView::ConstrainDimensions(const PMPoint& dimensions) const
{
	PMPoint constrainedDim( dimensions );

	constrainedDim.ConstrainTo( PMRect(kMinMSOPanelWidth, dimensions.Y(), kMaxMSOPanelWidth, kMaxMSOPanelHeight) );

	InterfacePtr<IPanelDetailController> detailController(this, UseDefaultIID());
	if (detailController)
	{
		InterfacePtr<const IPanelControlData> panelData(this,UseDefaultIID());
		IControlView* upperStrip = panelData->FindWidget(kMSOPanelNameStripWidgetID);
		IControlView* lowerStrip = panelData->FindWidget(kMSOPanelControlStripWidgetID);

		PMReal nonListHeight = lowerStrip->GetFrame().Height() + upperStrip->GetFrame().Height();
		
		IControlView* treeView = panelData->FindWidget(kMSOPanelTreeWidgetID);
									   
		PMReal h = kMSOStateMediumRowHeight;
		if (detailController->GetDetailLevel()+1 == kSmallSize)
			h = kMSOStateSmallRowHeight;
		else if (detailController->GetDetailLevel()+1 == kLargeSize)
			h = kMSOStateLargeRowHeight;
		else if (detailController->GetDetailLevel()+1 == kExtraLargeSize)
			h = kMSOStateExtraLargeRowHeight;

		//	Need to round down to a full tag width so we don't show half tags.
		PMReal listHeight = constrainedDim.Y() - nonListHeight;

		const int32 kMinNumRowsVisible = 3;	// so has enough room for the MSOAndMixedSelection text
		int32 numRowsToShow = std::max(kMinNumRowsVisible,::ToInt32(::Floor(listHeight/h)));

		listHeight = numRowsToShow * h;
		constrainedDim.Y(listHeight + nonListHeight);
	}

	return constrainedDim;
} // end ConstrainDimensions()