//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/buttonui/msopanel/MSOPanelDetailController.cpp $
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

#include "IControlView.h"
#include "IOWLPaletteSizer.h"
#include "IPanelControlData.h"
#include "IPanelDetailController.h"
#include "IPMStream.h"
#include "ITreeAttributes.h"
#include "ITreeViewWidgetMgr.h"
#include "IWidgetParent.h"

// ----- Includes -----

#include "CPMUnknown.h"
#include "FormFieldUIDefs.h"

// ----- Utility files -----

#include "IPalettePanelUtils.h"

// ----- ID.h files -----

#include "FormFieldUIID.h"


class MSOPanelDetailController : public CPMUnknown<IPanelDetailController>
{
public:
	MSOPanelDetailController(IPMUnknown *boss);
	virtual ~MSOPanelDetailController();
	
	virtual void	ReadWrite(IPMStream *s, ImplementationID prop);

	virtual void	RotateDetailLevel();
	virtual void	ShowDetailLevel(int16 nthLevel);
	
	virtual int16	GetDetailLevel() const;
	virtual int16	GetNumDetailLevels() const;
	virtual int16	GetDefaultDetailLevel() const;
	
private:
	int32	fTreeNodeSize;
};

// =============================================================================
// *** MSOPanelDetailController impl ***
// -----------------------------------------------------------------------------

CREATE_PERSIST_PMINTERFACE(MSOPanelDetailController, kMSOPanelDetailControllerImpl)

MSOPanelDetailController::MSOPanelDetailController(IPMUnknown *boss) :
	CPMUnknown<IPanelDetailController>(boss), fTreeNodeSize(kMediumSize)
{
}

MSOPanelDetailController::~MSOPanelDetailController()
{
}

// -----------------------------------------------------------------------------

void MSOPanelDetailController::ReadWrite(IPMStream *s, ImplementationID prop)
{
	bool16 readingFromResource = kFalse;
	s->XferBool(readingFromResource);
	 
	if (s->IsWriting() || !readingFromResource)
	{
		s->XferInt32(fTreeNodeSize);
	}
}

// -----------------------------------------------------------------------------

void MSOPanelDetailController::RotateDetailLevel()
{
	switch (fTreeNodeSize)
	{
	case kSmallSize:
		ShowDetailLevel(1);
		break;
	case kMediumSize:
		ShowDetailLevel(2);
		break;
	case kLargeSize:
		ShowDetailLevel(3);
		break;
	case kExtraLargeSize:
		ShowDetailLevel(0);
		break;
	}
}

// -----------------------------------------------------------------------------

void MSOPanelDetailController::ShowDetailLevel(int16 nthLevel)
{
	if (nthLevel+1 != fTreeNodeSize)
	{
		PreDirty();
		fTreeNodeSize = nthLevel+1;
		InterfacePtr<IPanelControlData> panelData(this, UseDefaultIID());
		IControlView* treeView = panelData->FindWidget(kMSOPanelTreeWidgetID);
		InterfacePtr<ITreeViewWidgetMgr> tvWidgetMgr(treeView, UseDefaultIID());
		if (tvWidgetMgr)
		{
			tvWidgetMgr->SetStyle(fTreeNodeSize);
			
			// fix up the thumb scroll size.
			InterfacePtr<ITreeAttributes> treeAttr(tvWidgetMgr, UseDefaultIID());
			PMReal h = tvWidgetMgr->GetNodeWidgetHeight(kInvalidNodeID);
			int32 height = ToInt32(h);
			treeAttr->SetScrollAmount(ITreeAttributes::kVerticalScrollBar, height, height);  // this will call ChangeRoot()
								
			// this next bit is a little unusual. Toggling the row size changes our min max size, but we only recalculate that during panel resize usually...so we have to force a recalculation of our min/max size by calling UpdateOWLPaletteSizes()
			InterfacePtr<const IWidgetParent> wp(panelData,UseDefaultIID());
			InterfacePtr<IOWLPaletteSizer> palSizer((IOWLPaletteSizer*)wp->QueryParentFor(IOWLPaletteSizer::kDefaultIID));
			palSizer->UpdateOWLPaletteSizes();

			if (treeView && treeView->IsVisible(kTrue))
			{
				// force redraw now with new node size
				treeView->ForceRedraw(treeView->GetDrawRegion(), kTrue);
			}
		}
	}
}

// -----------------------------------------------------------------------------

int16 MSOPanelDetailController::GetDetailLevel() const
{
	// Detail level is 0-based, tree node style is 1-based
	return fTreeNodeSize-1;
}

// -----------------------------------------------------------------------------

int16 MSOPanelDetailController::GetNumDetailLevels() const
{
	return 4;
}

// -----------------------------------------------------------------------------

int16 MSOPanelDetailController::GetDefaultDetailLevel() const
{
	// kMediumSize-1
	return 1;
}